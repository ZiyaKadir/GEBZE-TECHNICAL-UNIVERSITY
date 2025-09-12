#include "../include/BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>

// Callback function for traversal
void print_account(int id, BankAccount *account, void *user_data) {
    printf("Account ID: %d, Balance: %.2f, Active: %d\n", 
           id, account->balance, account->is_active);
}

int main() {
    // Create a new tree
    BinaryTree *tree = tree_create();
    if (tree == NULL) {
        printf("Failed to create tree\n");
        return 1;
    }
    
    printf("Testing binary tree with auto ID assignment...\n\n");
    
    // Create some test accounts (without IDs - they'll be auto-assigned)
    BankAccount acc1 = {0, 100.0, 1};  // ID field ignored for auto-assignment
    BankAccount acc2 = {0, 200.0, 1};
    BankAccount acc3 = {0, 300.0, 1};
    BankAccount acc4 = {0, 400.0, 1};
    BankAccount acc5 = {0, 500.0, 1};
    
    // Test insertion with auto ID assignment
    printf("Inserting accounts with auto ID assignment...\n");
    int id1 = tree_insert_auto_id(tree, acc1);
    int id2 = tree_insert_auto_id(tree, acc2);
    int id3 = tree_insert_auto_id(tree, acc3);
    int id4 = tree_insert_auto_id(tree, acc4);
    int id5 = tree_insert_auto_id(tree, acc5);
    
    printf("Assigned IDs: %d, %d, %d, %d, %d\n", id1, id2, id3, id4, id5);
    printf("Tree size: %d\n\n", tree_size(tree));
    
    // Test traversal
    printf("Tree contents (in-order traversal):\n");
    tree_traverse(tree, print_account, NULL);
    printf("\n");
    
    // Test finding
    printf("Looking up account ID %d...\n", id3);
    BankAccount *found = tree_find(tree, id3);
    if (found) {
        printf("Found! Balance: %.2f\n\n", found->balance);
    } else {
        printf("Not found!\n\n");
    }
    
    // Test deleting
    printf("Deleting account ID %d...\n", id3);
    int deleted = tree_delete(tree, id3);
    printf("Deletion %s\n", deleted ? "successful" : "failed");
    printf("Tree size: %d\n\n", tree_size(tree));
    
    // Test inserting a new account after deletion
    printf("Inserting a new account after deletion...\n");
    BankAccount new_acc = {0, 600.0, 1};
    int new_id = tree_insert_auto_id(tree, new_acc);
    printf("New account assigned ID: %d (should reuse the deleted ID %d)\n\n", new_id, id3);
    
    // Verify reused ID
    found = tree_find(tree, new_id);
    if (found) {
        printf("Found account with ID %d! Balance: %.2f\n\n", new_id, found->balance);
    } else {
        printf("Not found!\n\n");
    }
    
    // Check remaining tree structure
    printf("Final tree contents:\n");
    tree_traverse(tree, print_account, NULL);
    printf("\n");
    
    // Clean up
    printf("Destroying tree...\n");
    tree_destroy(tree);
    printf("Test completed!\n");
    
    return 0;
}