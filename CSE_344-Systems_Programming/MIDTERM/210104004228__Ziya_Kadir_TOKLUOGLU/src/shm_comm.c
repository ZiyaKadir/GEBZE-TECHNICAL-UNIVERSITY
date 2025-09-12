// shm_comm.c
#define _POSIX_C_SOURCE 200809L
#include "shm_comm.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/BinaryTree.h"

static void   *shm_base   = NULL;
static size_t  shm_offset = 0;

void init_shared_memory(void) {
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) { perror("shm_open"); exit(EXIT_FAILURE); }
    if (ftruncate(fd, SHM_SIZE) == -1) { perror("ftruncate"); exit(EXIT_FAILURE); }
    shm_base = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm_base == MAP_FAILED) { perror("mmap"); exit(EXIT_FAILURE); }
    close(fd);
    shm_offset = 0;
}

void *shm_alloc(size_t size) {
    if (shm_offset + size > SHM_SIZE) {
        fprintf(stderr, "Out of shared memory!\n");
        exit(EXIT_FAILURE);
    }
    void *ptr = (char*)shm_base + shm_offset;
    shm_offset += size;
    return ptr;
}

void cleanup_shared_memory(void) {
    munmap(shm_base, SHM_SIZE);
    shm_unlink(SHM_NAME);
}