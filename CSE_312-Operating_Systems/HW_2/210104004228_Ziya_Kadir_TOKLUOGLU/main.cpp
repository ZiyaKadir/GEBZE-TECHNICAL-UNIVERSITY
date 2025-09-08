#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <ctime>
#include <fcntl.h>
#include <unistd.h>

#include "Helper_functions.h"
#include "Directory.h"
#include "File.h"



using namespace std;

#define MAX_SIZE_CD 16*1024*1024 // 16 MB

int File::entry_size = 64; // 64 bytes

int block_number = 0;

void create_superblock(const string& filename, int block_size, int Total_Entry_size, int necessary_blocks){
    int fd = open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0){
        cerr << "Error: Cannot create superblock file" << endl;
        return;
    }

    int64_t max_bytes = MAX_SIZE_CD;
    int64_t total_blocks = max_bytes / block_size;
    
    // Write max_bytes and total_blocks to the superblock file
    write(fd, &max_bytes, sizeof(max_bytes)); // Write max_bytes to the file
    write(fd, &total_blocks, sizeof(total_blocks)); // Write total_blocks to the file
    write(fd, &block_size, sizeof(block_size)); // Write block_size to the file
    write(fd, &Total_Entry_size, sizeof(Total_Entry_size)); // Write Total_Entry_size to the file
    write(fd, &necessary_blocks, sizeof(necessary_blocks)); // Write necessary_blocks to the file for file entries

cout << "==========================================" << endl;
    cout << "Max Bytes = " << max_bytes << endl;
    cout << "Total Blocks = " << total_blocks << endl;
    cout << "Block Size = " << block_size << endl;
    cout << "Total Entry Size = " << Total_Entry_size << endl;
    cout << "Necessary Blocks = " << necessary_blocks << endl;
cout << "==========================================" << endl;


    block_number++;

    close(fd);
}


void create_file_entry(const int fd, File& root){
    file_entry entry;
    if (fd < 0) {
        cerr << "Error: Invalid file descriptor" << endl;
        return;
    }

    //cout << "Creating Block Number = " << block_number << endl;

    entry = root.get_entry();
    //off_t offset;
    off_t offset = lseek(fd, 0, SEEK_CUR);
    // cout << "Current Offset = " << offset << endl;
    /*
    cout << "Entry Name = " << entry.name << endl;
    cout << "Entry Date = " << entry.date << endl;
    cout << "Entry Time = " << entry.time << endl;
    cout << "Entry Size = " << entry.size << endl;
    cout << "Entry Start Block = " << entry.start_block << endl;
    cout << "Entry Type = " << entry.type << endl;
    cout << "Entry Number of Subfiles = " << entry.number_sub_files << endl;

    */
    ssize_t bytes_written = write(fd, &entry, sizeof(file_entry));
    //cout << "Bytes written = " << bytes_written << endl;
    //cout << "Size of file entry = " << sizeof(file_entry) << endl;
    if (bytes_written != sizeof(file_entry)) {
        cerr << "Failed to write file entry: " << strerror(errno) << endl;
        return;
    }

    offset = lseek(fd, 0, SEEK_CUR);
    //cout << "Current Offset after write = " << offset << endl;

    // Check if it's a directory and recursively write contents
    if (root.get_type() == '1') {
        Directory* temp = dynamic_cast<Directory*>(&root);
        if (temp != nullptr) {
            for (int i = 0; i < temp->getNumFiles(); i++) {
                create_file_entry(fd, *(temp->getFiles()[i]));
            }
        }
    }
}


void fill_actual_files(File& root, int fd, int block_size, string path = "/home/ziya/Desktop/OS_HW1"){

    //cout << "Type = " << root.get_type() << endl;
    
    if (root.get_type() == '1'){
        Directory* temp = dynamic_cast<Directory*>(&root);
        for (int i = 0; i < temp->getNumFiles(); i++){
            fill_actual_files(*(temp->getFiles()[i]), fd, block_size, path + "/" + temp->getFiles()[i]->get_name());
        }
    }
    else{
        int file_fd = open(path.c_str(), O_RDONLY);
        if (file_fd < 0){
            cerr << "Error: Cannot open file " << path + "/" + root.get_name() << endl;
            return;
        }

        //cout << "File Name = " << path << endl;
        int necessary_blocks = (root.get_size() /  block_size) + 1;

        block_number += necessary_blocks;

        root.set_start_block(block_number);

        
        // Write the actual file to the file system
        lseek(fd, block_number * block_size, SEEK_SET);

        char transfer; 
        for (int i = 0; i < root.get_size() ; i++){    
            transfer = read(file_fd, &transfer, 1);
            write(fd, &transfer, 1);
        }



        close(file_fd);
    }

}


void create_CD_ROM(File &root, Paramater_create &param){
   
    //cout << "Directory = " << root.get_name() << " , Size = " << root.get_size() << endl;


    if (root.get_size() > MAX_SIZE_CD){
        cerr << "Error: File System is too big not fit to CD" << endl;
        return;
    }
    
    int Total_Entry_size = root.get_number_of_subfiles() * File::entry_size;
    int necessary_blocks = Total_Entry_size / (param.size_fsystem * 1024);
 
    create_superblock(param.file_fsystem, param.size_fsystem * 1024, Total_Entry_size, necessary_blocks + 1);

    int fd = open(param.file_fsystem.c_str(), O_WRONLY);
    
    lseek(fd, block_number * param.size_fsystem * 1024, SEEK_SET);
    
    int tmp_block = block_number;
    create_file_entry(fd, root);
    block_number += necessary_blocks;
      
    fill_actual_files(root, fd, param.size_fsystem *1024 ,param.path_file);
 
    block_number = tmp_block;
    lseek(fd, block_number * param.size_fsystem * 1024, SEEK_SET);
    create_file_entry(fd, root);
    
    close(fd);
}

int main(int argc, char** argv) {
   

    cout << "File class size = " << sizeof(File) << endl;
    Paramater_create param;
    int start = take_input_create(param, argc, argv);
    cout << "Program Name: " << param.program_name << endl;
    cout << "Size of File System: " << param.size_fsystem << endl;
    cout << "File System Name: " << param.file_fsystem << endl;
    cout << "Path of File: " << param.path_file << endl;

    if (start < 0){
        cout << "Error: " << start << endl;
        return 0;
    }

    //create a CD-ROM object with the given size

    string dirPath(param.path_file);
    // ("/" + param.program_name).c_str()
    Directory rootDirectory( "", 0, time(nullptr));  // Create root directory object with current time
    takeDirectory(dirPath, rootDirectory);  // Start listing from the given path

    //Print (rootDirectory);

    create_CD_ROM(rootDirectory, param);

    cout << "========================File System Write=============================" << endl;
    Print(rootDirectory);
    cout << "======================================================================" << endl;
    // After processing, you can interact with the rootDirectory object to manipulate or query the file system

    return 0;
}
