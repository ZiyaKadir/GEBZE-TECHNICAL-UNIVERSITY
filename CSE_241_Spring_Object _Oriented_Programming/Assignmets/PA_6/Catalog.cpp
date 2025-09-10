#include "Catalog.hpp"

Catalog::Catalog(){
    year = 0;

}

Catalog::Catalog(const string& new_title, int new_year)
    : title(new_title), year(new_year){

}

Catalog::Catalog(const Catalog& copy){
    year = copy.year;
    title = copy.title;
}

Catalog::Catalog(const Catalog&& copy) : year(copy.year), title(copy.title){

}

Catalog::~Catalog(){
}

string Catalog::getTitle() const {
    return title;
}

void Catalog::setTitle(const string& new_title) {
    title = new_title;
}

int Catalog::getYear() const {
    return year;
}

void Catalog::setYear(int new_year) {
    year = new_year;
}

Catalog& Catalog::operator=(const Catalog& assign){

    if (this == &assign){
        return *this;
    }
    title = assign.title;
    year = assign.year;

    return *this;
}

//reduce unnecesaary spaces
string Catalog::trim_string(const string& str) {
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    
    if (start == string::npos) {
        // The string only contains spaces
        return "";
    }
    return str.substr(start, end - start + 1);
}

bool operator==(const Catalog& first, const Catalog& second){

    if(first.getTitle() == second.getTitle()){
        return true;
    }
    else{
        return false;
    }

    return false;
}

