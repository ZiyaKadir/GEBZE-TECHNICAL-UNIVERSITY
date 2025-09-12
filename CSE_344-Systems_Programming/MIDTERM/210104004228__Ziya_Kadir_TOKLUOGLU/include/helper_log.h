#ifndef HELPER_LOG_H
#define HELPER_LOG_H

#include <stddef.h>

void log_init(const char *db_filename);

void log_transaction(int account_id, char op, double amount, double balance);

void log_close(void);

#endif 
