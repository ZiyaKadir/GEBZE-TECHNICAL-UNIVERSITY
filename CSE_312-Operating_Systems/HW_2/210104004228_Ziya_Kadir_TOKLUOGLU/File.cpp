#include "File.h"
#include <iomanip>  // For std::put_time
#include <sstream>  // For std::stringstream

File::File(const char name[20], int64_t size, time_t modTime, File* parent)
: parent(parent) {
    memcpy(this->entry.name, name, 20);
    this->entry.size = size;
    this->entry.start_block = 0;
    this->entry.type = '0';  // Default type set to '0' for file
    formatDateTime(modTime);
}

File::~File() {
    // Cleanup if necessary
}

const char* File::get_name() const {
    return entry.name;
}

const char* File::get_date() const {
    return entry.date;
}

const char* File::get_time() const {
    return entry.time;
}

int64_t File::get_size() const {
    return entry.size;
}

int64_t File::get_start_block() const {
    return entry.start_block;
}

File* File::get_parent() const {
    return parent;
}

char File::get_type() const {
    return entry.type;
}

file_entry File::get_entry() const {
    return entry;
}


void File::set_entry(file_entry entry) {
    this->entry = entry;
}

void File::set_type(char type) {
    this->entry.type = type;
}

void File::set_size(int64_t size) {
    this->entry.size = size;
}

void File::set_start_block(int64_t start_block) {
    this->entry.start_block = start_block;
}

void File::set_name(const char name[20]) {
    memcpy(this->entry.name, name, 20);
}

void File::set_date(const char date[10]) {
    memcpy(this->entry.date, date, 10);
}

void File::set_time(const char time[10]) {
    memcpy(this->entry.time, time, 10);
}

void File::add_file(File* file) {
    cerr << "Error: Cannot add file to a non-directory type." << endl;
}

void File::set_parent(File* parent) {
    this->parent = parent;
}

void File::formatDateTime(time_t rawTime) {
    struct tm* timeInfo = localtime(&rawTime);
    strftime(this->entry.date, sizeof(this->entry.date), "%Y-%m-%d", timeInfo);
    strftime(this->entry.time, sizeof(this->entry.time), "%H:%M:%S", timeInfo);
}

int File::get_number_of_subfiles() const {
    return entry.number_sub_files;
}

void File::set_number_of_subfiles(int number_of_subfiles) {
    this->entry.number_sub_files = number_of_subfiles;
}
