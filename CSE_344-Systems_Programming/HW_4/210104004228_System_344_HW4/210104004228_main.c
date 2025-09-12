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
#include <time.h> 


#include "utils.h"
#include "buffer.h"

#define READ_BUFFER_SIZE 4096

// i use this to notify all threads to stop when SIGINT is pressed
volatile sig_atomic_t terminate_requested = 0;
Bounded_TS_Linked_List* g_buffer = NULL; 

void handle_sigint(int sig);
void setup_signal_handler();
void* worker_thread(void* arg);

typedef struct {

    Bounded_TS_Linked_List* buffer;
    Program_config* config;
    pthread_barrier_t* barrier;
    int thread_id;
    int match_count;

	// The start and end time of the thread
	// used to calculate the time taken by each thread
	struct timespec start_time;
	struct timespec end_time;

} Thread_Arg;


void handle_sigint(int sig) {
    (void)sig; 
    terminate_requested = 1;

    printf("\nSIGINT received (Signal %d), shutting down...\n", sig);

    if (g_buffer) {
        pthread_mutex_lock(&g_buffer->mutex);
        g_buffer->eof = true;

		// Essenttial waitig i need to add because the program does not succesfully finish
		// becuause they are waiting for spesific condition
        
        /* Wake up all worker threads that are waiting for new data */
        pthread_cond_broadcast(&g_buffer->not_empty); 
        
        /* Wake up the manager thread if it's waiting to add more data */
        pthread_cond_broadcast(&g_buffer->not_full);
        pthread_mutex_unlock(&g_buffer->mutex);
    }
}


void setup_signal_handler() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

/* 
   calculates how many milliseconds passed between two time points.
   i use this to calculate the time taken by each thread
   in this way i can understand the threads are really working seprately from each other
 */
double get_elapsed_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
}

/* 
   the main job of each worker thread - it gets lines from the buffer and searches for matches.
   each worker keeps track of how many matches it finds and how long it takes.
   all workers wait at a barrier at the end so that thread 0 can create the summary report.
 */
void* worker_thread(void* arg) {
    Thread_Arg* args = (Thread_Arg*)arg;
    Bounded_TS_Linked_List* buffer = args->buffer;
    const char* search_term = args->config->search_term;
    int match_count = 0;
    bool is_eof = false;
    
    clock_gettime(CLOCK_MONOTONIC, &args->start_time);
    
    /* Keep getting lines and searching until the program ends or there are no more lines */
    while (!terminate_requested) {
        char* line = buffer_pop(buffer, &is_eof);
        
        /* Stop working if we've reached the end of the file */
        if (is_eof) {
            break;
        }
        
        if (line) {
            if (boyer_moore_search(line, search_term)) {
                match_count++;
                printf("Worker %d found match: %s", args->thread_id, line);
                if (line[strlen(line) - 1] != '\n') {
                    printf("\n");
                }
            }
            free(line);
        }
    }
    
    clock_gettime(CLOCK_MONOTONIC, &args->end_time);
    
    args->match_count = match_count;
    
    // Each worker prints its own match count before waiting at the barrier
    printf("Worker %d found %d matches\n", args->thread_id, match_count);
    
    /* Wait here until all worker threads are done - important for synchronization */
    pthread_barrier_wait(args->barrier);
    
    /* Thread 0 is responsible for printing the final summary report */
    if (args->thread_id == 0) {
        printf("\n===== SUMMARY REPORT =====\n");
        Thread_Arg* all_args = args - args->thread_id; 
        
        int total_matches = 0;
        
        for (int i = 0; i < args->config->num_workers; i++) {
            double elapsed = get_elapsed_ms(all_args[i].start_time, all_args[i].end_time);
            printf("Worker %d found: %d matches (processed in %.2f ms)\n", 
                  i, all_args[i].match_count, elapsed);
            
            total_matches += all_args[i].match_count;
        }
        
        printf("\nTotal matches found: %d\n", total_matches);
        
        Buffer_stats stats = buffer_get_stats(buffer);
        printf("\nBuffer Statistics:\n");
        printf("  - Final size: %d/%d (%.1f%% full)\n", 
               stats.current_size, stats.capacity, stats.fill_percentage);
        
        printf("=========================\n");
    }
    
    return NULL;
}

/* 
   the manager reads the log file and puts lines into the buffer for workers to process.
   it reads the file in big chunks for speed, then splits chunks into complete lines.
   when it's done, it tells the worker threads that there are no more lines.
*/

void manager_function(Bounded_TS_Linked_List* buffer, Program_config* config) {
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    
    int fd = open(config->log_file, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open log file");
        buffer->eof = true;  
        return;
    }
    
    char read_buffer[READ_BUFFER_SIZE + 1];
    ssize_t bytes_read;
    char* line_buffer = NULL;
    size_t line_buffer_size = 0;
    size_t line_length = 0;
    int lines_processed = 0;
    
    /* Read the file in chunks until done or interrupted */
    while (!terminate_requested && (bytes_read = read(fd, read_buffer, READ_BUFFER_SIZE)) > 0) {
        read_buffer[bytes_read] = '\0';
        
        char* start = read_buffer;
        char* end;
        
        /* Find complete lines in each chunk and add them to the buffer */
        while ((end = strchr(start, '\n')) != NULL) {
            size_t piece_length = end - start + 1;  
            
            if (line_length + piece_length + 1 > line_buffer_size) {
                line_buffer_size = line_length + piece_length + READ_BUFFER_SIZE;
                line_buffer = realloc(line_buffer, line_buffer_size);
                if (!line_buffer) {
                    perror("Failed to allocate memory for line");
                    close(fd);
                    return;
                }
            }
            
            memcpy(line_buffer + line_length, start, piece_length);
            line_length += piece_length;
            line_buffer[line_length] = '\0';
            
            char* line_copy = strdup(line_buffer);
            if (!line_copy) {
                perror("Failed to allocate memory for line");
            } else {
                buffer_push(buffer, line_copy);
                lines_processed++;
                
                if (lines_processed % 500 == 0) {
                    printf("Manager: Processed %d lines\r", lines_processed);
                    fflush(stdout);
                }
            }
            
            line_length = 0;
            
            start = end + 1;
        }
        
        /* Save any partial line at the end of the chunk for next time */
        if (*start != '\0') {
            size_t remaining = strlen(start);
            
            if (line_length + remaining + 1 > line_buffer_size) {
                line_buffer_size = line_length + remaining + READ_BUFFER_SIZE;
                line_buffer = realloc(line_buffer, line_buffer_size);
                if (!line_buffer) {
                    perror("Failed to allocate memory for line");
                    close(fd);
                    return;
                }
            }
            
            memcpy(line_buffer + line_length, start, remaining);
            line_length += remaining;
            line_buffer[line_length] = '\0';
        }
    }
    
    /* Don't forget the last line if it doesn't end with a newline */
    if (line_length > 0) {
        char* line_copy = strdup(line_buffer);
        if (!line_copy) {
            perror("Failed to allocate memory for line");
        } else {
            buffer_push(buffer, line_copy);
            lines_processed++;
        }
    }
    
    free(line_buffer);
    close(fd);
    
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed = get_elapsed_ms(start_time, end_time);
    
    /* Tell worker threads there are no more lines to process */
    pthread_mutex_lock(&buffer->mutex);
    buffer->eof = true;
    pthread_cond_broadcast(&buffer->not_empty); 
    pthread_mutex_unlock(&buffer->mutex);
    
    printf("\nManager: Finished reading file\n");
    printf("Manager: Processed %d lines (took %.2f ms)\n", lines_processed, elapsed);
}

/* 
   the main function starts everything. It:
   1. Checks command line arguments
   2. Sets up the buffer and signal handling
   3. Creates worker threads
   4. Calls the manager function to read the file (the main thread) 
   // i think the main function as a thread that's why i dont create additional thread for the manager
   5. Waits for all threads to finish
   6. Cleans up resources
 */
int main(int argc, char *argv[]) {
    Program_config config;
    
    if (!parse_and_validate_args(argc, argv, &config)) {
        fprintf(stderr, "Usage: ./LogAnalyzer <buffer_size> <num_workers> <log_file> <search_term>\n");
        return EXIT_FAILURE;
    }
    
    printf("Buffer Size: %d\n", config.buffer_size);
    printf("Worker Count: %d\n", config.num_workers);
    printf("Log File: %s\n", config.log_file);
    printf("Search Term: %s\n", config.search_term);
    
    Bounded_TS_Linked_List buffer;
    buffer_init(&buffer, config.buffer_size);
    g_buffer = &buffer; 

    setup_signal_handler();
    
    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier, NULL, config.num_workers);
    
    Thread_Arg* worker_args = malloc(config.num_workers * sizeof(Thread_Arg));
    if (!worker_args) {
        perror("Failed to allocate memory for worker arguments");
        buffer_destroy(&buffer);
        pthread_barrier_destroy(&barrier);
        return EXIT_FAILURE;
    }
    
    pthread_t* worker_threads = malloc(config.num_workers * sizeof(pthread_t));
    if (!worker_threads) {
        perror("Failed to allocate memory for worker threads");
        buffer_destroy(&buffer);
        pthread_barrier_destroy(&barrier);
        free(worker_args);
        return EXIT_FAILURE;
    }
    
    /* Create all the worker threads */
    for (int i = 0; i < config.num_workers; i++) {
        worker_args[i].buffer = &buffer;
        worker_args[i].config = &config;
        worker_args[i].barrier = &barrier;
        worker_args[i].thread_id = i;
        worker_args[i].match_count = 0;
        
        if (pthread_create(&worker_threads[i], NULL, worker_thread, &worker_args[i]) != 0) {
            perror("Failed to create worker thread");
            buffer.eof = true;  
            
            for (int j = 0; j < i; j++) {
                pthread_join(worker_threads[j], NULL);
            }
            
            buffer_destroy(&buffer);
            pthread_barrier_destroy(&barrier);
            free(worker_args);
            free(worker_threads);
            
            return EXIT_FAILURE;
        }
    }
    
    /* Read the file and feed lines to the worker threads */
    manager_function(&buffer, &config);
    
    /* Wait for all worker threads to finish */
    for (int i = 0; i < config.num_workers; i++) {
        pthread_join(worker_threads[i], NULL);
    }
    
    buffer_destroy(&buffer);
    pthread_barrier_destroy(&barrier);
    free(worker_args);
    free(worker_threads);
    
    return EXIT_SUCCESS;
}