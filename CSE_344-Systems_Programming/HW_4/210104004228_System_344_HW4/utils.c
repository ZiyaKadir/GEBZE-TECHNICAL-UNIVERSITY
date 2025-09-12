#include "utils.h"

/* 
   Checks if the command line arguments are valid and fills the config structure.
   Returns true if all arguments are good, false if there's a problem.
 */
bool parse_and_validate_args(int argc, char **argv, Program_config *config) {
    if (argc != 5) {
        return false;
    }

    int buffer_size = atoi(argv[1]);
    int num_workers = atoi(argv[2]);

    if (buffer_size <= 0 || num_workers <= 0) {
        return false;
    }

    if (strlen(argv[3]) == 0 || strlen(argv[4]) == 0) {
        return false;
    }

    
    config->buffer_size = buffer_size;
    config->num_workers = num_workers;
    strncpy(config->log_file, argv[3], sizeof(config->log_file) - 1);
    strncpy(config->search_term, argv[4], sizeof(config->search_term) - 1);

    return true;
}


// Boyer-Moore string search algorithm

static inline int max(int a, int b) {
    return (a > b) ? a : b;
}


void compute_bad_character_table(const char *pattern, int pattern_length, int bad_char[MAX_CHAR]) {
    for (int i = 0; i < MAX_CHAR; i++) {
        bad_char[i] = -1;
    }
    
    for (int i = 0; i < pattern_length; i++) {
        bad_char[(unsigned char)pattern[i]] = i;
    }
}



bool boyer_moore_search(const char *text, const char *pattern) {
    int pattern_length = strlen(pattern);
    int text_length = strlen(text);
    
    if (pattern_length == 0 || pattern_length > text_length) {
        return false;
    }
    
    int bad_char[MAX_CHAR];
    compute_bad_character_table(pattern, pattern_length, bad_char);
    
    int shift = 0;
    
    while (shift <= (text_length - pattern_length)) {
        int j = pattern_length - 1;
        
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }
        
        if (j < 0) {
            return true;
        } else {
            shift += max(1, j - bad_char[(unsigned char)text[shift + j]]);
        }
    }
    
    return false;
}