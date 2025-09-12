// Creator:  Ziya Kadir TOKLUOGLU
#include "log_operation.h"
#include "secure_file.h"
#include "directory_management.h"


/**
 * @brief 
 * This function prints the manual menu for the user to understand the commands
 */
void Manual_menu() {
    const char *menu[] = {
        "+------------------------------------------+-------------------------------------+\n",
        "| Usage: fileManager <command> <arguments> |                                     |\n",
        "+------------------------------------------+-------------------------------------+\n",
        "| Command                                  | Description                         |\n",
        "+------------------------------------------+-------------------------------------+\n",
        "| createDir \"folderName\"                   | Create a new directory              |\n",
        "| createFile \"fileName\"                    | Create a new file                   |\n",
        "| listDir \"folderName\"                     | List all files in a directory       |\n",
        "| listFilesByExtension \"folder\" \".ext\"     | List files with specific extension  |\n",
        "| readFile \"fileName\"                      | Read a file's content               |\n",
        "| appendToFile \"file\" \"content\"            | Append content to a file            |\n",
        "| deleteFile \"fileName\"                    | Delete a file                       |\n",
        "| deleteDir \"folderName\"                   | Delete an empty directory           |\n",
        "| showLogs                                 | Display operation logs              |\n",
        "+------------------------------------------+-------------------------------------+\n"
    };

    // Change 'int' to 'size_t' to avoid signed-unsigned comparison warning
    for (size_t i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
        write(STDOUT_FILENO, menu[i], strlen(menu[i]));
    }
}



int main(int argc, char *argv[]) {

    mkdir("logs", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
    if (argc == 1 || argc < 2) {
        write(STDOUT_FILENO, "No arguments were given\n", 24);
        write(STDOUT_FILENO, "Please look at the Manual Menu, Start program again!\n", 53);
        Manual_menu();
        return 0;
    } 
    else if (argc == 2) {
        if (strcmp(argv[1], "showLogs") == 0) {
            write(STDOUT_FILENO, "showLogs\n", 9);
            return show_logs();
        } 
        else {
            write(STDOUT_FILENO, "Unknown command. Use fileManager without arguments to see available commands.\n", 77);
            Manual_menu();
        }
    } 
    else if (argc > 2) {
        if (strcmp(argv[1], "createDir") == 0) {
            write(STDOUT_FILENO, "createDir\n", 10);
            return create_directory(argv[2]);
        } 
        else if (strcmp(argv[1], "createFile") == 0) {
            write(STDOUT_FILENO, "createFile\n", 11);
            return create_file(argv[2]);
        } 
        else if (strcmp(argv[1], "listDir") == 0) {
            write(STDOUT_FILENO, "listDir\n", 8);
            return list_directory(argv[2]);
        } 
        else if (strcmp(argv[1], "listFilesByExtension") == 0) {
            write(STDOUT_FILENO, "listFilesByExtension\n", 22);
            return list_files_by_extension(argv[2], argv[3]);
        } 
        else if (strcmp(argv[1], "readFile") == 0) {
            write(STDOUT_FILENO, "readFile\n", 9);
            return read_file(argv[2]);
        } 
        else if (strcmp(argv[1], "appendToFile") == 0) {
            write(STDOUT_FILENO, "appendToFile\n", 13);
            return append_to_file(argv[2], argv[3]);
        } 
        else if (strcmp(argv[1], "deleteFile") == 0) {
            write(STDOUT_FILENO, "deleteFile\n", 11);
            return delete_file(argv[2]);
        } 
        else if (strcmp(argv[1], "deleteDir") == 0) {
            write(STDOUT_FILENO, "deleteDir\n", 10);
            return delete_directory(argv[2]);
        } 
        else {
            write(STDOUT_FILENO, "Unknown command. Use fileManager without arguments to see available commands.\n", 77);
            Manual_menu();
        }
    }

    return 0;
}

