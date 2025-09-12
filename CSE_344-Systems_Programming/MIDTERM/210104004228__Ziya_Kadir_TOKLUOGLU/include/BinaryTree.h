#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numeric_id;       
    double balance;       
    int is_active;         
} BankAccount;

typedef struct TreeNode {
    int id;                    
    BankAccount account;       
    struct TreeNode *left;     
    struct TreeNode *right;    
    int height;                
} TreeNode;


typedef struct {
    TreeNode *root;            
    int node_count;            
} BinaryTree;

BinaryTree* tree_create();

void tree_destroy(BinaryTree *tree);

BankAccount* tree_find(BinaryTree *tree, int id);

int tree_insert(BinaryTree *tree, int id, BankAccount account);

int tree_insert_auto_id(BinaryTree *tree, BankAccount account);

int tree_delete(BinaryTree *tree, int id);

int tree_size(BinaryTree *tree);

typedef void (*TraversalCallback)(int id, BankAccount *account, void *user_data);

void tree_traverse(BinaryTree *tree, TraversalCallback callback, void *user_data);

#endif /* BINARY_TREE_H */