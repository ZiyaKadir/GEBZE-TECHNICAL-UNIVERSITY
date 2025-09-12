// shm_comm.h
#ifndef SHM_COMM_H
#define SHM_COMM_H

#include <stddef.h>

#define SHM_NAME   "/ada_bank_shm"

#define MAX_NODES  1024
#define SHM_SIZE   (sizeof(BinaryTree) + MAX_NODES * sizeof(TreeNode))

void init_shared_memory(void);

void *shm_alloc(size_t size);

void cleanup_shared_memory(void);

#endif 
