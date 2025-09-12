#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>

#include "../include/Parse_client.h"
#include "../include/IPC_communication.h"

volatile sig_atomic_t termination_requested = 0;

static void client_signal_handler(int signo) {
    if (signo == SIGINT || signo == SIGTERM) {
        termination_requested = 1;
        const char *msg = "Termination requested; finishing outstanding...\n";
        write(STDERR_FILENO, msg, strlen(msg));
    }
}

static void setup_client_signal_handlers(void) {
    struct sigaction sa = { .sa_handler = client_signal_handler };
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT,  &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <client_file> <server_fifo>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *client_file = argv[1];
    const char *server_fifo = argv[2];

    /* Build names */
    char client_fifo[64];
    get_client_fifo_name(client_fifo, sizeof client_fifo, getpid());

    char sem_empty_name[64], sem_full_name[64];
    get_client_sem_names(sem_empty_name, sem_full_name,
                         sizeof sem_empty_name, getpid());

    // Modified output format
    printf("Reading %s..\n", client_file);

    /* Create FIFO */
    if (create_fifo(client_fifo) < 0) {
        perror("create_fifo (client)");
        return EXIT_FAILURE;
    }

    /* Keep one reader open to prevent ENXIO */
    int init_fd = open(client_fifo, O_RDWR);
    if (init_fd == -1) {
        perror("open O_RDWR (client_fifo)");
        remove_fifo(client_fifo);
        return EXIT_FAILURE;
    }

    setup_client_signal_handlers();

    // Remove debug output about semaphores
    sem_t *client_empty = sem_open(sem_empty_name, O_CREAT | O_EXCL, 0666, 1);
    sem_t *client_full  = sem_open(sem_full_name,  O_CREAT | O_EXCL, 0666, 0);

    if (client_empty == SEM_FAILED || client_full == SEM_FAILED) {
        perror("sem_open (client)");
        close(init_fd);
        remove_fifo(client_fifo);
        return EXIT_FAILURE;
    }

    /* Parse requests */
    int num_requests = count_client_operations(client_file);
    if (num_requests <= 0) {
        fprintf(stderr, "No operations in %s\n", client_file);
        goto cleanup;
    }
    
    printf("%d clients to connect.. creating clients..\n", num_requests);
    
    ClientRequest *reqs = malloc(num_requests * sizeof *reqs);
    if (!reqs) { perror("malloc"); goto cleanup; }
    if (read_client_file(client_file, reqs, num_requests) != num_requests) {
        fprintf(stderr, "read_client_file failed\n");
        goto cleanup;
    }

    /* Send ClientCommunication to server */
    sem_t *empty = sem_open("/bank_fifo_empty", 0);
    sem_t *full  = sem_open("/bank_fifo_full",  0);
    if (empty == SEM_FAILED || full == SEM_FAILED) {
        perror("sem_open (server)");
        goto cleanup;
    }

    sem_wait(empty);
    int sfd = open_fifo_write(server_fifo);
    if (sfd == -1) { 
        sem_post(empty); 
        printf("Cannot connect %s...\n", server_fifo);
        printf("exiting..\n");
        goto cleanup; 
    }

    printf("Connected to Adabank..\n");

    ClientCommunication cc = { .client_pid = getpid(), .request_number = num_requests };
    strncpy(cc.client_fifo, client_fifo, sizeof cc.client_fifo);
    strncpy(cc.sem_empty_name, sem_empty_name, sizeof cc.sem_empty_name);
    strncpy(cc.sem_full_name, sem_full_name, sizeof cc.sem_full_name);

    if (write_to_fifo(sfd, &cc, sizeof cc) != sizeof cc) {
        perror("write ClientCommunication");
        close_fifo(sfd);
        sem_post(empty);
        goto cleanup;
    }
    close_fifo(sfd);
    sem_post(full);

    for (int i = 0; i < num_requests && !termination_requested; ++i) {
        // Print client connection messages per PDF format
        printf("Client%02d connected..%s %0.f credits\n", 
               i+1, 
               reqs[i].operation == DEPOSIT ? "depositing" : "withdrawing",
               reqs[i].amount);
        
        while (sem_wait(client_empty) == -1 && errno == EINTR) {}
        int wfd;
        while ((wfd = open(client_fifo, O_WRONLY | O_NONBLOCK)) == -1 && errno == EINTR) {}
        
        if (wfd == -1) { perror("open client_fifo"); sem_post(client_empty); break; }
        
        int flags = fcntl(wfd, F_GETFL);
        
        fcntl(wfd, F_SETFL, flags & ~O_NONBLOCK);
        
        if (write(wfd, &i, sizeof i) != sizeof i ||
            write(wfd, &reqs[i], sizeof reqs[i]) != sizeof reqs[i]) {
            perror("write request"); close(wfd); sem_post(client_empty); break;
        }
        
        close(wfd);
        
        sem_post(client_full);
    }

    // Wait for a moment to collect results
    sleep(2);
    

cleanup:
    close(init_fd);

    if (client_empty != SEM_FAILED) { 
        sem_close(client_empty); 
        sem_unlink(sem_empty_name); 
    }
    if (client_full != SEM_FAILED) { 
        sem_close(client_full);  
        sem_unlink(sem_full_name); 
    }

    if (empty != SEM_FAILED) { 
        sem_close(empty);
    }
    if (full != SEM_FAILED) { 
        sem_close(full);
    }
    remove_fifo(client_fifo);
    free(reqs);
    return EXIT_SUCCESS;
}