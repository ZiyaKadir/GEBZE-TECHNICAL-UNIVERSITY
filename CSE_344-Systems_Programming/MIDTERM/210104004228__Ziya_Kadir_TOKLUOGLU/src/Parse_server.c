#include "../include/BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
#define MAX_LINE_LENGTH 256

// Callback function for traversal - prints account information
void print_account(int id, BankAccount *account, void *user_data) {
    printf("BankID_%d, Balance: %.2f, Active: %d\n", 
           id, account->balance, account->is_active);
}

// Parse a single line from the CSV file
int parse_account_line(char *line, int *id, double *balance) {
    char *token;
    
    // Get account ID
    token = strtok(line, ",");
    if (token == NULL) return 0;
    *id = atoi(token);
    
    // Get balance
    token = strtok(NULL, ",");
    if (token == NULL) return 0;
    *balance = atof(token);
    
    return 1;
}

// Load accounts from CSV file into the binary tree
int load_accounts_from_csv(const char *filename, BinaryTree *tree) {
    int fd, bytes_read, line_count = 0;
    char buffer[BUFFER_SIZE], line[MAX_LINE_LENGTH];
    int pos = 0, id;
    double balance;
    int header_skipped = 0;
    
    // Open the file
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open database file");
        return -1;
    }
    
    // Read the file
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n') {
                // End of line, process it
                line[pos] = '\0';
                pos = 0;
                
                // Skip header lines (first two lines)
                if (!header_skipped) {
                    line_count++;
                    if (line_count >= 2) {
                        header_skipped = 1;
                    }
                    continue;
                }
                
                // Parse the line and insert into tree
                if (parse_account_line(line, &id, &balance)) {
                    BankAccount account = {id, balance, 1}; // All accounts are active initially
                    tree_insert(tree, id, account);
                    line_count++;
                }
            } else if (pos < MAX_LINE_LENGTH - 1) {
                // Add character to current line
                line[pos++] = buffer[i];
            }
        }
    }
    
    // Handle last line if it doesn't end with newline
    if (pos > 0) {
        line[pos] = '\0';
        if (header_skipped && parse_account_line(line, &id, &balance)) {
            BankAccount account = {id, balance, 1};
            tree_insert(tree, id, account);
            line_count++;
        }
    }
    
    // Close the file
    close(fd);
    
    // Return number of accounts loaded (excluding header lines)
    return line_count - 2;
}

// Save accounts from binary tree to CSV file
void save_account_to_file(int id, BankAccount *account, void *user_data) {
    int fd = *((int*)user_data);
    char line[MAX_LINE_LENGTH];
    
    // Only write active accounts
    if (account->is_active) {
        // Format: AccountID,Balance
        snprintf(line, MAX_LINE_LENGTH, "%d,%.2f\n", id, account->balance);
        
        // Write to file
        write(fd, line, strlen(line));
    }
}

int save_accounts_to_csv(const char *filename, BinaryTree *tree, const char *bank_name) {
    int fd;
    char header[MAX_LINE_LENGTH];
    
    // Open the file
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to open database file for writing");
        return -1;
    }
    
    // Write bank name header
    snprintf(header, MAX_LINE_LENGTH, "%s DATABASE\n", bank_name);
    write(fd, header, strlen(header));
    
    // Write column headers
    strcpy(header, "AccountID,Balance\n");
    write(fd, header, strlen(header));
    
    // Traverse tree and write each account
    tree_traverse(tree, save_account_to_file, &fd);
    
    // Close the file
    close(fd);
    
    return 0;
}

// Process a deposit operation
int process_deposit(BinaryTree *tree, int account_id, double amount, int is_new_account, 
    int *new_account_id, double *new_balance, char *message, int message_size) {
if (amount <= 0) {
snprintf(message, message_size, "Deposit amount must be positive");
return 0;  // Failure
}

if (is_new_account) {
// Create a new account with the specified amount
BankAccount new_account = {0, amount, 1};  // ID will be set by tree_insert_auto_id

// Insert with auto-assigned ID
*new_account_id = tree_insert_auto_id(tree, new_account);
if (*new_account_id <= 0) {
snprintf(message, message_size, "Failed to create new account");
return 0;  // Failure
}

*new_balance = amount;
snprintf(message, message_size, "New account created with ID: BankID_%d", *new_account_id);
return 1;  // Success
} else {
// Find existing account
BankAccount *account = tree_find(tree, account_id);
if (account == NULL || !account->is_active) {
snprintf(message, message_size, "Account not found or inactive");
return 0;  // Failure
}

// Update balance
account->balance += amount;
*new_balance = account->balance;
*new_account_id = account_id;

snprintf(message, message_size, "Deposit successful. New balance: %.2f", *new_balance);
return 1;  // Success
}
}

// Process a withdrawal operation
int process_withdraw(BinaryTree *tree, int account_id, double amount, 
     double *new_balance, char *message, int message_size) {
if (amount <= 0) {
snprintf(message, message_size, "Withdrawal amount must be positive");
return 0;  // Failure
}

// Find existing account
BankAccount *account = tree_find(tree, account_id);
if (account == NULL || !account->is_active) {
snprintf(message, message_size, "Account not found or inactive");
return 0;  // Failure
}

// Check if sufficient balance
if (account->balance < amount) {
snprintf(message, message_size, "Insufficient funds. Current balance: %.2f", account->balance);
return 0;  // Failure
}

// Update balance
account->balance -= amount;
*new_balance = account->balance;

// Check if account should be closed (balance is zero)
if (*new_balance == 0) {
account->is_active = 0;  // Mark as inactive
snprintf(message, message_size, "Withdrawal successful. Account closed.");
} else {
snprintf(message, message_size, "Withdrawal successful. New balance: %.2f", *new_balance);
}

return 1;  // Success
}