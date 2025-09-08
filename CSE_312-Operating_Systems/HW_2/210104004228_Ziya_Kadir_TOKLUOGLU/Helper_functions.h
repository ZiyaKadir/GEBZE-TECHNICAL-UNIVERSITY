#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <ctime>
#include "Directory.h"
#include "File.h"

using namespace std;


typedef enum Operation{
    DIREC,
    DUMPE2FS,
    READ
} Operation;

typedef struct Paramater_create{
    string program_name; // index 0
    int size_fsystem; // index 1 for make file system
    string file_fsystem; // index 2 for make file system // index 1 for file system operation
    string path_file; // index 3 for make file system

} Paramater_create;



typedef struct Paramater_oper{
    string program_name; // index 0
    string file_fsystem; // index 2 for make file system // index 1 for file system operation
    Operation operation; // index 2 for file system operation
    string paramaters[2];// index 3,4 or more for file system operation's paramaters

    int size_fystem; 

} Paramater_oper;

typedef struct Paramater_CD{
    int64_t max_bytes;
    int64_t total_blocks;
    int block_size;
    int Total_Entry_size;
    int necessary_blocks;
}Paramater_CD;



int take_input_create(Paramater_create &param, int argc, char** argv);


int take_input_oper(Paramater_oper &param, int argc, char** argv);


void takeDirectory(const string& dirPath, Directory& parentDirectory);

void Print(File& root);

void Print_Path(File& root);

#endif // HELPER_FUNCTION_H