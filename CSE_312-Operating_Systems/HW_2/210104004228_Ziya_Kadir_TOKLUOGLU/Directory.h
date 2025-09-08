#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "File.h"
#include <vector>
#include <ctime>

using namespace std;

class Directory : public File {
public:
    //Directory(const char name[20], int64_t size, char modTime, File* parent = nullptr);
    Directory(const char name[20], int64_t size = 0, time_t modTime = 0, File* parent = nullptr);
    virtual ~Directory();

    virtual void add_file(File* file) override;  // Override to add file-specific functionality
    const vector<File*>& getFiles() const;
    int getNumFiles() const;

    int get_number_of_subfiles() const;
    void set_number_of_subfiles(int number_of_subfiles);
    
    vector<File*>& getFiles();
    
    File* operator[](int index) const;

private:
    vector<File*> files;  // Using pointers to manage file objects
};

#endif // DIRECTORY_H
