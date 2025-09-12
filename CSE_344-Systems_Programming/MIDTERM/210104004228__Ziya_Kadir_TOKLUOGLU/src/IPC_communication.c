#include "../include/IPC_communication.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>


int create_fifo(const char *fifo_name) {
    if (mkfifo(fifo_name, 0666) == -1) {
        if (errno != EEXIST) {
            perror("mkfifo");
            return -1;
        }
    }
    return 0;
}

/* Open a FIFO for reading */
int open_fifo_read(const char *fifo_name) {
    int fd = open(fifo_name, O_RDONLY);
    if (fd == -1) {
        perror("open fifo for reading");
        return -1;
    }
    return fd;
}

int open_fifo_write(const char *fifo_name) {
    int fd = open(fifo_name, O_WRONLY);
    if (fd == -1) {
        perror("open fifo for writing");
        return -1;
    }
    return fd;
}

void close_fifo(int fd) {
    if (fd >= 0) {
        close(fd);
    }
}

int write_to_fifo(int fd, void *buffer, size_t size) {
    ssize_t bytes_written = write(fd, buffer, size);
    if (bytes_written == -1) {
        perror("write to fifo");
        return -1;
    }
    return bytes_written;
}

int read_from_fifo(int fd, void *buffer, size_t size) {
    ssize_t bytes_read = read(fd, buffer, size);
    if (bytes_read == -1) {
        perror("read from fifo");
        return -1;
    }
    return bytes_read;
}

void remove_fifo(const char *fifo_name) {
    unlink(fifo_name);
}

void get_client_fifo_name(char *buffer, size_t size, pid_t pid) {
    snprintf(buffer, size, "/tmp/client_%d_fifo", pid);
}

void get_client_sem_names(char *empty_name, char *full_name, size_t size, pid_t pid) {
    snprintf(empty_name, size, "client_%d_empty", pid);
    snprintf(full_name, size, "client_%d_full", pid);
}



int fifo_exists(const char *fifo_name) {
    struct stat st;
    if (stat(fifo_name, &st) == -1) {
        if (errno != ENOENT)
            perror("stat on FIFO");
        return 0;
    }
    return S_ISFIFO(st.st_mode);
}

int write_message(int fd, const void *buffer, size_t size) {

    if (write_to_fifo(fd, (void *)&size, sizeof(size)) != sizeof(size)) {
        return -1;
    }
    
    if (write_to_fifo(fd, (void *)buffer, size) != size) {
        return -1;
    }
    
    fsync(fd);
    
    return 0;
}

char *read_message(int fd, size_t *out_size) {
    size_t size;
    char *buffer = NULL;
    
    ssize_t bytes_read = read_from_fifo(fd, &size, sizeof(size));
    if (bytes_read != sizeof(size)) {
        if (bytes_read == 0) {

            errno = 0;
        } else if (bytes_read == -1 && errno == EINTR) {

        } else {
            perror("read message size");
        }
        return NULL;
    }
    
    buffer = malloc(size + 1); 
    if (!buffer) {
        perror("malloc");
        return NULL;
    }
    
    bytes_read = read_from_fifo(fd, buffer, size);
    if (bytes_read != size) {
        free(buffer);
        buffer = NULL;
        if (bytes_read == 0) {
            errno = 0;
        } else if (bytes_read == -1 && errno == EINTR) {
        } else {
            perror("read message content");
        }
        return NULL;
    }
    
    buffer[size] = '\0';
    
    if (out_size) {
        *out_size = size;
    }
    
    return buffer;
}