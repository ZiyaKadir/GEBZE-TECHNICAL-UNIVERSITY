#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <errno.h>
#include "teller.h"
#include "IPC_communication.h"
#include "Parse_client.h"
#include "BinaryTree.h"
#include "helper_log.h"

extern BinaryTree *shared_db;

pid_t Teller(void *(*func)(void *), void *arg_func) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Teller: fork");
        return -1;
    }
    if (pid == 0) {
        func(arg_func);
        _exit(EXIT_SUCCESS);
    }
    return pid;
}


int waitTeller(pid_t pid, int* status) {
    int ret = waitpid(pid, status, 0);
    if (ret == -1) {
        perror("waitpid failed");
        return -1;
    }
    return ret;
}

static int handle_deposit(const ClientRequest *req,
                          int *new_id, double *new_bal,
                          char *msg, size_t msg_size) {
    if (req->amount <= 0) {
        snprintf(msg, msg_size, "Deposit amount must be positive");
        return 0;
    }
    if (req->is_new_account) {
        BankAccount acct = {0, req->amount, 1};
        *new_id = tree_insert_auto_id(shared_db, acct);
        if (*new_id <= 0) {
            snprintf(msg, msg_size, "Failed to create new account");
            return 0;
        }
        *new_bal = req->amount;
        snprintf(msg, msg_size, "New account created with ID: BankID_%d", *new_id);
        return 1;
    }
    BankAccount *acct = tree_find(shared_db, req->numeric_id);
    if (!acct || !acct->is_active) {
        snprintf(msg, msg_size, "Account not found or inactive");
        return 0;
    }
    acct->balance += req->amount;
    *new_bal = acct->balance;
    *new_id = req->numeric_id;
    snprintf(msg, msg_size, "Deposit successful. New balance: %.2f", *new_bal);
    return 1;
}

static int handle_withdraw(const ClientRequest *req,
                           int *new_id, double *new_bal,
                           char *msg, size_t msg_size) {
    if (req->amount <= 0) {
        snprintf(msg, msg_size, "Withdrawal amount must be positive");
        return 0;
    }
    BankAccount *acct = tree_find(shared_db, req->numeric_id);
    if (!acct || !acct->is_active) {
        snprintf(msg, msg_size, "Account not found or inactive");
        return 0;
    }
    if (acct->balance < req->amount) {
        snprintf(msg, msg_size, "Insufficient funds. Current balance: %.2f", acct->balance);
        return 0;
    }
    acct->balance -= req->amount;
    *new_bal = acct->balance;
    *new_id = req->numeric_id;
    if (*new_bal == 0) {
        acct->is_active = 0;
        snprintf(msg, msg_size, "Withdrawal successful. Account closed.");
    } else {
        snprintf(msg, msg_size, "Withdrawal successful. New balance: %.2f", *new_bal);
    }
    return 1;
}

void *process_client_request(void *arg) {
    TellerArgs *args = (TellerArgs *)arg;
    // Remove verbose logging per PDF format
    // printf("\nTeller[%d] launched\n"...);

    sem_t *client_empty = sem_open(args->sem_empty_name, 0);
    sem_t *client_full  = sem_open(args->sem_full_name, 0);
    if (client_empty == SEM_FAILED || client_full == SEM_FAILED) {
        perror("Teller sem_open");
        free(args);
        return NULL;
    }
    // Remove verbose logging
    // printf("Teller[%d] semaphores opened OK\n", getpid());

    while (sem_wait(client_full) == -1 && errno == EINTR) {}
    // Remove verbose logging
    // printf("Teller[%d] awakened: request available\n", getpid());

    int rfd = -1;
    while ((rfd = open(args->client_fifo, O_RDONLY | O_NONBLOCK)) == -1 && errno == EINTR) {}
    if (rfd == -1) {
        perror("Teller open FIFO");
        sem_post(client_empty);
        goto cleanup;
    }
    int flags = fcntl(rfd, F_GETFL);
    fcntl(rfd, F_SETFL, flags & ~O_NONBLOCK);

    int req_index;
    if (read(rfd, &req_index, sizeof req_index) != sizeof req_index) {
        perror("Teller read index");
        close(rfd);
        sem_post(client_empty);
        goto cleanup;
    }

    ClientRequest req;
    if (read(rfd, &req, sizeof req) != sizeof req) {
        perror("Teller read request");
        close(rfd);
        sem_post(client_empty);
        goto cleanup;
    }
    close(rfd);

    // Replace verbose output with PDF format
    char client_name[20];
    snprintf(client_name, sizeof(client_name), "Client%02d", req_index+1);

    int new_id = req.numeric_id;
    double new_bal = 0.0;
    char msg[128];
    int ok;

    if (req.operation == DEPOSIT) {
        ok = handle_deposit(&req, &new_id, &new_bal, msg, sizeof msg);
        if (ok) {
            printf("%s deposited %.0f credits... updating log\n", 
                   client_name, req.amount);
        }
    } else {
        ok = handle_withdraw(&req, &new_id, &new_bal, msg, sizeof msg);
        if (ok) {
            printf("%s withdraws %.0f credits.. updating log", 
                   client_name, req.amount);
            if (new_bal == 0) {
                printf("... Bye %s\n", client_name);
            } else {
                printf("\n");
            }
        } else {
            printf("%s withdraws %.0f credit.. operation not permitted.\n", 
                   client_name, req.amount);
        }
    }

    if (ok) {
        char op = req.operation==DEPOSIT? 'D' : 'W';
        log_transaction(new_id, op, req.amount, new_bal);
    }

    sem_post(client_empty);

cleanup:
    if (rfd != -1) close(rfd);
    if (client_empty != SEM_FAILED) sem_close(client_empty);
    if (client_full  != SEM_FAILED) sem_close(client_full);
    if (args) free(args);
    return NULL;
}