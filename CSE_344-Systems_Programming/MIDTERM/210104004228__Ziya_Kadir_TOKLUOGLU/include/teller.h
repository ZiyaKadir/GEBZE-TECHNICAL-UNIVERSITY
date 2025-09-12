#ifndef TELLER_H
#define TELLER_H

#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include "../include/BinaryTree.h"
#include "Parse_client.h"


typedef struct {
    char client_fifo[64];       // Client FIFO path
    char sem_empty_name[64];    // Semaphore name for empty buffer
    char sem_full_name[64];     // Semaphore name for full buffer
    BinaryTree *db;             // Pointer to shared binary tree
} TellerArgs;

pid_t Teller(void *(*func)(void *), void *arg_func);

void *process_client_request(void *arg);

int waitTeller(pid_t pid, int* status);

#endif 