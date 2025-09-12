#include "directory_management.h"


int create_directory(const char *folder_name) {
    write(STDOUT_FILENO, "Creating directory \"", 21);
    write(STDOUT_FILENO, folder_name, strlen(folder_name));
    write(STDOUT_FILENO, "\"...\n", 5);

    pid_t pid = fork();

    if (pid < 0) {
        write(STDERR_FILENO, "Fork failed: ", 13);
        write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
        write(STDERR_FILENO, "\n", 1);
        log_output("Error: fork failed when creating directory \"%s\".", folder_name);
        return -1;
    }

    if (pid == 0) { 
        if (mkdir(folder_name, 0755) == -1) {
            if (errno == EEXIST)
                exit(2); 
            else
                exit(1); 
        }
        exit(0); 
    } else {  
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            write(STDERR_FILENO, "waitpid failed: ", 16);
            write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
            write(STDERR_FILENO, "\n", 1);
            log_output("Error: waitpid failed when creating directory \"%s\".", folder_name);
            return -1;
        }

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);

            if (exit_status == 0) {
                log_output("Directory \"%s\" created successfully.", folder_name);
                return 0;
            } else if (exit_status == 2) {
                log_output("Error: Directory \"%s\" already exists.", folder_name);
                write(STDOUT_FILENO, "Error: Directory \"", 18);
                write(STDOUT_FILENO, folder_name, strlen(folder_name));
                write(STDOUT_FILENO, "\" already exists.\n", 18);
                return -1;
            } else {
                log_output("Error: Unable to create directory \"%s\".", folder_name);
                write(STDOUT_FILENO, "Error: Unable to create directory \"", 35);
                write(STDOUT_FILENO, folder_name, strlen(folder_name));
                write(STDOUT_FILENO, "\".\n", 3);
                return -1;
            }
        } else {
            log_output("Error: Child terminated abnormally while creating \"%s\".", folder_name);
            return -1;
        }
    }
}



int list_directory(const char *folder_name) {
    pid_t pid = fork();

    if (pid < 0) {
        write(STDERR_FILENO, "Fork failed\n", 12);
        log_output("Error: fork failed when listing directory \"%s\".", folder_name);
        return -1;
    }

    if (pid == 0) { 
        DIR *dir = opendir(folder_name);
        if (!dir) {
            write(STDOUT_FILENO, "Error: Directory not found.\n", 28);
            exit(1);  
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            write(STDOUT_FILENO, entry->d_name, strlen(entry->d_name));
            write(STDOUT_FILENO, "\n", 1);
        }

        closedir(dir);
        exit(0);  
    } else {  
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            write(STDERR_FILENO, "waitpid failed\n", 15);
            log_output("Error: waitpid failed when listing directory \"%s\".", folder_name);
            return -1;
        }

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            log_output("Directory \"%s\" listed successfully.", folder_name);
            return 0;
        } else {
            log_output("Error: Directory \"%s\" not found.", folder_name);
            return -1;
        }
    }
}




int list_files_by_extension(const char *folder_name, const char *extension) {
    pid_t pid = fork();

    if (pid < 0) {
        write(STDERR_FILENO, "Fork failed\n", 12);
        log_output("Error: fork failed when listing files by extension in \"%s\".", folder_name);
        return -1;
    }

    if (pid == 0) {  // Child process: Handles file listing
        DIR *dir = opendir(folder_name);
        if (!dir) {
            write(STDOUT_FILENO, "Error: Directory not found.\n", 28);
            exit(1);  // Exit code 1: Directory not found
        }

        struct dirent *entry;
        int found = 0;
        struct stat st;
        char filepath[512];

        while ((entry = readdir(dir)) != NULL) {
            strcpy(filepath, folder_name);
            strcat(filepath, "/");
            strcat(filepath, entry->d_name);

            if (stat(filepath, &st) == 0 && S_ISREG(st.st_mode)) {
                const char *ext = strrchr(entry->d_name, '.');
                if (ext && strcmp(ext, extension) == 0) {
                    write(STDOUT_FILENO, entry->d_name, strlen(entry->d_name));
                    write(STDOUT_FILENO, "\n", 1);
                    found = 1;
                }
            }
        }

        closedir(dir);

        if (found)
            exit(0); 
        else
            exit(2); 
    } else {  
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            write(STDERR_FILENO, "waitpid failed\n", 15);
            log_output("Error: waitpid failed when listing files in \"%s\".", folder_name);
            return -1;
        }

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);

            if (exit_status == 0) {
                log_output("Files with extension \"%s\" listed successfully in \"%s\".", extension, folder_name);
                return 0;
            } else if (exit_status == 2) {
                log_output("No files with extension \"%s\" found in \"%s\".", extension, folder_name);
                write(STDOUT_FILENO, "No files with extension \"", 25);
                write(STDOUT_FILENO, extension, strlen(extension));
                write(STDOUT_FILENO, "\" found in \"", 11);
                write(STDOUT_FILENO, folder_name, strlen(folder_name));
                write(STDOUT_FILENO, "\".\n", 3);
                return -1;
            } else {
                log_output("Error: Unable to access directory \"%s\".", folder_name);
                write(STDOUT_FILENO, "Error: Unable to access directory \"", 35);
                write(STDOUT_FILENO, folder_name, strlen(folder_name));
                write(STDOUT_FILENO, "\".\n", 3);
                return -1;
            }
        } else {
            log_output("Error: Child terminated abnormally while listing files in \"%s\".", folder_name);
            return -1;
        }
    }
}





int delete_directory(const char *folder_name) {
    pid_t pid = fork();

    if (pid < 0) {
        write(STDERR_FILENO, "Fork failed: ", 13);
        write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
        write(STDERR_FILENO, "\n", 1);
        log_output("Error: fork failed when deleting directory \"%s\".", folder_name);
        return -1;
    }

    if (pid == 0) {  
        if (rmdir(folder_name) == -1) {
            if (errno == ENOTEMPTY) {
                exit(2); 
            } else if (errno == ENOENT) {
                exit(3); 
            } else {
                exit(1); 
            }
        }
        exit(0); 
    } else {  
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            write(STDERR_FILENO, "waitpid failed: ", 16);
            write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
            write(STDERR_FILENO, "\n", 1);
            log_output("Error: waitpid failed when deleting directory \"%s\".", folder_name);
            return -1;
        }

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            
            if (exit_status == 0) {
                log_output("Directory \"%s\" deleted successfully.", folder_name);
                return 0;
            } else if (exit_status == 2) {
                log_output("Error: Directory \"%s\" is not empty.", folder_name);
                write(STDOUT_FILENO, "Error: Directory \"", 18);
                write(STDOUT_FILENO, folder_name, strlen(folder_name));
                write(STDOUT_FILENO, "\" is not empty.\n", 16);
                return -1;
            } else if (exit_status == 3) {
                log_output("Error: Directory \"%s\" not found.", folder_name);
                write(STDOUT_FILENO, "Error: Directory \"", 18);
                write(STDOUT_FILENO, folder_name, strlen(folder_name));
                write(STDOUT_FILENO, "\" not found.\n", 13);
                return -1;
            } else {
                log_output("Error: Unable to delete directory \"%s\".", folder_name);
                write(STDOUT_FILENO, "Error: Unable to delete directory \"", 35);
                write(STDOUT_FILENO, folder_name, strlen(folder_name));
                write(STDOUT_FILENO, "\".\n", 3);
                return -1;
            }
        } else {
            log_output("Error: Child terminated abnormally while deleting directory \"%s\".", folder_name);
            return -1;
        }
    }
}
