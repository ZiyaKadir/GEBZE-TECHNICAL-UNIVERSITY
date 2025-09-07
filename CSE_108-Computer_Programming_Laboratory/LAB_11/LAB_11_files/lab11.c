#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Book {
    char title[200];
    char author[200];
    char subject[200];
    int book_id;
    int year;
};

struct Book *books = NULL;
int book_count = 0;
int capacity = 10;

void initialize_library() {
    books = (struct Book*)malloc(capacity * sizeof(struct Book));
    if(books == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

void expand_library() {
    capacity *= 2;
    books = (struct Book*)realloc(books, capacity * sizeof(struct Book));
    if(books == NULL) {
        printf("Memory reallocation failed!\n");
        exit(1);
    }
}

void add_new_book() {
    if(book_count >= capacity) {
        expand_library();
    }
    
    printf("Choose = 1\n");
    printf("*******************\n");
    
    printf("Please enter book title = ");
    while(getchar() != '\n');
    scanf("%[^\n]%*c", books[book_count].title);
    
    printf("Please enter book author = ");
    while(getchar() != '\n');
    scanf("%[^\n]%*c", books[book_count].author);
    
    printf("Please enter book subject = ");
    while(getchar() != '\n');
    scanf("%[^\n]%*c", books[book_count].subject);
    
    printf("Please enter book year = ");
    scanf("%d", &books[book_count].year);
    
    books[book_count].book_id = book_count + 1;
    book_count++;
    
    printf("*******************\n");
}

void search_by_title() {
    char search_title[200];
    printf("Choose = 1\n");
    printf("*******************\n");
    printf("Enter a book title = ");
    
    while(getchar() != '\n'); // Clear buffer
    fgets(search_title, sizeof(search_title), stdin);
    search_title[strcspn(search_title, "\n")] = 0; // Remove newline
    
    for(int i = 0; i < book_count; i++) {
        if(strcmp(books[i].title, search_title) == 0) {
            printf("Book Found\n");
            printf("Title => %s\n", books[i].title);
            printf("Author => %s\n", books[i].author);
            printf("Subject => %s\n", books[i].subject);
            printf("Year => %d\n", books[i].year);
            printf("*******************\n");
            return;
        }
    }
    printf("Book not found!\n");
    printf("*******************\n");
}

void search_by_author() {
    char search_author[200];
    printf("Choose = 2\n");
    printf("*******************\n");
    printf("Enter a book Author = ");
    
    while(getchar() != '\n'); // Clear buffer
    fgets(search_author, sizeof(search_author), stdin);
    search_author[strcspn(search_author, "\n")] = 0; // Remove newline
    
    for(int i = 0; i < book_count; i++) {
        if(strcmp(books[i].author, search_author) == 0) {
            printf("Book Found\n");
            printf("Title => %s\n", books[i].title);
            printf("Author => %s\n", books[i].author);
            printf("Subject => %s\n", books[i].subject);
            printf("Year => %d\n", books[i].year);
            printf("*******************\n");
            return;
        }
    }
    printf("Book not found!\n");
    printf("*******************\n");
}

void search_by_subject() {
    char search_subject[200];
    printf("Choose = 3\n");
    printf("*******************\n");
    printf("Enter a book Subject = ");
    
    while(getchar() != '\n'); // Clear buffer
    fgets(search_subject, sizeof(search_subject), stdin);
    search_subject[strcspn(search_subject, "\n")] = 0; // Remove newline
    
    for(int i = 0; i < book_count; i++) {
        if(strcmp(books[i].subject, search_subject) == 0) {
            printf("Book Found\n");
            printf("Title => %s\n", books[i].title);
            printf("Author => %s\n", books[i].author);
            printf("Subject => %s\n", books[i].subject);
            printf("Year => %d\n", books[i].year);
            printf("*******************\n");
            return;
        }
    }
    printf("Book not found!\n");
    printf("*******************\n");
}

void sort_books_by_year() {
    struct Book temp_books[1000];
    for(int i = 0; i < book_count; i++) {
        temp_books[i] = books[i];
    }
    
    for(int i = 0; i < book_count - 1; i++) {
        for(int j = 0; j < book_count - i - 1; j++) {
            if(temp_books[j].year < temp_books[j + 1].year) {
                struct Book temp = temp_books[j];
                temp_books[j] = temp_books[j + 1];
                temp_books[j + 1] = temp;
            }
        }
    }
    
    printf("Choose = 4\n");
    printf("*******************\n");
    printf("List of Books\n");
    printf("*******************\n");
    
    for(int i = 0; i < book_count; i++) {
        printf("%d. Book:\n", i + 1);
        printf("Title => %s\n", temp_books[i].title);
        printf("Author => %s\n", temp_books[i].author);
        printf("Subject => %s\n", temp_books[i].subject);
        printf("Year => %d\n", temp_books[i].year);
        printf("*******************\n");
    }
}

void list_all_books() {
    struct Book temp_books[1000];
    for(int i = 0; i < book_count; i++) {
        temp_books[i] = books[i];
    }
    
    for(int i = 0; i < book_count - 1; i++) {
        for(int j = 0; j < book_count - i - 1; j++) {
            if(temp_books[j].book_id > temp_books[j + 1].book_id) {
                struct Book temp = temp_books[j];
                temp_books[j] = temp_books[j + 1];
                temp_books[j + 1] = temp;
            }
        }
    }
    
    printf("Choose = 5\n");
    printf("*******************\n");
    printf("List of Books\n");
    printf("*******************\n");
    
    for(int i = 0; i < book_count; i++) {
        printf("%d. Book:\n", i + 1);
        printf("Title => %s\n", temp_books[i].title);
        printf("Author => %s\n", temp_books[i].author);
        printf("Subject => %s\n", temp_books[i].subject);
        printf("Year => %d\n", temp_books[i].year);
        printf("*******************\n");
    }
}

void submenu() {
    int choice;
    
    while(1) {
        printf("SUBMENU\n");
        printf("1. Get by Title\n");
        printf("2. Get by Author\n");
        printf("3. Get by Subject\n");
        printf("4. Sorted List by Year (DESC)\n");
        printf("5. List All Books\n");
        printf("6. EXIT SUBMENU\n");
        printf("Choose = ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                search_by_title();
                break;
            case 2:
                search_by_author();
                break;
            case 3:
                search_by_subject();
                break;
            case 4:
                sort_books_by_year();
                break;
            case 5:
                list_all_books();
                break;
            case 6:
                return;
            default:
                printf("TRY AGAIN\n");
                break;
        }
    }
}

void main_menu() {
    int choice;
    
    while(1) {
        printf("MENU\n");
        printf("1. Add New Book\n");
        printf("2. List Books\n");
        printf("3. EXIT\n");
        printf("Choose = ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                add_new_book();
                break;
            case 2:
                submenu();
                break;
            case 3:
                free(books);
                exit(0);
            default:
                printf("TRY AGAIN\n");
                break;
        }
    }
}

int main() {
    initialize_library();
    main_menu();
    return 0;
}