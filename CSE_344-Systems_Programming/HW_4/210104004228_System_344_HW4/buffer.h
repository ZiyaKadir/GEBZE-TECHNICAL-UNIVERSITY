#ifndef BUFFER_H
#define BUFFER_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>


extern volatile sig_atomic_t terminate_requested;


typedef struct Buffer_node {
    char* data;                
    struct Buffer_node* next;   
} Buffer_node;

// Thread safe bounded linked list buffer
typedef struct {
    Buffer_node* head;          
    Buffer_node* tail;           
    int count;                  
    int capacity;               
    
    pthread_mutex_t mutex;      
    pthread_cond_t not_full;    
    pthread_cond_t not_empty;   
    
    bool eof;
} Bounded_TS_Linked_List;
// it is like the BoundedTSQueue in the cpp but i use the linked list as a data strcuture


typedef struct {
    int current_size;
    int capacity;
    float fill_percentage;
} Buffer_stats;

void buffer_init(Bounded_TS_Linked_List *buf, int capacity);

void buffer_destroy(Bounded_TS_Linked_List *buf);

void buffer_push(Bounded_TS_Linked_List *buf, char *line);

char* buffer_pop(Bounded_TS_Linked_List *buf, bool *is_eof);

Buffer_stats buffer_get_stats(Bounded_TS_Linked_List *buf);

#endif