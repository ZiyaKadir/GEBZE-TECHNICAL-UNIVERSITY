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

int main() {
    BinaryTree *tree = tree_create();
    if (tree == NULL) {
        fprintf(stderr, "Failed to create account tree\n");
        return 1;
    }
    
    printf("Testing database parsing and account management\n\n");
    
    // Load accounts from CSV
    const char *filename = "../ClientFolder/DATABASE.csv";
    int loaded = load_accounts_from_csv(filename, tree);
    if (loaded < 0) {
        fprintf(stderr, "Failed to load accounts from %s\n", filename);
        tree_destroy(tree);
        return 1;
    }
    
    printf("Loaded %d accounts from %s\n", loaded, filename);
    printf("Current tree size: %d\n\n", tree_size(tree));
    
    // Print all accounts
    printf("Current accounts:\n");
    tree_traverse(tree, print_account, NULL);
    printf("\n");
    
    // Test account operations
    printf("Performing account operations:\n");
    
    // 1. Find and print an account
    int test_id = 3;
    BankAccount *found = tree_find(tree, test_id);
    if (found) {
        printf("Account BankID_%d found: Balance %.2f\n", test_id, found->balance);
        
        // 2. Deposit to the account
        double deposit_amount = 250.0;
        found->balance += deposit_amount;
        printf("Deposited %.2f to BankID_%d, new balance: %.2f\n", 
               deposit_amount, test_id, found->balance);
    } else {
        printf("Account BankID_%d not found\n", test_id);
    }
    
    // 3. Add a new account
    BankAccount new_account = {0, 800.0, 1};
    int new_id = tree_insert_auto_id(tree, new_account);
    printf("Created new account BankID_%d with initial balance %.2f\n", 
           new_id, new_account.balance);
    
    // 4. Close an account
    test_id = 2;
    found = tree_find(tree, test_id);
    if (found) {
        printf("Closing account BankID_%d with balance %.2f\n", test_id, found->balance);
        found->is_active = 0;
        tree_delete(tree, test_id);
    }
    
    printf("\nFinal tree size: %d\n", tree_size(tree));
    printf("Final accounts:\n");
    tree_traverse(tree, print_account, NULL);
    printf("\n");
    
    // Save updated accounts back to CSV
    const char *updated_filename = "DATABASE_updated.csv";
    if (save_accounts_to_csv(updated_filename, tree, "AdaBank") == 0) {
        printf("Saved updated accounts to %s\n", updated_filename);
    } else {
        fprintf(stderr, "Failed to save accounts to %s\n", updated_filename);
    }
    
    // Clean up
    tree_destroy(tree);
    printf("Test completed!\n");
    
    return 0;
}