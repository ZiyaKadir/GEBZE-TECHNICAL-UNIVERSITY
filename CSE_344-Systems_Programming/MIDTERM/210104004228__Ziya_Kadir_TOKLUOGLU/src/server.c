// src/server.c
#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "../include/BinaryTree.h"
#include "../include/Parse_server.h"
#include "../include/IPC_communication.h"
#include "../include/teller.h"
#include "../include/shm_comm.h"  
#include "../include/helper_log.h"

#define SEM_EMPTY  "/bank_fifo_empty"   // client may write
#define SEM_FULL   "/bank_fifo_full"    // server may read

volatile sig_atomic_t termination_requested = 0;
BinaryTree *shared_db;              // ← now in shared memory

static void server_signal_handler(int signo) {
    if (signo == SIGINT || signo == SIGTERM) {
        termination_requested = 1;
        const char *msg = "Shutdown requested; finishing...\n";
        write(STDERR_FILENO, msg, strlen(msg));
    }
    else if (signo == SIGCHLD) {
        while (waitpid(-1, NULL, WNOHANG) > 0) {}
    }
}

static void setup_server_signal_handlers(void)
{
    /* SIGINT  & SIGTERM  → interrupt syscalls so main-loop notices */
    struct sigaction sa_int = {0};
    sa_int.sa_handler = server_signal_handler;
    sigfillset(&sa_int.sa_mask);          /* no SA_RESTART here           */
    sigaction(SIGINT,  &sa_int, NULL);
    sigaction(SIGTERM, &sa_int, NULL);

    /* SIGCHLD → we WANT auto-restart so children don't abort open()/read() */
    struct sigaction sa_chld = {0};
    sa_chld.sa_handler = server_signal_handler;
    sa_chld.sa_flags   = SA_RESTART;      /* only for SIGCHLD             */
    sigfillset(&sa_chld.sa_mask);
    sigaction(SIGCHLD, &sa_chld, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <bank_name> <server_fifo>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *bank_name = argv[1];
    const char *fifo_name = argv[2];
    char db_file[256];
    
    snprintf(db_file, sizeof(db_file), "%s.db", bank_name);

    init_shared_memory();
    shared_db = tree_create();
    if (!shared_db) {
        fprintf(stderr, "tree_create() failed\n");
        cleanup_shared_memory();
        return EXIT_FAILURE;
    }

    log_init(db_file);

    printf("%s is active....\n", bank_name);
    
    struct stat st;
    if (stat(db_file, &st) == 0) {
        printf("Loading existing bank database...\n");
        load_accounts_from_csv(db_file, shared_db);
        // Keep this silent per PDF format
    } else {
        printf("No previous logs.. Creating the bank database\n");
        save_accounts_to_csv(db_file, shared_db, bank_name);
    }

    setup_server_signal_handlers();

    sem_t *empty = sem_open(SEM_EMPTY,
                            O_CREAT | O_EXCL, 0666,
                            1);
    if (empty == SEM_FAILED && errno == EEXIST)
        empty = sem_open(SEM_EMPTY, 0);

    sem_t *full = sem_open(SEM_FULL,
                           O_CREAT | O_EXCL, 0666,
                           0);
    if (full == SEM_FAILED && errno == EEXIST)
        full = sem_open(SEM_FULL, 0);

    if (empty == SEM_FAILED || full == SEM_FAILED) {
        perror("sem_open");
        tree_destroy(shared_db);
        cleanup_shared_memory();
        return EXIT_FAILURE;
    }

    if (create_fifo(fifo_name) < 0) {
        fprintf(stderr, "create_fifo(%s) failed\n", fifo_name);
        goto cleanup;
    }

    printf("Waiting for clients @%s...\n", fifo_name);

    TellerArgs *targs = malloc(sizeof(*targs));

    while (!termination_requested) {
        int srv_fd = open_fifo_read(fifo_name);
        if (srv_fd < 0) break;

        if (sem_wait(full) == -1) {
            if (errno == EINTR) {
                close_fifo(srv_fd);
                continue;
            }
            perror("sem_wait(full)");
            close_fifo(srv_fd);
            break;
        }

        ClientCommunication comm;
        ssize_t bytes_read = read_from_fifo(srv_fd, &comm, sizeof(comm));
        close_fifo(srv_fd);

        if (bytes_read != sizeof(comm)) {
            perror("read_from_fifo (comm)");
            sem_post(empty);
            continue;
        }

        printf("- Received %d clients from PID%d..\n", comm.request_number, comm.client_pid);

        for (int i = 0; i < comm.request_number; i++) {
            if (!targs) {
                perror("malloc TellerArgs");
                continue;
            }
            strncpy(targs->client_fifo,    comm.client_fifo,
                    sizeof targs->client_fifo);
            strncpy(targs->sem_empty_name, comm.sem_empty_name,
                    sizeof targs->sem_empty_name);
            strncpy(targs->sem_full_name,  comm.sem_full_name,
                    sizeof targs->sem_full_name);

            pid_t teller_pid = Teller((void*(*)(void*))process_client_request,
                                      targs);
            if (teller_pid < 0) {
                fprintf(stderr,
                        "Failed to spawn Teller for request %d\n", i);
                free(targs);
            } else {
                printf("-- Teller PID%d is active serving Client%02d...\n",
                       teller_pid, i+1);
            }

            waitTeller(teller_pid, NULL);
        }

        sem_post(empty);
        
        printf("Waiting for clients @%s...\n", fifo_name);
    }

    printf("Signal received closing active Tellers\n");
    printf("Removing %s... Updating log file...\n", fifo_name);
    log_close();
    save_accounts_to_csv(db_file, shared_db, bank_name);

    remove_fifo(fifo_name);
    printf("%s says \"Bye\"...\n", bank_name);

cleanup:
    free(targs);
    sem_close(empty);
    sem_close(full);
    sem_unlink(SEM_EMPTY);
    sem_unlink(SEM_FULL);

    cleanup_shared_memory();

    return EXIT_SUCCESS;
}