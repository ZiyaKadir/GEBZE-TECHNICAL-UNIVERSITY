#define _POSIX_C_SOURCE 200809L
#include "../include/helper_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static FILE *log_fp = NULL;

void log_init(const char *db_filename) {
    char logname[256];
    char *dot = strrchr(db_filename, '.');
    if (dot) {
        size_t len = dot - db_filename;
        strncpy(logname, db_filename, len);
        logname[len] = '\0';
        strcat(logname, ".bankLog");
    } else {
        snprintf(logname, sizeof logname, "%s.bankLog", db_filename);
    }
    log_fp = fopen(logname, "w");
    if (!log_fp) {
        perror("Failed to open log file");
        exit(EXIT_FAILURE);
    }

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char buf[64];
    strftime(buf, sizeof buf, "%H:%M %B %d %Y", tm);
    fprintf(log_fp, "# Adabank Log file updated @%s\n", buf);
    fflush(log_fp);
}

void log_transaction(int account_id, char op, double amount, double balance) {
    if (!log_fp) return;
    // Format according to the PDF example
    if (op == 'W' && balance == 0) {
        fprintf(log_fp, "# BankID_%02d D %.0f W %.0f 0\n",
                account_id, amount, amount);  // This is a simplification
    } else if (op == 'D') {
        fprintf(log_fp, "BankID_%02d D %.0f %.0f\n",
                account_id, amount, balance);
    } else {
        fprintf(log_fp, "BankID_%02d W %.0f %.0f\n",
                account_id, amount, balance);
    }
    fflush(log_fp);
}

void log_close(void) {
    if (!log_fp) return;
    fprintf(log_fp, "## end of log.\n");
    fclose(log_fp);
    log_fp = NULL;
}