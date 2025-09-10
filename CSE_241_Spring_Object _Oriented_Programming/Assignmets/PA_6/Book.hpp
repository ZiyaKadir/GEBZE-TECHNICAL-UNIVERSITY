#ifndef BOOK_HPP
#define BOOK_HPP

#include "Catalog.hpp"



class Book : public Catalog {
private:
    vector<string> authors;
    vector<string> tags;

public:
    Book();
    Book(const string& new_title , const vector<string>& new_author, int new_year, const vector<string>& new_tags);
    Book(const Book& copy);
    Book(const Book&& copy);
    ~Book();

    Book& operator=(const Book& assign);

    vector<string> getAuthors() const;
    void setAuthors(const vector<string>& new_author);

    vector<string> getTags() const;
    void setTags(const vector<string>& new_tags);


    // Declaration for operator[] on authors (read-only)
    const string& operator[](size_t index) const;

    // Declaration for operator[] on authors (write)
    string& operator[](size_t index);

    // Declaration for operator[] on tags (read-only)
    const string& operator()(size_t index) const;

    // Declaration for operator[] on tags (write)
    string& operator()(size_t index);

    friend ostream& operator<<(ostream& out, const Book& book);

    friend fstream& operator<<(fstream& out, const Book& book);

    bool check_field(string& control) override;

    void take_variable(fstream& file , string& control) override;

    void f_print(fstream& file);

    void print();

    void trim_member() override;



};

#endif
