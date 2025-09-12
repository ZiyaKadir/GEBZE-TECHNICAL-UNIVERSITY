#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "buffer.h"

/* 
   Sets up a new buffer with a given capacity.
   Creates all the needed locks and condition variables to make the buffer thread-safe.
 */
void buffer_init(Bounded_TS_Linked_List *buf, int capacity) {
    buf->head = NULL;
    buf->tail = NULL;
    buf->count = 0;
    buf->capacity = capacity;
    buf->eof = false;

    pthread_mutex_init(&buf->mutex, NULL);
    pthread_cond_init(&buf->not_full, NULL);
    pthread_cond_init(&buf->not_empty, NULL);
}

/* 
   Cleans up all resources used by the buffer.
   Frees all nodes and the data they contain, and destroys locks and condition variables.
 */
void buffer_destroy(Bounded_TS_Linked_List *buf) {
    pthread_mutex_lock(&buf->mutex);
    
    Buffer_node* current = buf->head;
    while (current != NULL) {
        Buffer_node* next = current->next;
        free(current->data); 
        free(current);        
        current = next;
    }
    
    buf->head = NULL;
    buf->tail = NULL;
    buf->count = 0;
    
    pthread_mutex_unlock(&buf->mutex);
    
    pthread_mutex_destroy(&buf->mutex);
    pthread_cond_destroy(&buf->not_full);
    pthread_cond_destroy(&buf->not_empty);
}

/* 
  Adds a line to the buffer. If the buffer is full, waits until there's space.
  Used by the manager thread to feed lines to the worker threads.
 */
void buffer_push(Bounded_TS_Linked_List *buf, char *line) {
    /* Create a new node to hold the line */
    Buffer_node* new_node = malloc(sizeof(Buffer_node));
    if (!new_node) {
        perror("Failed to allocate memory for buffer node");
        free(line);  
        return;
    }
    
    new_node->data = line;
    new_node->next = NULL;
    
    pthread_mutex_lock(&buf->mutex);
    
    /* Wait here if the buffer is full - key part of the producer-consumer pattern */
    while (buf->count >= buf->capacity && !terminate_requested) {
        pthread_cond_wait(&buf->not_full, &buf->mutex);
    }
    
    /* If the program is shutting down, don't add the line */
    if (terminate_requested) {
        pthread_mutex_unlock(&buf->mutex);
        free(new_node);
        free(line);
        return;
    }
    
    /* Add the node to the linked list */
    if (buf->tail == NULL) {
        buf->head = new_node;
        buf->tail = new_node;
    } else {
        buf->tail->next = new_node;
        buf->tail = new_node;
    }
    
    buf->count++;
    
    /* Tell waiting worker threads that there's new data */
    pthread_cond_signal(&buf->not_empty);
    pthread_mutex_unlock(&buf->mutex);
}

/* 
  Gets a line from the buffer. If the buffer is empty, waits until there's data.
  Used by worker threads to get lines to search.
 */
char* buffer_pop(Bounded_TS_Linked_List *buf, bool *is_eof) {
    pthread_mutex_lock(&buf->mutex);
    
    /* Wait here if the buffer is empty - key part of the producer-consumer pattern */
    while (buf->count == 0 && !buf->eof && !terminate_requested) {
        pthread_cond_wait(&buf->not_empty, &buf->mutex);
    }
    
    /* If the program is shutting down, stop processing */
    if (terminate_requested) {
        *is_eof = true;
        pthread_mutex_unlock(&buf->mutex);
        return NULL;
    }
    
    /* If there are no more lines and the file is fully read, we're done */
    if (buf->count == 0 && buf->eof) {
        *is_eof = true;
        pthread_mutex_unlock(&buf->mutex);
        return NULL;
    }
    
    /* Get a line from the linked list */
    Buffer_node* node = buf->head;
    char* line = node->data;
    
    buf->head = node->next;
    if (buf->head == NULL) {
        buf->tail = NULL;
    }
    
    buf->count--;
    
    free(node);
    
    /* Tell the waiting manager thread that there's space in the buffer */
    pthread_cond_signal(&buf->not_full);
    pthread_mutex_unlock(&buf->mutex);
    
    *is_eof = false;
    return line;
}


Buffer_stats buffer_get_stats(Bounded_TS_Linked_List *buf) {
    Buffer_stats stats;
    
    pthread_mutex_lock(&buf->mutex);
    stats.current_size = buf->count;
    stats.capacity = buf->capacity;
    stats.fill_percentage = (float)buf->count / buf->capacity * 100.0f;
    pthread_mutex_unlock(&buf->mutex);
    
    return stats;
}