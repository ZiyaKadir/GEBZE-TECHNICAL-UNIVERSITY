#ifndef SECURE_FILE_H
#define SECURE_FILE_H


#include "log_operation.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int create_file(const char *file_name);
int read_file(const char *file_name);
int append_to_file(const char *file_name, const char *content);
int delete_file(const char *file_name);

#endif
