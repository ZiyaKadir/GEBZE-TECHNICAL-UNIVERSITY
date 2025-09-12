#include "secure_file.h"

int create_file(const char *file_name) {
    pid_t pid = fork();

    if (pid < 0) {
        write(STDERR_FILENO, "Fork failed\n", 12);
        log_output("Error: fork failed when creating file \"%s\".", file_name);
        return -1;
    }

    if (pid == 0) { 
        int fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, 0644);
        if (fd == -1) {
            if (errno == EEXIST) {
                exit(2); 
            } else {
                exit(1); 
            }
        }

        char *timestamp = get_timestamp();
        if (!timestamp) {
            close(fd);
            exit(1);
        }

        if (write(fd, timestamp, strlen(timestamp)) < 0) {
            write(STDERR_FILENO, "Error writing timestamp to file\n", 32);
            close(fd);
            free(timestamp);
            exit(1);
        }

        free(timestamp);
        close(fd);
        exit(0); 
    } else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            write(STDERR_FILENO, "waitpid failed\n", 15);
            log_output("Error: waitpid failed while creating file \"%s\".", file_name);
            return -1;
        }

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status == 0) {
                log_output("File \"%s\" created successfully.", file_name);
                return 0;
            } else if (exit_status == 2) {
                log_output("Error: File \"%s\" already exists.", file_name);
                return -1;
            } else {
                log_output("Error: Unable to create file \"%s\".", file_name);
                return -1;
            }
        } else {
            log_output("Error: Child terminated abnormally while creating file \"%s\".", file_name);
            return -1;
        }
    }
}

int read_file(const char *file_name) {
    pid_t pid = fork();

    if (pid < 0) {
        write(STDERR_FILENO, "Fork failed\n", 12);
        log_output("Error: fork failed while reading file \"%s\".", file_name);
        return -1;
    }

    if (pid == 0) {  
        int fd = open(file_name, O_RDONLY);
        if (fd == -1) {
            write(STDOUT_FILENO, "Error: File \"", 13);
            write(STDOUT_FILENO, file_name, strlen(file_name));
            write(STDOUT_FILENO, "\" not found.\n", 13);
            exit(1);
        }

        char buffer[256];
        ssize_t bytes_read;

        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }

        close(fd);
        exit(0);  
    } else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            write(STDERR_FILENO, "waitpid failed\n", 15);
            log_output("Error: waitpid failed when reading file \"%s\".", file_name);
            return -1;
        }

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status == 0) {
                log_output("File \"%s\" read successfully.", file_name);
                return 0;
            } else {
                log_output("Error: File \"%s\" not found or unable to read.", file_name);
                return -1;
            }
        } else {
            log_output("Error: Child terminated abnormally while reading \"%s\".", file_name);
            return -1;
        }
    }
}

int append_to_file(const char *file_name, const char *content) {
    pid_t pid = fork();

    if (pid < 0) {
        write(STDERR_FILENO, "Fork failed\n", 12);
        log_output("Error: fork failed when appending to file \"%s\".", file_name);
        return -1;
    }

    if (pid == 0) { // Child process performs file appending
        int fd = open(file_name, O_WRONLY | O_APPEND);
        if (fd == -1) {
            write(STDERR_FILENO, "Error opening file\n", 19);
            exit(1);
        }

        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0; 

        
        if (fcntl(fd, F_SETLK, &lock) == -1) {
            write(STDERR_FILENO, "File is locked\n", 15);
            close(fd);
            exit(2);
        }

        if (write(fd, content, strlen(content)) < 0) {
            write(STDERR_FILENO, "Error writing to file\n", 22);
            lock.l_type = F_UNLCK;  
            fcntl(fd, F_SETLK, &lock);
            close(fd);
            exit(1);
        }

        
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        close(fd);
        exit(0);
    } else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);

            if (exit_status == 0) {
                log_output("Content appended successfully to \"%s\".", file_name);
                return 0;
            } else if (exit_status == 2) {
                log_output("Error: Cannot write to \"%s\". File is locked.", file_name);
                return -1;
            } else {
                log_output("Error: Cannot write to \"%s\". File is locked or read-only.", file_name);
                return -1;
            }
        } else {
            log_output("Error: Child terminated abnormally while appending to \"%s\".", file_name);
            return -1;
        }
    }
}

int delete_file(const char *file_name) {
    pid_t pid = fork();

    if (pid < 0) {
        write(STDERR_FILENO, "Fork failed\n", 12);
        log_output("Error: fork failed when deleting file \"%s\".", file_name);
        return -1;
    }

    if (pid == 0) { 
        if (unlink(file_name) == -1) {
            if (errno == ENOENT) {
                exit(2); 
            } else {
                exit(1); 
            }
        }
        exit(0); 
    } else { 
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            write(STDERR_FILENO, "waitpid failed\n", 15);
            log_output("Error: waitpid failed when deleting file \"%s\".", file_name);
            return -1;
        }

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);

            if (exit_status == 0) {
                log_output("File \"%s\" deleted successfully.", file_name);
                return 0;
            } else if (exit_status == 2) {
                log_output("Error: File \"%s\" not found.", file_name);
                write(STDOUT_FILENO, "Error: File \"", 13);
                write(STDOUT_FILENO, file_name, strlen(file_name));
                write(STDOUT_FILENO, "\" not found.\n", 13);
                return -1;
            } else {
                log_output("Error: Unable to delete file \"%s\".", file_name);
                return -1;
            }
        } else {
            log_output("Error: Child terminated abnormally while deleting \"%s\".", file_name);
            return -1;
        }
    }
}
