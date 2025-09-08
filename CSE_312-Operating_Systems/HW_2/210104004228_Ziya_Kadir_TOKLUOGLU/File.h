#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <ctime>
#include <cstring>  // For memcpy

using namespace std;

typedef struct file_entry{
    char name[20];       // 20 bytes for name
    char date[20];       // 10 bytes for date in YYYY-MM-DD
    char time[20];       // 10 bytes for time in HH:MM:SS
    int64_t size;      // 8 byte for file size
    int64_t start_block; // 8 byte for start block
    char type;
    int number_sub_files = 1;         // 1 byte for type (0 for file, 1 for directory)

    ostream &operator<<(ostream &os) {
        os << "Name: " << name << endl;
        os << "Date: " << date << endl;
        os << "Time: " << time << endl;
        os << "Size: " << size << " bytes" << endl;
        os << "Start Block: " << start_block << endl;
        os << "Type: " << type << endl;
        os << "Number of Subfiles: " << number_sub_files << endl;
        return os;
    }

    file_entry& operator=(const file_entry& other) {
        if (this == &other) {
            return *this;
        }
        memcpy(this, &other, sizeof(file_entry));
        return *this;
    }
    
} file_entry;



class File {
public:
    File(const char name[20] = "", int64_t size = 0, time_t modTime = 0, File* parent = nullptr);
    virtual ~File();  // Virtual to allow inheritance

    static int entry_size;  // Size of each entry in the file system

    const char* get_name() const;
    const char* get_date() const;
    const char* get_time() const;
    int64_t get_start_block() const;
    int64_t get_size() const;

    File* get_parent() const;
    virtual char get_type() const;

    file_entry get_entry() const;
    void set_entry(file_entry entry);


    virtual void add_file(File* file);

    void set_name(const char name[20]);
    void set_date(const char date[10]);
    void set_time(const char time[10]);

    void set_start_block(int64_t start_block);
    void set_size(int64_t size);
    void set_type(char type);
    void set_parent(File* parent);
    virtual int get_number_of_subfiles() const;
    virtual void set_number_of_subfiles(int number_of_subfiles);

protected:

    file_entry entry;
    File* parent;        // Pointer to parent file

    void formatDateTime(time_t rawTime);
};

#endif // FILE_H
