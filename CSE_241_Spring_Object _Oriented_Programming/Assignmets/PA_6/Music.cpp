#include "Music.hpp"

Music::Music(): Catalog(){

}

Music::Music(const string& new_title, const vector<string>& new_artists, int new_year, const vector<string>& new_genre)
    : Catalog(new_title, new_year), artists(new_artists), genre(new_genre) {

}

Music::Music(const Music& copy): Catalog(copy.title,copy.year){
    artists = copy.artists;
    genre = copy.genre;
}

Music::Music(const Music&& copy) : Catalog(copy.title, copy.year),
artists(copy.artists), genre(copy.genre)
{

}

Music::~Music(){

}

vector<string> Music::getArtists() const {
    return artists;
}

void Music::setArtists(const vector<string>& new_artists) {
    artists = new_artists;
}

vector<string> Music::getGenre() const {
    return genre;
}

void Music::setGenre(const vector<string>& new_genre) {
    genre = new_genre;
}


Music& Music::operator=(const Music& assign){

    if(this == &assign){
        return *this;
    }

    artists = assign.artists;
    genre = assign.genre;

    setTitle(assign.title);
    setYear(assign.year);

    return *this;
}

// Implementation of operator[] for artists (read-only)
const string& Music::operator[](size_t index) const {
    return artists[index];
}

// Implementation of operator[] for artists (write)
string& Music::operator[](size_t index) {
    return artists[index];
}

// Implementation of operator[] for genre (read-only)
const string& Music::operator()(size_t index) const {
    return genre[index];
}

// Implementation of operator[] for genre (write)
string& Music::operator()(size_t index) {
    return genre[index];
}



// Implementation of operator << for appropriate format in the PDF
ostream& operator<<(ostream& out, const Music& music) {

    out << "\"" << music.getTitle() << "\"";
    out << " ";

    out << "\"";
    const vector<string>& artists = music.getArtists();
    for (size_t i = 0; i < artists.size(); i++) {
        out << artists[i];
        if (i != artists.size() - 1)
            out << ",";
    }
    out << "\"";

    out << " ";

    out << "\"" << music.getYear() << "\"";
    out << " ";

    out << "\"";
    const vector<string>& genre = music.getGenre();
   
    for (size_t i = 0; i < genre.size(); i++) {
        out << genre[i] ;
        if (i != genre.size() - 1)
            out << ",";
    }
    out << "\"";

    out << endl; 
    return out;
}

// Implementation of operator << for appropriate format in the PDF
fstream& operator<<(fstream& out, const Music& music) {

    out << "\"" << music.getTitle() << "\"";
    out << " ";

    out << "\"";
    const vector<string>& artists = music.getArtists();
    for (size_t i = 0; i < artists.size(); i++) {
        out << artists[i];
        if (i != artists.size() - 1)
            out << ", ";
    }
    out << "\"";

    out << " ";

    out << " \"" << music.getYear() << "\"";
    out << " ";

    out << "\"";
    const vector<string>& genre = music.getGenre();
   
    for (size_t i = 0; i < genre.size(); i++) {
         out << "\"" << genre[i] << "\"";
        if (i != genre.size() - 1)
            out << ",";
    }
    out << "\"";

    out << endl; 
    return out;
}

//cehck the fields by counting the ""
bool Music::check_field(string& control){
    
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
void Music::take_variable(fstream& file , string& control){
    
        // it count " and according to number program decide that string from main string char

    int counter = 0;
    int num_art = 0;
    int num_genre =0;

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
                    num_art++;
                }
                else{
                    artists.resize(num_art + 1);
                    artists[num_art].push_back(i);
                }
            }
            //converting to integer one by one
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
                    num_genre ++;
                }
                else{
                    genre.resize(num_genre + 1);
                    genre[num_genre].push_back(i);
                }
            }
            else{
            }
        }
    }
    trim_member();

}

// to use pure virtual function

void Music::print(){
    cout << *this;
}
// to use pure virtual function

void Music::f_print(fstream& file){
    file << *this;
}

// reduce unnecesarry space
void Music::trim_member() {

    for (string& artis : artists) {
        artis = trim_string(artis);
    }

    for (string& g : genre) {
        g = trim_string(g);
    }
}

bool operator==(const Music& first,const Music& second){
    
    cout << "comparison result" << endl;
    if(first.getTitle()== second.getTitle()){
        return true;
    }

    return false;
}
