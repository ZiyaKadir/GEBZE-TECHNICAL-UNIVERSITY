#include "log_operation.h"

char* get_timestamp() {
    char *timestamp = malloc(TIMESTAMP_SIZE);
    if (!timestamp) {
        write(STDERR_FILENO, "Memory allocation failed\n", 25);
        return NULL;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(timestamp, TIMESTAMP_SIZE, "[%Y-%m-%d %H:%M:%S]", t);

    return timestamp;
}

void log_operation(const char *message) {
    char *timestamp = get_timestamp();
    if (!timestamp) {
        return;
    }

    int fd = open("logs/log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        write(STDERR_FILENO, "Error opening log file\n", 23);
        free(timestamp);
        return;
    }

    
    char buffer[512];
    strcpy(buffer, timestamp);
    strcat(buffer, " ");
    strcat(buffer, message);
    strcat(buffer, "\n");

    if (write(fd, buffer, strlen(buffer)) < 0) {
        write(STDERR_FILENO, "Error writing to log file\n", 26);
    }

    close(fd);
    free(timestamp);
}

void log_output(const char *format, ...) {
    char buffer[512];
    va_list args;
    va_start(args, format);

   
    char *p = buffer;
    const char *f = format;
    while (*f && (p - buffer) < (long int)sizeof(buffer) - 1) { 
        if (*f == '%' && *(f + 1) == 's') { 
            f += 2;
            const char *str_arg = va_arg(args, const char *);
            while (*str_arg && (p - buffer) < (long int)sizeof(buffer) - 1) { 
                *p++ = *str_arg++;
            }
        } else {
            *p++ = *f++;
        }
    }
    *p = '\0';

    va_end(args);

    log_operation(buffer);
}



int show_logs(void) {
    pid_t pid = fork();

    if (pid < 0) {
        write(STDERR_FILENO, "Fork failed\n", 12);
        log_output("Error: fork failed while displaying logs.");
        return -1;
    }

    if (pid == 0) { 
        int fd = open("logs/log.txt", O_RDONLY);
        if (fd < 0) {
            write(STDERR_FILENO, "Error opening log file\n", 23);
            exit(1);
        }

        char buffer[256];
        ssize_t bytes_read;

        
        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
            if (write(STDOUT_FILENO, buffer, bytes_read) < 0) {
                write(STDERR_FILENO, "Error writing logs to stdout\n", 30);
                close(fd);
                exit(1);
            }
        }

        close(fd);
        exit(0); 
    } else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            write(STDERR_FILENO, "waitpid failed\n", 15);
            log_output("Error: waitpid failed while displaying logs.");
            return -1;
        }

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);

            if (exit_status == 0) {
                log_output("Logs displayed successfully.");
                return 0;
            } else {
                log_output("Error: Unable to display logs.");
                return -1;
            }
        } else {
            log_output("Error: Child terminated abnormally while displaying logs.");
            return -1;
        }
    }
}
