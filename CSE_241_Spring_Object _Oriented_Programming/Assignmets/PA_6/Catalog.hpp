#ifndef CATALOG_HPP
#define CATALOG_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include <string>



class Catalog {
protected:
    string title;
    int year;

public:
    Catalog();
    Catalog(const string& new_title, int new_year);
    Catalog(const Catalog& copy);
    Catalog(const Catalog&& copy);
    virtual ~Catalog();

    // Getter and Setter
    string getTitle() const;
    void setTitle(const string& new_title);

    int getYear() const;
    void setYear(int new_year);

    Catalog& operator=(const Catalog& assign);

    string trim_string(const string& str);

    friend bool operator==(const Catalog& first, const Catalog& second);

  
    virtual bool check_field(string& control) = 0;

    virtual void take_variable(fstream& file , string& control) = 0;

    virtual void print() = 0;

    virtual void f_print(fstream& file) = 0;

    virtual void trim_member() = 0;

};

#endif
