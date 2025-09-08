#include "Directory.h"

Directory::Directory(const char name[20], int64_t size, time_t modTime, File* parent)
: File(name, size, modTime, parent) {
    set_type('1');  // '1' for directory
}

Directory::~Directory() {
    for (auto file : files) {
        delete file;  // Ensure no memory leaks
    }
}

void Directory::add_file(File* file) {

    //cout << "Adding file " << file->get_name() << " to directory " << get_name() << endl;
    if (file) {
        files.push_back(file);
        file->set_parent(this);  // Set this directory as the parent
        this->set_size(get_size() + file->get_size());
        this->set_number_of_subfiles(this->get_number_of_subfiles() + file->get_number_of_subfiles());
    }
}

const vector<File*>& Directory::getFiles() const {
    return files;
}

int Directory::getNumFiles() const {
    return files.size();
}

int Directory::get_number_of_subfiles() const {
    return entry.number_sub_files;
}

vector<File*>& Directory::getFiles() {
    return files;
}


void Directory::set_number_of_subfiles(int number_of_subfiles) {
    entry.number_sub_files = number_of_subfiles;
}


File* Directory::operator[](int index) const {
    if (index >= 0 && index < static_cast<int>(files.size())) {
        return files[index];
    }
    return nullptr;
}
