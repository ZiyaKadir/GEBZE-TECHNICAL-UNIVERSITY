#include <iostream>
#include <string>
#include <vector>
#include "Book.hpp"
#include "Movie.hpp"
#include "Music.hpp"
#include "Stack.cpp"

using namespace std;

// Custom exception class for duplicate entry
class DuplicateEntryException : public exception {
public:
    const char* what() const noexcept override {
        return "Exception: Duplicate entry";
    }
};

// Custom exception class for not found entry
class EntryNotFoundException : public exception {
public:
    const char* what() const noexcept override {
        return "Exception: Entry not found";
    }
};
// Custom exception class for Wrong command
class WrongCommandException : public exception {
public:
    const char* what() const noexcept override {
        return "Exception: Wrong command";
    }
};
// Custom exception class for missing field
class MissingField : public exception {
public:
    const char* what() const noexcept override {
        return "Exception: missing filed";
    }
};

//check the main string include sub string or not
bool check_include(const string& mainString, const string& subString) {
    return mainString.find(subString) != string::npos;
}

int main() {

// to hold the duplicate index
        int duplicate;


// these string for conrolling the file string
        string control;
        string catalog_format;
        Stack<Catalog*> data;

// opening the files
        fstream file_log("output.txt", ios::in | ios:: out | ios::trunc);
        fstream file_data("data.txt", ios::in | ios::out);
        getline(file_data, catalog_format);

        file_log << "Catalog Read :" << catalog_format << endl;
        int counter = 0;


// starting file necessary elements
while (!file_data.eof()) {

    getline(file_data, control);

    if (catalog_format == "movie") {
        Catalog* movie = new Movie; //Creating the derived class connecting base class 
        if (movie->check_field(control) == false) { // find missing field 
            try {
                throw MissingField();
            } catch (const MissingField& ex) {
                file_log << ex.what() << endl; // Print exception message
                file_log << control << endl;
                continue; // Handle missing field case
            }
        }
        //after controlling 
        movie->take_variable(file_data, control);
        try {
            bool isDuplicate = false;
            for (size_t i = 0; i < data.get_List().size(); i++) {
                if (*movie == *data[i]) {
                    isDuplicate = true; // to control the duplicate
                    duplicate = i;
                    break;
                }
            }
            if (isDuplicate) {
                throw DuplicateEntryException();
            }
        } catch (const DuplicateEntryException& ex) {
            file_log << ex.what() << endl; // Print exception message
            data[duplicate]->f_print(file_log);
            continue; // Handle duplicate entry case
        }
        data.push(movie);
    } 
    //Actually the maintain else if doing same think only different derived class 
    else if (catalog_format == "music") {
        Catalog* music = new Music;
        if (music->check_field(control) == false) {
            try {
                throw MissingField();
            } catch (const MissingField& ex) {
                file_log << ex.what() << endl; // Print exception message
                file_log << control << endl;

                continue; // Handle missing field case
            }
        }
        music->take_variable(file_data, control);

        try {
            bool isDuplicate = false;
            for (size_t i = 0; i < data.get_List().size(); i++) {
                if (*music == *data[i]) {
                    isDuplicate = true;
                    duplicate = i;
                    break;
                }
            }
            if (isDuplicate) {
                throw DuplicateEntryException();
            }
        } catch (const DuplicateEntryException& ex) {
            file_log << ex.what() << endl; // Print exception message
            data[duplicate]->f_print(file_log);
            continue; // Handle duplicate entry case
        }

        data.push(music);
    } else if (catalog_format == "book") {
        Catalog* book = new Book;
        if (book->check_field(control) == false) {
            try {
                throw MissingField();
            } catch (const MissingField& ex) {
                file_log << ex.what() << endl; // Print exception message
                file_log << control << endl;
                continue; // Handle missing field case
            }
        }
        book->take_variable(file_data, control);
        try {
            bool isDuplicate = false;
            for (size_t i = 0; i < data.get_List().size(); i++) {
                if (*book == *data[i]) {
                    isDuplicate = true;
                    duplicate = i;
                    break;
                }
            }
            if (isDuplicate) {
                throw DuplicateEntryException();
            }
        } catch (const DuplicateEntryException& ex) {
            file_log << ex.what() << endl; // Print exception message
            data[duplicate]->f_print(file_log);
            continue; // Handle duplicate entry case
        }
        data.push(book);
    } else {
        break;
    }
    counter++;
}

        file_data.close();

    file_log << data.get_List().size() << " unique entries" << endl;

        fstream file_command("commands.txt", ios::in | ios::out);


//file controlling variable
// I did not create for command txt because i did not forecast that it is very confusing
        string command_string;
        int num_quoto = 0;
        string command;
        string word;
        string keyword;
        string field;

        while (!file_command.eof()) {

            //reading data like take variable by controlling "" step by step
            getline(file_command, command_string);

            command.clear();
            word.clear();
            keyword.clear();
            field.clear();

            num_quoto = 0;
            for (auto i : command_string) {
                if (i == '"') {
                    num_quoto++;
                } else if (i != ' ' && num_quoto == 0) {
                    command.push_back(i);
                } else if (num_quoto == 1) {
                    word.push_back(i);
                } else if (i != ' ' && num_quoto == 2) {
                    keyword.push_back(i);
                } else if (num_quoto == 3) {
                    field.push_back(i);
                }
            }


            if (command == "search") {
                if (field == "title") {
                    bool found = false;
                    for (size_t i = 0; i < data.get_List().size(); i++) {
                        if (check_include(data[i]->getTitle(), word)) {
                            file_log << "Found entry:" << endl;
                            data[i]->f_print(file_log);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        try{
                        throw EntryNotFoundException(); 
                        }
                        catch (const EntryNotFoundException& ex) {
                          file_log << ex.what() << endl; // Print exception message
                            file_log << command << " \"" << word << "\" " << keyword << " \"" << field << "\"" << endl;
                        }// Throw exception for entry not found
                    }
                }
                else{
                    try{
                    throw WrongCommandException(); // Throw exception for wrong command
                    }
                    catch (const WrongCommandException& ex) {

                        file_log << ex.what() << endl; // Print exception message
                        file_log << command << " \"" << word << "\" " << keyword << " \"" << field << "\"" << endl;
                        // Handle other exceptions
                    } 
                }
            } else if (command == "sort") {
                if (word == "title") {
                    for (size_t i = 0; i < data.get_List().size() - 1; i++) {
                        for (size_t j = 0; j < data.get_List().size() - i - 1; j++) {
                            if (data[j]->getTitle() >= data[j + 1]->getTitle()) {
                                Catalog* temp = data[j];
                                data[j] = data[j + 1];
                                data[j + 1] = temp;
                            }
                        }
                    }

                    for (size_t i = 0; i < data.get_List().size(); i++) {
                        data[i]->f_print(file_log);
                    }
                } else if (word == "year") {

                    file_log << command << "\"year\"" << endl;
                    for (size_t i = 0; i < data.get_List().size() - 1; i++) {
                        for (size_t j = 0; j < data.get_List().size() - i - 1; j++) {
                            if (data[j]->getYear() >= data[j + 1]->getYear()) {
                                Catalog* temp = data[j];
                                data[j] = data[j + 1];
                                data[j + 1] = temp;
                            }
                        }
                    }
                    for (size_t i = 0; i < data.get_List().size(); i++) {
                        data[i]->f_print(file_log);
                    }
                } else {
                    try{
                    throw WrongCommandException(); // Throw exception for wrong command
                    }
                    catch (const WrongCommandException& ex) {

                        file_log << ex.what() << endl; // Print exception message
                        // Handle other exceptions
                    }
                    
                }
            } else {
                try{
                    throw WrongCommandException(); // Throw exception for wrong command
                }
                catch (const WrongCommandException& ex) {

                    file_log << ex.what() << endl; // Print exception message
                    // Handle other exceptions
                }
            }
        }
    file_command.close();
    file_log.close();

    return 0;
}
