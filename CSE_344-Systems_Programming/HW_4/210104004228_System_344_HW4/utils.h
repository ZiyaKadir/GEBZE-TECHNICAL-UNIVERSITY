#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

#define MAX_CHAR 256

typedef struct Program_config{
    int buffer_size;
    int num_workers;
    char log_file[256];
    char search_term[128];
} Program_config;

bool parse_and_validate_args(int argc, char **argv, Program_config *config);

void compute_bad_character_table(const char *pattern, int pattern_length, int bad_char[MAX_CHAR]);
bool boyer_moore_search(const char *text, const char *pattern);

#endif