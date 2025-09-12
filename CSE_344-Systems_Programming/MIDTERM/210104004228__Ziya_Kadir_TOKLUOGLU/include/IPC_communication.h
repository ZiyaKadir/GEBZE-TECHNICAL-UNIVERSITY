#ifndef IPC_COMMUNICATION_H
#define IPC_COMMUNICATION_H

#include <stddef.h> 
#include <sys/types.h> 

typedef struct {
    pid_t client_pid;
    char client_fifo[64];
    int request_number;
    char sem_empty_name[64];  
    char sem_full_name[64];   
} ClientCommunication;

typedef struct {
    int    ok;            /* 1 on success, 0 on failure                */
    int    numeric_id;    /* new or existing BankID_XX                 */
    double new_balance;   /* balance after the operation               */
    char   message[128];  /* short, human–readable status message      */
} TellerResponse;

int create_fifo(const char *fifo_name);
int open_fifo_read(const char *fifo_name);
int open_fifo_write(const char *fifo_name);
void close_fifo(int fd);
int write_to_fifo(int fd, void *buffer, size_t size);
int read_from_fifo(int fd, void *buffer, size_t size);
void remove_fifo(const char *fifo_name);
void get_client_fifo_name(char *buffer, size_t size, pid_t pid);
void get_client_sem_names(char *empty_name, char *full_name, size_t size, pid_t pid);

int write_message(int fd, const void *buffer, size_t size);
char *read_message(int fd, size_t *out_size);

int fifo_exists(const char *fifo_name);

#endif // IPC_COMMUNICATION_H
