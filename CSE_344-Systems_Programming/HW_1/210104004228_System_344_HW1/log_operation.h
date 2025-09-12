#ifndef LOG_OPERATION_H
#define LOG_OPERATION_H


#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>


#define TIMESTAMP_SIZE 32

/**
 * @brief
 * Functions for handling logging operations with timestamps.
 */

char* get_timestamp();
void log_output(const char *format, ...);
void log_operation(const char *message);

int show_logs(void);


#endif
