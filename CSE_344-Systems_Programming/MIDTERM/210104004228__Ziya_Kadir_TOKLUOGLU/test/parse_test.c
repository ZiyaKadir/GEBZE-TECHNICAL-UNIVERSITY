#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

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

// Main function for testing
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <client_file>\n", argv[0]);
        return 1;
    }
    
    const char *filename = argv[1];
    
    // Count operations in the file
    int op_count = count_client_operations(filename);
    if (op_count < 0) {
        printf("Error: Could not open file '%s'\n", filename);
        return 1;
    }
    
    printf("Found %d operations in file '%s'\n", op_count, filename);
    
    // Allocate memory for requests
    ClientRequest *requests = (ClientRequest *)malloc(op_count * sizeof(ClientRequest));
    if (!requests) {
        printf("Error: Memory allocation failed\n");
        return 1;
    }
    
    // Read client file
    int read_count = read_client_file(filename, requests, op_count);
    if (read_count < 0) {
        printf("Error: Failed to read file '%s'\n", filename);
        free(requests);
        return 1;
    }
    
    printf("Successfully read %d operations\n", read_count);
    
    // Print all requests
    printf("\nClient Requests:\n");
    for (int i = 0; i < read_count; i++) {
        printf("Request #%d:\n", i + 1);
        print_client_request(&requests[i]);
    }
    
    free(requests);
    return 0;
}

int parse_client_line(const char *line, ClientRequest *request) {
    char operation_str[20];
    char account_id[16];
    double amount;
    
    // Parse the line format: "[ACCOUNT_ID] [OPERATION] [AMOUNT]"
    int result = sscanf(line, "%s %s %lf", account_id, operation_str, &amount);
    
    if (result != 3) {
        return -1; // Invalid format
    }
    
    // Copy account ID
    strncpy(request->account_id, account_id, sizeof(request->account_id) - 1);
    request->account_id[sizeof(request->account_id) - 1] = '\0';
    
    // Check if this is a new account
    request->is_new_account = (strcmp(account_id, "N") == 0) ? 1 : 0;
    
    // Extract numeric ID for existing accounts
    request->numeric_id = 0; // Default value
    request->is_valid = 0;   // Default to invalid
    
    if (!request->is_new_account) {
        if (strncmp(account_id, "BankID_", 7) == 0) {
            // Try to extract numeric ID after "BankID_"
            char *id_str = account_id + 7; // Point to character after "BankID_"
            
            // Check if the remaining string is a valid number
            int valid = 1;
            for (int i = 0; id_str[i] != '\0'; i++) {
                if (id_str[i] < '0' || id_str[i] > '9') {
                    valid = 0;
                    break;
                }
            }
            
            if (valid && strlen(id_str) > 0) {
                request->numeric_id = atoi(id_str);
                request->is_valid = 1;
            }
        }
    } else {
        // For new accounts, mark as valid
        request->is_valid = 1;
    }
    
    // Parse operation
    if (strcmp(operation_str, "deposit") == 0) {
        request->operation = DEPOSIT;
    } else if (strcmp(operation_str, "withdraw") == 0) {
        request->operation = WITHDRAW;
    } else {
        return -1; // Invalid operation
    }
    
    // Set amount
    request->amount = amount;
    
    return 0; // Success
}



// Count the number of valid operations in a client file using file descriptors
int count_client_operations(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        return -1; // Error opening file
    }
    
    char buffer[4096];
    char line[256];
    int line_pos = 0;
    int count = 0;
    ssize_t bytes_read;
    
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n' || line_pos == sizeof(line) - 1) {
                // End of line reached
                line[line_pos] = '\0';
                
                // Skip empty lines
                if (line_pos > 0) {
                    // Test if line can be parsed
                    ClientRequest dummy_request;
                    if (parse_client_line(line, &dummy_request) == 0) {
                        count++;
                    }
                }
                
                line_pos = 0;
            } else {
                // Add character to current line
                line[line_pos++] = buffer[i];
            }
        }
    }
    
    // Check for the last line if it doesn't end with a newline
    if (line_pos > 0) {
        line[line_pos] = '\0';
        ClientRequest dummy_request;
        if (parse_client_line(line, &dummy_request) == 0) {
            count++;
        }
    }
    
    close(fd);
    return count;
}

// Read all client operations from a file into an array using file descriptors
int read_client_file(const char *filename, ClientRequest *requests, int max_requests) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        return -1; // Error opening file
    }
    
    char buffer[4096];
    char line[256];
    int line_pos = 0;
    int count = 0;
    ssize_t bytes_read;
    
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0 && count < max_requests) {
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n' || line_pos == sizeof(line) - 1) {
                // End of line reached
                line[line_pos] = '\0';
                
                // Skip empty lines
                if (line_pos > 0) {
                    // Parse the line
                    if (parse_client_line(line, &requests[count]) == 0) {
                        count++;
                        if (count >= max_requests) {
                            break;
                        }
                    }
                }
                
                line_pos = 0;
            } else {
                // Add character to current line
                line[line_pos++] = buffer[i];
            }
        }
    }
    
    // Check for the last line if it doesn't end with a newline
    if (line_pos > 0 && count < max_requests) {
        line[line_pos] = '\0';
        if (parse_client_line(line, &requests[count]) == 0) {
            count++;
        }
    }
    
    close(fd);
    return count;
}

// Update the print function to show the new fields
void print_client_request(ClientRequest *request) {
    printf("Account ID: %s\n", request->account_id);
    printf("Numeric ID: %d\n", request->numeric_id);
    printf("Operation: %s\n", request->operation == DEPOSIT ? "deposit" : "withdraw");
    printf("Amount: %.2f\n", request->amount);
    printf("Is New Account: %s\n", request->is_new_account ? "Yes" : "No");
    printf("Is Valid ID: %s\n", request->is_valid ? "Yes" : "No");
    printf("------------------\n");
}