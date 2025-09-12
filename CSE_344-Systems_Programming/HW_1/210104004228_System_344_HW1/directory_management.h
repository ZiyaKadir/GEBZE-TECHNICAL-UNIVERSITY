#ifndef DIRECTORY_MANAGEMENT_H
#define DIRECTORY_MANAGEMENT_H

#include "log_operation.h"
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


int create_directory(const char *folder_name);
int list_directory(const char *folder_name);
int list_files_by_extension(const char *folder_name, const char *extension);
int delete_directory(const char *folder_name);

#endif
