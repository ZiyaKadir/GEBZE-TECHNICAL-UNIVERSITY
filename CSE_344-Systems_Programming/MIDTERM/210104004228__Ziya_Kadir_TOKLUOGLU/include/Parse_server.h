#ifndef PARSE_SERVER_H
#define PARSE_SERVER_H

#include "BinaryTree.h"

void print_account(int id, BankAccount *account, void *user_data);

int parse_account_line(char *line, int *id, double *balance);

int load_accounts_from_csv(const char *filename, BinaryTree *tree);

int save_accounts_to_csv(const char *filename, BinaryTree *tree, const char *bank_name);

int process_deposit(BinaryTree *tree, int account_id, double amount, int is_new_account, 
                   int *new_account_id, double *new_balance, char *message, int message_size);

int process_withdraw(BinaryTree *tree, int account_id, double amount, 
                    double *new_balance, char *message, int message_size);

void save_account_to_file(int id, BankAccount *account, void *user_data);

#endif