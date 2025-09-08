#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * @brief Node structure for linked list
 */
struct node {
    char bookname[30];
    char author[30];
    int year;
    struct node *next;
};

/**
 * @brief Inserts a new node in ascending order by year
 * @param root Current root of the linked list
 * @param bookname Name of the book
 * @param author Author of the book
 * @param year Publication year
 * @return Updated root of the linked list
 */
struct node* insert_node(struct node *root, char *bookname, char *author, int year) {
    // Create new node
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    if(new_node == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    strcpy(new_node->bookname, bookname);
    strcpy(new_node->author, author);
    new_node->year = year;
    new_node->next = NULL;
    
    // Case 1: If there is no node in the list (if root is NULL)
    if(root == NULL) {
        return new_node;
    }
    
    // Case 2: If there is at least one node in the list, create a new node with the incoming data
    // and check if this node should be added to left side of the list
    if(new_node->year < root->year) {
        new_node->next = root;
        return new_node;
    }
    
    // Case 3: If above two doesn't hold, create a new node with incoming data
    // Use a loop to find the correct place for new node and insert it
    struct node *current = root;
    while(current->next != NULL && current->next->year < new_node->year) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    
    return root;
}

/**
 * @brief Reads book data from source.txt file and creates linked list
 * @return Root of the created linked list
 */
struct node* read_file() {
    FILE *file = fopen("source.txt", "r");
    if(file == NULL) {
        printf("Error: Cannot open source.txt file\n");
        exit(1);
    }
    
    struct node *root = NULL;
    char bookname[30], author[30];
    int year;
    
    // Read each line and insert into linked list
    while(fscanf(file, "%s %s %d", bookname, author, &year) == 3) {
        root = insert_node(root, bookname, author, year);
    }
    
    fclose(file);
    return root;
}

/**
 * @brief Prints the entire linked list
 * @param root Root of the linked list
 */
void print_nodes(struct node *root) {
    printf("Printing the linked list...\n");
    
    struct node *current = root;
    while(current != NULL) {
        printf("%-15s %-15s %d\n", current->bookname, current->author, current->year);
        current = current->next;
    }
    printf("\n");
}

/**
 * @brief Deletes a node with the specified book name
 * @param root Current root of the linked list
 * @param bookname Name of the book to delete
 * @return Updated root of the linked list
 */
struct node* delete_node(struct node *root, char *bookname) {
    if(root == NULL) {
        return NULL;
    }
    
    // Case 1: If the root itself is the node you are looking for
    if(strcmp(root->bookname, bookname) == 0) {
        struct node *temp = root;
        root = root->next;
        free(temp);
        printf("%s has been deleted.\n", bookname);
        return root;
    }
    
    // Case 2: If the root is not what we are looking for, use a loop to find this node in the list
    struct node *current = root;
    while(current->next != NULL) {
        if(strcmp(current->next->bookname, bookname) == 0) {
            struct node *temp = current->next;
            current->next = current->next->next;
            free(temp);
            printf("%s has been deleted.\n", bookname);
            return root;
        }
        current = current->next;
    }
    
    // Book not found
    printf("%s is not in the list.\n", bookname);
    return root;
}

/**
 * @brief Creates a sample source.txt file for testing
 */
void create_sample_file() {
    FILE *file = fopen("source.txt", "w");
    if(file == NULL) {
        printf("Error creating sample file\n");
        return;
    }
    
    fprintf(file, "MrsDalloway VirginiaWoolf 1925\n");
    fprintf(file, "MobyDick HermanMelville 1851\n");
    fprintf(file, "WarAndPeace LeoTolstoy 1869\n");
    fprintf(file, "TheStranger AlbertCamus 1942\n");
    fprintf(file, "EastOfEden JohnSteinbeck 1952\n");
    
    fclose(file);
}

/**
 * @brief Frees all nodes in the linked list
 * @param root Root of the linked list
 */
void free_list(struct node *root) {
    struct node *current = root;
    while(current != NULL) {
        struct node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct node *root = NULL;
    
    // create_sample_file();
    
    printf("Reading the source.txt file...\n");
    
    root = read_file();
    
    print_nodes(root);
    
    int choice;
    char book_to_delete[30];
    
    while(1) {
        printf("\n=== MENU ===\n");
        printf("1. Delete a book\n");
        printf("2. Print current list\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Which book do you want to delete? ");
                scanf("%s", book_to_delete);
                root = delete_node(root, book_to_delete);
                break;
                
            case 2:
                print_nodes(root);
                break;
                
            case 3:
                printf("Exiting program...\n");
                // Free all allocated memory before exit
                free_list(root);
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }
}