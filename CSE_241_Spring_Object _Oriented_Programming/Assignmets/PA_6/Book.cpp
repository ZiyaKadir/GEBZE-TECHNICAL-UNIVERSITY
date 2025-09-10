#include "Book.hpp"

Book::Book(): Catalog(){
    

}

Book::Book(const string& new_title, const vector<string>& new_author, int new_year, const vector<string>& new_tags)
    : Catalog(new_title, new_year), authors(new_author), tags(new_tags) {}


Book::Book(const Book& copy): Catalog(copy.title, copy.year), 
authors(copy.authors), tags(copy.tags){

}

Book::Book(const Book&& copy) : Catalog(copy.title, copy.year){
    authors = copy.authors;
    tags = copy.tags;
}

Book::~Book(){

}


vector<string> Book::getAuthors() const {
    return authors;
}

void Book::setAuthors(const vector<string>& new_author) {
    authors = new_author;
}

vector<string> Book::getTags() const {
    return tags;
}

void Book::setTags(const vector<string>& new_tags) {
    tags = new_tags;
}

Book& Book::operator=(const Book& assign){

    if(this == &assign){
        return *this;
    }
    
    authors = assign.authors;
    tags = assign.tags;

    setTitle(assign.title);
    setYear(assign.year);

    return *this;
}

// Implementation of operator[] for authors (read-only)
const string& Book::operator[](size_t index) const {
    return authors[index];
}

// Implementation of operator[] for authors (write)
string& Book::operator[](size_t index) {
    return authors[index];
}

// Implementation of operator[] for tags (read-only)
const string& Book::operator()(size_t index) const {
    return tags[index];
}

// Implementation of operator[] for tags (write)
string& Book::operator()(size_t index) {
    return tags[index];
}

ostream& operator<<(ostream& out, const Book& book) {
    out << "\"" << book.getTitle() << "\"";
    out << " ";

    out << "\"";
    const vector<string>& authors = book.getAuthors();
    for (size_t i = 0; i < authors.size(); i++) {
        out << book[i];
        if (i != authors.size() - 1)
            out << ", ";
    }
    out << "\"";

    out << " \"" << book.getYear() << "\"";
    out << " ";

    out << "\"";
    const vector<string>& tags = book.getTags();
    for (size_t i = 0; i < tags.size(); i++) {
        out << book(i);
        if (i != tags.size() - 1)
            out << ", ";
    }
    out << "\"";

    out << endl;
    return out;
}


// Implementation of operator << for appropriate format in the PDF

fstream& operator<<(fstream& out, const Book& book) {
    out << "\"" << book.getTitle() << "\"";
    out << " ";

    out << "\"";
    const vector<string>& authors = book.getAuthors();
    for (size_t i = 0; i < authors.size(); i++) {
        out << book[i];
        if (i != authors.size() - 1)
            out << ", ";
    }
    out << "\"";

    out << " \"" << book.getYear() << "\"";
    out << " ";

    out << "\"";
    const vector<string>& tags = book.getTags();
    for (size_t i = 0; i < tags.size(); i++) {
        out << book(i);
        if (i != tags.size() - 1)
            out << ", ";
    }
    out << "\"";

    out << endl;
    return out;
}

//cehck the fields by counting the ""
bool Book::check_field(string& control){
    
    int counter = 0;

    for (auto i : control){
        if(i == '"'){
            counter ++;
        }
    }
    if ((counter / 2) == 4 && (counter % 2 == 0)){
        return true;
    }
    else{
        return false;
    }

    return false;
}

// take variable accorrding to PDf format and my class member
void Book::take_variable(fstream& file , string& control){
    
    // it count " and according to number program decide that string from main string char


    int counter = 0;
    int num_aut = 0;
    int num_tag =0;

    for(auto i: control){
        if(i == '"'){
            counter++;
        }
        else{
            if(counter == 1){
                title.push_back(i);
            }
            else if(counter == 3){
                if(i == ','){
                    num_aut++;
                }
                else{
                    authors.resize(num_aut + 1);
                    authors[num_aut].push_back(i);
                }
            }
            // convet to integer
            else if(counter == 5){
                if(i >= '0' && i <= '9'){
                    year *= 10;
                    year += (i-'0');
                }
                else{
                }
            }
            else if(counter == 7){
                if(i == ','){
                    num_tag ++;
                }
                else{
                    tags.resize(num_tag + 1);
                    tags[num_tag].push_back(i);
                }
            }
            else{
            }
        }
    }
    trim_member();

}
// to use pure virtual function
void Book::print(){
    cout << *this;
}
// to use pure virrtual function
void Book::f_print(fstream& file){
    file << *this;
}
// reduce unnecesarry space
void Book::trim_member() {

    for (string& auot : authors) {
        auot = trim_string(auot);
    }

    for (string& t : tags) {
        t = trim_string(t);
    }
}
