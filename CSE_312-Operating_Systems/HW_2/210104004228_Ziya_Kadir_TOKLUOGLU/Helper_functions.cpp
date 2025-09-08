#include "Helper_functions.h"

using namespace std;

int str_cmp(const char* str1, const char* str2){
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i] != str2[i]){
            return 0;
        }
        i++;
    }
    if(str1[i] != '\0' || str2[i] != '\0'){
        return 1;
    }
    return 1;
}

int take_input_create(Paramater_create &param, int argc, char** argv){

    if(argc >= 3 && argc <= 5){
        param.program_name = argv[0];

        if(param.program_name == "./makeFileSystem"){
            if (argc != 4) return -1;

            cout << "Make File System Function"<< endl;
            param.size_fsystem = atoi(argv[1]);
            param.file_fsystem = argv[2];
            param.path_file = argv[3];
        }
        else{
            return -2;
        }
    }
    param.program_name = argv[0] + 2;
    return 0;
}


int take_input_oper(Paramater_oper &param, int argc, char** argv){

    if(argc >= 3 && argc <= 5){
        param.program_name = argv[0];

        if(param.program_name == "./fileSystemOper"){
            param.file_fsystem = argv[1];

            cout << "argv operation = " << argv[2] << endl;
            
            if(str_cmp(argv[2], "dir")){
                cout << "DIR Function"<< endl;
                if (argc != 4) return -1;
                param.operation = DIREC;
                param.paramaters[0] = argv[3];
            }
            else if(str_cmp(argv[2], "dumpe2fs")){
                cout << "Dump2fs Function"<< endl;
                if (argc != 3) return -1;
                param.operation = DUMPE2FS;
                //param.paramaters[0] = argv[3];
            }
            else if(str_cmp(argv[2], "read")){
                cout << "Read Function"<< endl;
                if (argc != 5) return -1;
                param.operation = READ;
                param.paramaters[0] = argv[3];
                param.paramaters[1] = argv[4];
            }
            else{
                return -2;
            }
        }
        else{
            return -2;
        }
    }
    return 0;
}


void Print(File& root){

    //cout << "Root Type: " << root.get_type() << endl;

    if (root.get_type() == '1'){
        cout << "Directory = " << root.get_name() << "Size =" << root.get_size() << endl;
        Directory* temp = dynamic_cast<Directory*>(&root);

        for (int i = 0; i < temp->getNumFiles(); i++){
            Print(*(temp->getFiles()[i]));
        }
    }
    else{
        cout << "File = " << root.get_name() << "Size ="<< root.get_size() << endl;
    }
   
}

void Print_Path(File& root){

    if (root.get_type() == '1'){
        cout << "Directory >>  " << root.get_name() << endl;
        Directory* temp = dynamic_cast<Directory*>(&root);

        for (int i = 0; i < temp->getNumFiles(); i++){
            Print_Path(*(temp->getFiles()[i]));
        }
    }
    else{
        cout << "File >>  " << root.get_name() << endl;
    }

}



// Recursively list files and directories from a given path and add them to the parent directory object
void takeDirectory(const string& dirPath, Directory& parentDirectory) {

    DIR* dir = opendir(dirPath.c_str());

    if (dir == nullptr) {
        cerr << "Failed to open directory: " << dirPath << endl;
        return;
    }
    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string entryName = entry->d_name;
        if (entryName == "." || entryName == "..") continue;  // Skip . and .. entries

        string fullPath = dirPath + "/" + entryName;
        struct stat entryStat;
        if (stat(fullPath.c_str(), &entryStat) == -1) {
            cerr << "Failed to get stat for: " << fullPath << endl;
            continue;
        }

        if (entryName.size() >= 20){
            cerr << "File name is too long: " << entryName << endl;
            continue;
        }

        if (S_ISDIR(entryStat.st_mode)) {  // If the entry is a directory
            Directory* newDir = new Directory(entryName.c_str(), 0, entryStat.st_mtime);
            takeDirectory(fullPath, *newDir);
            parentDirectory.add_file(newDir);
        } else if (S_ISREG(entryStat.st_mode)) {  // If the entry is a file

            File* newFile = new File(entryName.c_str(), entryStat.st_size, entryStat.st_mtime);
            parentDirectory.add_file(newFile);
        }
    }
    closedir(dir);
}

