#ifndef MUSIC_HPP
#define MUSIC_HPP

#include "Catalog.hpp"


using namespace std;

class Music : public Catalog {
private:
    vector<string> artists;
    vector<string> genre;

public:
    Music();
    Music(const string& new_title, const vector<string>& new_artists, int new_year, const vector<string>& new_genre);
    Music(const Music& copy);
    Music(const Music&& copy);
    ~Music();

    Music& operator=(const Music& assign);

    vector<string> getArtists() const;
    void setArtists(const vector<string>& new_artists);

    vector<string> getGenre() const;
    void setGenre(const vector<string>& new_genre);

    // Declaration for operator[] on artists (read-only)
    const string& operator[](size_t index) const;

    // Declaration for operator[] on artists (write)
    string& operator[](size_t index);

    // Declaration for operator[] on genre (read-only)
    const string& operator()(size_t index) const;

    // Declaration for operator[] on genre (write)
    string& operator()(size_t index);

    //Decleration of operator<< for appropriate format in the PDF
    friend ostream& operator<<(ostream& os, const Music& music);

    //Decleration of operator<< for appropriate format in the PDF
    friend fstream& operator<<(fstream& os, const Music& music);

    bool check_field(string& control) override;

    void take_variable(fstream& file , string& control) override;

    void trim_member() override;

    friend bool operator==(const Music& first, const Music& second);

    void f_print(fstream& file);

    void print();

};

#endif