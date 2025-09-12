#ifndef PARSE_CLIENT_H
#define PARSE_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    DEPOSIT,
    WITHDRAW
} OperationType;

typedef struct {
    char account_id[16];     // Original ID string: "N" or "BankID_XX"
    int numeric_id;          // Extracted numeric ID (0 for invalid or new accounts)
    OperationType operation;
    double amount;
    int is_new_account;      // Flag for new accounts
    int is_valid;            // Flag indicating if the account ID is valid
} ClientRequest;

int parse_client_line(const char *line, ClientRequest *request);

int count_client_operations(const char *filename);

int read_client_file(const char *filename, ClientRequest *requests, int max_requests);

void print_client_request(ClientRequest *request);

#endif 