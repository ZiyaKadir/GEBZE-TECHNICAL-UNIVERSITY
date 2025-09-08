#include <iostream>
#include <string>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


#include "Helper_functions.h"
#include "Directory.h"
#include "File.h"

using namespace std;



void read_superblock(Paramater_oper& param, Paramater_CD& param_cd) {
    cout << "Read Superblock" << endl;

    int fd = open(param.file_fsystem.c_str(), O_RDONLY);
    if (fd < 0){
        cerr << "Error: Cannot open superblock file" << endl;
        return;
    }

    int64_t max_bytes;
    int64_t total_blocks;
    int block_size;
    int Total_Entry_size;
    int necessary_blocks;

    read(fd, &max_bytes, sizeof(max_bytes));
    read(fd, &total_blocks, sizeof(total_blocks));
    read(fd, &block_size, sizeof(block_size));
    read(fd, &Total_Entry_size, sizeof(Total_Entry_size));
    read(fd, &necessary_blocks, sizeof(necessary_blocks));


    param_cd.max_bytes = max_bytes;
    param_cd.total_blocks = total_blocks;
    param_cd.block_size = block_size;
    param_cd.Total_Entry_size = Total_Entry_size;
    param_cd.necessary_blocks = necessary_blocks;
    

cout << "==========================================" << endl;
    cout << "Max Bytes = " << max_bytes << endl;
    cout << "Total Blocks = " << total_blocks << endl;
    cout << "Block Size = " << block_size << endl;
    cout << "Total Entry Size = " << Total_Entry_size << endl;
    cout << "Necessary Blocks = " << necessary_blocks << endl;
cout << "==========================================" << endl;

    close(fd);
    
}

int read_file_entry(File* root, int fd, Paramater_CD& param_cd) {
    //cout << "Read File Entry" << endl;

    file_entry entry;
    ssize_t bytesRead = read(fd, &entry, sizeof(file_entry));
    if (bytesRead < 0) {
        cerr << "Failed to read file entry" << endl;
        perror("Read error");
        return 0;
    } else if (bytesRead == 0) {
        cerr << "No data read, might be EOF" << endl;
        return 0;
    }

    File* file = nullptr;
    if (entry.type == '1') {
        file = new Directory("", 0, time(nullptr));
    } else {
        file = new File();
    }
    file->set_entry(entry);

    cout << "Read file directory: " << file->get_name() << " , Date: " << 
        file->get_date() << ", Time: " << file->get_time() << ", Size = " << file->get_size()
         << ", Start Block = " << file->get_start_block() << ", Type = " << file->get_type() << endl;

    root->add_file(file);

    if (file->get_type() == '1') {
        Directory* dir = dynamic_cast<Directory*>(file);
        if (dir != nullptr) {
            for (int i = 0; i < dir->get_number_of_subfiles() -1; i++) {
                i += read_file_entry(dir, fd, param_cd);
            }
        } else {
            cerr << "Failed to cast to Directory" << endl;
        }
    }

    return file->get_number_of_subfiles();
}

void read_file_system(Paramater_oper& param, Paramater_CD& param_cd, File* file_system) {
    //cout << "Read File System" << endl;

    int fd = open(param.file_fsystem.c_str(), O_RDONLY);
    if (fd < 0) {
        cerr << "Error: Cannot open file system file" << endl;
        return;
    }

    off_t offset = lseek(fd, param_cd.block_size, SEEK_SET);
    if (offset == (off_t)-1) {
        cerr << "Error seeking to file entries" << endl;
        close(fd);
        return;
    }


    read_file_entry(file_system, fd, param_cd);

    close(fd);

}

bool dir_file(File* current_directory, const string& target_path, const string& current_path = "") {

    string effective_path = current_path.empty() ? "/" : current_path;
    
    cout << "Current Path: " << effective_path << endl;
    cout << "Target Path: " << target_path << endl;
    
    if (effective_path == target_path) {
        cout << "Found the directory: " << current_directory->get_name() << "\n";
        // Found the directory, now list its contents
        Directory* dir = dynamic_cast<Directory*>(current_directory);
        if (dir) {
            Print_Path(*dir);
        }
        return true;
    }

    // If it's a directory, search within it
    Directory* dir = dynamic_cast<Directory*>(current_directory);
    if (dir) {
        vector<File*> subfiles = dir->getFiles();
        for (auto subfile : subfiles) {
            string new_path = effective_path == "/" ? effective_path + subfile->get_name() : effective_path + "/" + subfile->get_name();
            if (dir_file(subfile, target_path, new_path)) {
                return true;
            }
        }
    }

    return false;
}



int main(int argc, char** argv) {

    Paramater_oper param;
    Paramater_CD param_cd;
    take_input_oper(param, argc, argv);
    cout << "Program Name: " << param.program_name << endl;
    cout << "File System Name: " << param.file_fsystem << endl;
    cout << "Operation: " << param.operation << endl;
    cout << "Paramater 1: " << param.paramaters[0] << endl;
    cout << "Paramater 2: " << param.paramaters[1] << endl;

    Directory file_system("root", 0, time(nullptr));
    read_superblock(param, param_cd);
    read_file_system(param, param_cd, &file_system);
    
    
    if (param.operation == DUMPE2FS) {
        cout << "========================File System Read=============================" << endl;
        Print_Path(file_system);
        cout << "======================================================================" << endl;

    } else if (param.operation == DIREC) {
        cout << "Dump2fs Function" << endl;
        
        string target_path;

        for (int i = 0; i < param.paramaters[0].size() -6; i++) {
            target_path += param.paramaters[0][i+3];
        }
        cout << "Target Path: " << target_path << endl;
        
        if (!dir_file(&file_system, target_path)) {
            cout << "Directory not found.\n";
        }

    } else if (param.operation == READ) {
        cout << "Read Function" << endl;

        // TO DO: Implement read operation

    } else {
        cerr << "Invalid operation" << endl;
    }
    return 0;
}



