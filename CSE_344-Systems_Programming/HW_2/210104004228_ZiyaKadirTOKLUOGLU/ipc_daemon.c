#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

#define FIFO1_PATH "/tmp/fifo1"
#define FIFO2_PATH "/tmp/fifo2"
#define LOG_FILE "/tmp/daemon_log"

#define COMMAND "FIND_LARGER"



int result = 0;         
int child_counter = 0;   
pid_t child1_pid = 0, child2_pid = 0; 
time_t child1_start, child2_start;  
int daemon_running = 1; 
int log_fifo_fd = -1;    

void create_fifos();
void cleanup_fifos();
void signal_handler(int sig);
void child1_process();
void child2_process();
void become_daemon();
void check_child_timeouts();
void log_message(const char *message);

void log_message(const char *message) {
    int log_fd;
    time_t now;
    char timestamp[64];
    char buffer[512];
    
    time(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
    
    snprintf(buffer, sizeof(buffer), "[%s] %s\n", timestamp, message);
    
    log_fd = open(LOG_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (log_fd != -1) {
        write(log_fd, buffer, strlen(buffer));
        close(log_fd);
    }
}


void signal_handler(int sig) {
    pid_t pid;
    int status;
    char message[256];
    time_t now;
    
    switch (sig) {
        case SIGCHLD:
            while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
                snprintf(message, sizeof(message), "Process ID of exited child: [PID : %d]", pid);
                log_message(message);
                
                if (WIFEXITED(status)) {
                    snprintf(message, sizeof(message), "Child %d exited with status: %d", pid, WEXITSTATUS(status));
                    log_message(message);
                } else if (WIFSIGNALED(status)) {
                    snprintf(message, sizeof(message), "Child %d killed by signal: %d", pid, WTERMSIG(status));
                    log_message(message);
                }
                
                if (pid == child1_pid) {
                    child1_pid = 0;
                    child_counter += 2;
                    snprintf(message, sizeof(message), "Child 1 terminated, counter now: %d", child_counter);
                    log_message(message);
                } else if (pid == child2_pid) {
                    child2_pid = 0;
                    child_counter += 2;
                    snprintf(message, sizeof(message), "Child 2 terminated, counter now: %d", child_counter);
                    log_message(message);
                } else {
                    child_counter += 2;
                    snprintf(message, sizeof(message), "Unknown child terminated, counter now: %d", child_counter);
                    log_message(message);
                }
            }
            break;
            
        case SIGUSR1:
            log_message("Received SIGUSR1 signal - Showing status");
            
            snprintf(message, sizeof(message), "Child counter: %d", child_counter);
            log_message(message);
            
            time(&now);
            
            if (child1_pid > 0) {
                snprintf(message, sizeof(message), "Child 1 (PID: %d) running for %ld seconds", 
                        child1_pid, now - child1_start);
                log_message(message);
            } else {
                log_message("Child 1 is not running");
            }
            
            if (child2_pid > 0) {
                snprintf(message, sizeof(message), "Child 2 (PID: %d) running for %ld seconds", 
                        child2_pid, now - child2_start);
                log_message(message);
            } else {
                log_message("Child 2 is not running");
            }
            break;
            
        case SIGHUP:
            log_message("Received SIGHUP signal - Reloading configuration");
            break;
            
        case SIGTERM:
            log_message("Received SIGTERM signal - Shutting down daemon");
            
            if (child1_pid > 0) {
                kill(child1_pid, SIGTERM);
                log_message("Sent SIGTERM to child 1");
            }
            
            if (child2_pid > 0) {
                kill(child2_pid, SIGTERM);
                log_message("Sent SIGTERM to child 2");
            }
            
            cleanup_fifos();
            
            log_message("Daemon shutting down");
            
            daemon_running = 0;
            break;
            
        default:
            snprintf(message, sizeof(message), "Received unhandled signal %d", sig);
            log_message(message);
            break;
    }
}

void check_child_timeouts() {
    time_t now;
    time(&now);
    char message[100];
    
    // Check if children are taking too long (more than 30 seconds)
    if (child1_pid > 0 && (now - child1_start) > 20) {
        snprintf(message, sizeof(message), "Child 1 (PID: %d) timed out, terminating", child1_pid);
        log_message(message);
        kill(child1_pid, SIGTERM);
        child1_pid = 0;
    }
    
    if (child2_pid > 0 && (now - child2_start) > 20) {
        snprintf(message, sizeof(message), "Child 2 (PID: %d) timed out, terminating", child2_pid);
        log_message(message);
        kill(child2_pid, SIGTERM);
        child2_pid = 0;
    }
}

void create_fifos() {

    cleanup_fifos();
    
    if (mkfifo(FIFO1_PATH, 0666) == -1) {
        log_message("mkfifo for FIFO1 failed");
        exit(EXIT_FAILURE);
    }
    
    if (mkfifo(FIFO2_PATH, 0666) == -1) {
        log_message("mkfifo for FIFO2 failed");
        unlink(FIFO1_PATH); 
        exit(EXIT_FAILURE);
    }
    
    log_message("FIFOs created successfully");
}

void cleanup_fifos() {
    unlink(FIFO1_PATH);
    unlink(FIFO2_PATH);

}

void child1_process() {
    int fifo1_fd, fifo2_fd;
    int num1, num2, larger_num;
    
    // log_message("Child 1 starting execution");
    
    // Open first FIFO for reading
    fifo1_fd = open(FIFO1_PATH, O_RDONLY);

    // Sleep for 10 seconds as required by assignment
    sleep(11);

    // +1 more second needs to wait because of the sequence of the opening FIFOS
    
    if (fifo1_fd == -1) {
        // log_message("Failed to open FIFO1 for reading");
        exit(EXIT_FAILURE);
    } 
    
    // log_message("Successfully opened FIFO1 for reading");
    
    // Read two integers from FIFO1
    if (read(fifo1_fd, &num1, sizeof(num1)) != sizeof(num1) || 
        read(fifo1_fd, &num2, sizeof(num2)) != sizeof(num2)) {
        // log_message("Failed to read integers from FIFO1");
        close(fifo1_fd);
        exit(EXIT_FAILURE);
    } else {
        char msg[100];
        snprintf(msg, sizeof(msg), "Successfully read integers from FIFO1: num1 = %d, num2 = %d", num1, num2);
        // log_message(msg);
    }
    
    close(fifo1_fd);
    
    // Determine the larger number
    larger_num = (num1 > num2) ? num1 : num2;
    
    // Open second FIFO for writing
    fifo2_fd = open(FIFO2_PATH, O_WRONLY);
    if (fifo2_fd == -1) {
        // log_message("Failed to open FIFO2 for writing");
        exit(EXIT_FAILURE);
    } else {
        // log_message("Successfully opened FIFO2 for writing");
    }
    
    // Write the larger number to FIFO2
    if (write(fifo2_fd, &larger_num, sizeof(larger_num)) != sizeof(larger_num)) {
        // log_message("Failed to write to FIFO2");
        close(fifo2_fd);
        exit(EXIT_FAILURE);
    } else {
        char msg[100];
        snprintf(msg, sizeof(msg), "Successfully wrote the larger number (%d) to FIFO2", larger_num);
        // log_message(msg);
    }
    
    close(fifo2_fd);
    // log_message("Child 1 completed successfully");
    exit(EXIT_SUCCESS);
}

void child2_process() {
    int fifo2_fd;
    int larger_num;
    char output_buffer[100];
    int stdout_fd = STDOUT_FILENO;
    
    fifo2_fd = open(FIFO2_PATH, O_RDONLY);
    // log_message("Child 2 starting execution");
    
    sleep(10);
    // Open second FIFO for reading
    
    
    if (fifo2_fd == -1) {
        // log_message("Failed to open FIFO2 for reading");
        exit(EXIT_FAILURE);
    } else {
        // log_message("Successfully opened FIFO2 for reading");
    }


    // Read the command from FIFO2
    char command_buffer[100];
    if (read(fifo2_fd, command_buffer, sizeof(command_buffer)) <= 0) {
        // log_message("Failed to read command from FIFO2");
        close(fifo2_fd);
        exit(EXIT_FAILURE);
    } else {
        // log_message("Successfully read command from FIFO2");
    }

    // Check if the command is correct
    if (strncmp(command_buffer, COMMAND, strlen(COMMAND)) != 0) {
        // log_message("Invalid command received");
        close(fifo2_fd);
        exit(EXIT_FAILURE);
    } else {
        // log_message("Valid command received");
    }
    
    // Read the larger number from FIFO2
    if (read(fifo2_fd, &larger_num, sizeof(larger_num)) != sizeof(larger_num)) {
        // log_message("Failed to read from FIFO2");
        close(fifo2_fd);
        exit(EXIT_FAILURE);
    } else {
        char msg[100];
        snprintf(msg, sizeof(msg), "Successfully read larger number %d from FIFO2", larger_num);
        // log_message(msg);
    }
    
    close(fifo2_fd);
    
    // Print the larger number to stdout using write system call
    snprintf(output_buffer, sizeof(output_buffer), "The larger number is: %d\n", larger_num);
    write(stdout_fd, output_buffer, strlen(output_buffer));
    
    char msg[100];
    snprintf(msg, sizeof(msg), "The larger number is: %d", larger_num);
    // log_message(msg);

    result = larger_num;
    
    // log_message("Child 2 completed successfully");
    exit(EXIT_SUCCESS);
}

void become_daemon() {
    pid_t pid;
    
    pid = fork();
    if (pid < 0) {

        const char *error_msg = "First fork failed\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        exit(EXIT_FAILURE);
    } else if (pid > 0) {

        exit(EXIT_SUCCESS);
    }
    
    if (setsid() < 0) {
        const char *error_msg = "setsid failed\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        exit(EXIT_FAILURE);
    }
    
    pid = fork();
    if (pid < 0) {
        const char *error_msg = "Second fork failed\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        exit(EXIT_FAILURE);
    } else if (pid > 0) {

        exit(EXIT_SUCCESS);
    }
    
    chdir("/");
    
    umask(0);
    

    int init_log_fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  
    if (init_log_fd >= 0) {

        const char *init_msg = "Initializing daemon...\n";
        write(init_log_fd, init_msg, strlen(init_msg));
        close(init_log_fd);
    }
    
    for (int i = 0; i < sysconf(_SC_OPEN_MAX); i++) {
        close(i);
    }
    
    int log_fd = open(LOG_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (log_fd < 0) {

        exit(EXIT_FAILURE);
    }
    
    dup2(log_fd, STDOUT_FILENO);
    dup2(log_fd, STDERR_FILENO);
    
    int null_fd = open("/dev/null", O_RDONLY);
    if (null_fd >= 0) {
        dup2(null_fd, STDIN_FILENO);
        close(null_fd);
    }
    
    if (log_fd > STDERR_FILENO) {
        close(log_fd);
    }
    
    int msg_fd = open(LOG_FILE, O_WRONLY | O_APPEND);
    if (msg_fd >= 0) {
        time_t now;
        char timestamp[64];
        time(&now);
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
        
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "[%s] Daemon started successfully\n", timestamp);
        write(msg_fd, buffer, strlen(buffer));
        close(msg_fd);
    }
}

int main(int argc, char *argv[]) {
    int num1, num2;
    int fifo1_fd, fifo2_fd;
    struct sigaction sa;
    char buffer[100];
    
    if (argc != 3) {
        const char *usage_msg = "Usage: %s <int1> <int2>\n";
        snprintf(buffer, sizeof(buffer), usage_msg, argv[0]);
        write(STDERR_FILENO, buffer, strlen(buffer));
        exit(EXIT_FAILURE);
    }
    
    num1 = atoi(argv[1]);
    num2 = atoi(argv[2]);
    
    snprintf(buffer, sizeof(buffer), "Input numbers: %d and %d\n", num1, num2);
    write(STDOUT_FILENO, buffer, strlen(buffer));
    
    become_daemon();
    
    char message[100];
    snprintf(message, sizeof(message), "Daemon initialized with numbers: %d and %d", num1, num2);
    log_message(message);
    
    create_fifos();
    
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_NOCLDSTOP; // Don't report when children stop/continue
    
    if (sigaction(SIGCHLD, &sa, NULL) == -1 ||
        sigaction(SIGUSR1, &sa, NULL) == -1 ||
        sigaction(SIGHUP, &sa, NULL) == -1 ||
        sigaction(SIGTERM, &sa, NULL) == -1) {
        log_message("Failed to set up signal handlers");
        exit(EXIT_FAILURE);
    }
    
    
    time(&child1_start);
    time(&child2_start);
    
    child1_pid = fork();
    if (child1_pid == -1) {
        log_message("Failed to create first child process");
        exit(EXIT_FAILURE);
    } else if (child1_pid == 0) {

        child1_process();
        exit(EXIT_FAILURE);
    }
    
    snprintf(message, sizeof(message), "Created Child 1 process (PID: %d)", child1_pid);
    log_message(message);
    
    child2_pid = fork();
    if (child2_pid == -1) {
        log_message("Failed to create second child process");
        kill(child1_pid, SIGTERM); 
        exit(EXIT_FAILURE);
    } else if (child2_pid == 0) {

        child2_process();
        exit(EXIT_FAILURE); 
    }
    
    snprintf(message, sizeof(message), "Created Child 2 process (PID: %d)", child2_pid);
    log_message(message);
    
    fifo1_fd = open(FIFO1_PATH, O_WRONLY);
    if (fifo1_fd == -1) {
        log_message("Failed to open FIFO1 for writing");
        exit(EXIT_FAILURE);
    }
    
    if (write(fifo1_fd, &num1, sizeof(num1)) != sizeof(num1) || 
        write(fifo1_fd, &num2, sizeof(num2)) != sizeof(num2)) {
        log_message("Failed to write to FIFO1");
        close(fifo1_fd);
        exit(EXIT_FAILURE);
    }

    
    fifo2_fd = open(FIFO2_PATH, O_WRONLY);
    if (fifo1_fd == -1) {
        log_message("Failed to open FIFO1 for writing");
        exit(EXIT_FAILURE);
    }

    if (write(fifo2_fd, COMMAND, strlen(COMMAND)) != strlen(COMMAND)) {
        log_message("Failed to write command to FIFO2");
        close(fifo2_fd);
        exit(EXIT_FAILURE);
    } else {
        log_message("Successfully wrote command to FIFO2");
    }
    

    
    close(fifo1_fd);
    
    log_message("Parent: Sent integers to FIFO1");
    
    int proceeding_count = 0;
    
    while (daemon_running && child_counter < 4) {
        char loop_msg[100];
        snprintf(loop_msg, sizeof(loop_msg), "proceeding (%d) child_counter=%d daemon_running=%d", 
                ++proceeding_count, child_counter, daemon_running);
        log_message(loop_msg);
            
        check_child_timeouts();
        
        sleep(2);
    }
    
    log_message("All children have exited or daemon shutting down");  
    
    cleanup_fifos();
    
    log_message("Daemon terminating");
    
    return EXIT_SUCCESS;
}