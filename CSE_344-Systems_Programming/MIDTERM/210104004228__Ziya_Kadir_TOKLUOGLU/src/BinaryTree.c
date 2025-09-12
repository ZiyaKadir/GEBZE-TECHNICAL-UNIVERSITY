#include "../include/BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/shm_comm.h"


static int get_height(TreeNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

static int get_balance(TreeNode *node) {
    if (node == NULL) {
        return 0;
    }
    return get_height(node->left) - get_height(node->right);
}

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static TreeNode* create_node(int id, BankAccount account) {
    TreeNode *node = shm_alloc(sizeof(TreeNode));
    if (!node) {
        fprintf(stderr, "Failed to allocate shared node\n");
        return NULL;
    }
 
   
    node->id = id;
    node->account = account;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  
    
    return node;
}

static TreeNode* right_rotate(TreeNode *y) {
    TreeNode *x = y->left;
    TreeNode *T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    
    return x;
}

static TreeNode* left_rotate(TreeNode *x) {
    TreeNode *y = x->right;
    TreeNode *T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    
    return y;
}


int tree_insert_auto_id(BinaryTree *tree, BankAccount account) {
    if (tree == NULL) {
        return -1;  
    }
    
    int id = 1;
    
    while (tree_find(tree, id) != NULL) {
        id++;
    }
    
    account.numeric_id = id;  
    
    int success = tree_insert(tree, id, account);
    
    if (success) {
        return id;  
    } else {
        return -1; 
    }
}



// Recursive function to insert a node into the tree
static TreeNode* insert_node(TreeNode *node, int id, BankAccount account, int *is_new) {
    // 1. Perform standard BST insertion
    if (node == NULL) {
        *is_new = 1;  // Mark as a new insertion
        return create_node(id, account);
    }
    
    if (id < node->id) {
        node->left = insert_node(node->left, id, account, is_new);
    } else if (id > node->id) {
        node->right = insert_node(node->right, id, account, is_new);
    } else {
        // Key already exists, update the account
        node->account = account;
        *is_new = 0;  // Mark as an update
        return node;
    }
    
    // 2. Update height of this ancestor node
    node->height = 1 + max(get_height(node->left), get_height(node->right));
    
    // 3. Get the balance factor to check if this node became unbalanced
    int balance = get_balance(node);
    
    // If unbalanced, there are 4 cases:
    
    // Left Left Case
    if (balance > 1 && id < node->left->id) {
        return right_rotate(node);
    }
    
    // Right Right Case
    if (balance < -1 && id > node->right->id) {
        return left_rotate(node);
    }
    
    // Left Right Case
    if (balance > 1 && id > node->left->id) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    
    // Right Left Case
    if (balance < -1 && id < node->right->id) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    
    // Return the unchanged node pointer
    return node;
}

// Helper function to find the node with the minimum value in a tree
static TreeNode* find_min_node(TreeNode *node) {
    TreeNode *current = node;
    
    // Loop to find the leftmost leaf
    while (current && current->left != NULL) {
        current = current->left;
    }
    
    return current;
}

// Recursive function to delete a node from the tree
static TreeNode* delete_node(TreeNode *root, int id, int *was_deleted) {
    // Base case
    if (root == NULL) {
        *was_deleted = 0;
        return NULL;
    }
    
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (id < root->id) {
        root->left = delete_node(root->left, id, was_deleted);
    }
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (id > root->id) {
        root->right = delete_node(root->right, id, was_deleted);
    }
    // If key is same as root's key, then this is the node to be deleted
    else {
        *was_deleted = 1;  // Mark as deleted
        
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            TreeNode *temp = root->left ? root->left : root->right;
            
            // No child case
            if (temp == NULL) {
                free(root);
                root = NULL;
            } else {
                // One child case
                TreeNode *old_root = root;
                root = temp;
                free(old_root);
            }
        } else {
            // Node with two children: Get the inorder successor
            TreeNode *temp = find_min_node(root->right);
            
            // Store old root data
            TreeNode *old_root = root;
            
            // Create new node with successor's data
            root = create_node(temp->id, temp->account);
            if (root == NULL) {
                root = old_root;  // Restore old root if allocation failed
                *was_deleted = 0;
                return root;
            }
            
            // Copy children from old root
            root->left = old_root->left;
            root->right = old_root->right;
            root->height = old_root->height;
            
            // Delete the inorder successor
            int dummy_was_deleted;
            root->right = delete_node(root->right, temp->id, &dummy_was_deleted);
            
            // Free the old root
            free(old_root);
        }
    }
    
    // If the tree had only one node, return
    if (root == NULL) {
        return NULL;
    }
    
    // Update height of the current node
    root->height = 1 + max(get_height(root->left), get_height(root->right));
    
    // Get the balance factor to check if this node became unbalanced
    int balance = get_balance(root);
    
    // If unbalanced, there are 4 cases:
    
    // Left Left Case
    if (balance > 1 && get_balance(root->left) >= 0) {
        return right_rotate(root);
    }
    
    // Left Right Case
    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    
    // Right Right Case
    if (balance < -1 && get_balance(root->right) <= 0) {
        return left_rotate(root);
    }
    
    // Right Left Case
    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    
    return root;
}

// Recursive function to find a node in the tree
static BankAccount* find_node(TreeNode *root, int id) {
    if (root == NULL) {
        return NULL;
    }
    
    if (id == root->id) {
        return &(root->account);
    }
    
    if (id < root->id) {
        return find_node(root->left, id);
    } else {
        return find_node(root->right, id);
    }
}

// Recursive function to free the entire tree
static void free_tree_nodes(TreeNode *root) {
    if (root != NULL) {
        free_tree_nodes(root->left);
        free_tree_nodes(root->right);
        free(root);
    }
}

// Recursive function to perform in-order traversal
static void inorder_traversal(TreeNode *root, TraversalCallback callback, void *user_data) {
    if (root != NULL) {
        inorder_traversal(root->left, callback, user_data);
        callback(root->id, &(root->account), user_data);
        inorder_traversal(root->right, callback, user_data);
    }
}

// Public API implementations

// Create a new binary tree
BinaryTree* tree_create() {
    BinaryTree *tree = (BinaryTree*)shm_alloc(sizeof(BinaryTree));
    if (tree == NULL) {
        return NULL;
    }
    
    tree->root = NULL;
    tree->node_count = 0;
    
    return tree;
}

// Destroy a binary tree and free all associated memory
void tree_destroy(BinaryTree *tree) {
    if (tree != NULL) {
        free_tree_nodes(tree->root);
        free(tree);
    }
}

// Find an account by ID
BankAccount* tree_find(BinaryTree *tree, int id) {
    if (tree == NULL) {
        return NULL;
    }
    
    return find_node(tree->root, id);
}

// Insert or update an account
int tree_insert(BinaryTree *tree, int id, BankAccount account) {
    if (tree == NULL) {
        return 0;
    }
    
    int is_new = 0;
    tree->root = insert_node(tree->root, id, account, &is_new);
    
    if (is_new) {
        tree->node_count++;
    }
    
    return is_new;
}



// Delete an account
int tree_delete(BinaryTree *tree, int id) {
    if (tree == NULL) {
        return 0;
    }
    
    int was_deleted = 0;
    tree->root = delete_node(tree->root, id, &was_deleted);
    
    if (was_deleted) {
        tree->node_count--;
    }
    
    return was_deleted;
}

// Get the number of accounts
int tree_size(BinaryTree *tree) {
    if (tree == NULL) {
        return 0;
    }
    
    return tree->node_count;
}

// Traverse the tree in-order
void tree_traverse(BinaryTree *tree, TraversalCallback callback, void *user_data) {
    if (tree == NULL || callback == NULL) {
        return;
    }
    
    inorder_traversal(tree->root, callback, user_data);
}