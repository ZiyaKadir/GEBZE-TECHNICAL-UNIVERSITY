#ifndef MOVIE_HPP
#define MOVIE_HPP

#include "Catalog.hpp"


using namespace std;

class Movie : public Catalog {
private:
    string director;
    vector<string> starring;
    vector<string> genre;

public:
    Movie();
    Movie(const string& new_title, const string& new_director, int new_year, const vector<string>& new_genre, const vector<string>& new_starring);
    Movie(const Movie &copy);
    Movie(const Movie &&copy);
    ~Movie();

    Movie& operator=(const Movie& assign);

    string getDirector() const;
    void setDirector(const string& new_director);

    vector<string> getStarring() const;
    void setStarring(const vector<string>& new_starring);

    vector<string> getGenre() const;
    void setGenre(const vector<string>& new_genre);

     void trim_member() override;


    // Declaration for operator[] on starring (read-only)
    const string& operator[](size_t index) const;

    // Declaration for operator[] on starring (write)
    string& operator[](size_t index);

    // Declaration for operator[] on genre (read-only)
    const string& operator()(size_t index) const;

    // Declaration for operator[] on genre (write)
    string& operator()(size_t index);

    friend ostream& operator<<(ostream& out, const Movie& movie);

    friend fstream& operator<<(fstream& out, const Movie& movie);

    // friend bool operator==(const Movie& lhs, const Movie& rhs);


    bool check_field(string& control) override;

    void take_variable(fstream& file , string& control) override;

    void print();

    void f_print(fstream& file);


};

#endif
