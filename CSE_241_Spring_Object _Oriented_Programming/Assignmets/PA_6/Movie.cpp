#include "Movie.hpp"

Movie::Movie(): Catalog(){

}
Movie::Movie(const string& new_title, const string& new_director, int new_year, const vector<string>& new_genre, const vector<string>& new_starring)
    : Catalog(new_title, new_year), director(new_director), starring(new_starring), genre(new_genre) {

}

Movie::Movie(const Movie& copy) : director(copy.director), starring(copy.starring) ,genre(copy.genre)
, Catalog(copy.title,copy.year){

}

Movie::Movie(const Movie&& copy) : Catalog(copy.title, copy.year){
    director = copy.director;
    starring = copy.starring;
    genre = copy.genre;
}

Movie::~Movie(){

}


string Movie::getDirector() const {
    return director;
}

void Movie::setDirector(const string& new_director) {
    director = new_director;
}

vector<string> Movie::getStarring() const {
    return starring;
}

void Movie::setStarring(const vector<string>& new_starring) {
    starring = new_starring;
}

vector<string> Movie::getGenre() const {
    return genre;
}

void Movie::setGenre(const vector<string>& new_genre) {
    genre = new_genre;
}


Movie& Movie::operator=(const Movie& assign){
    
    if (this == &assign){
        return *this;
    }

    director = assign.director;
    starring = assign.starring;
    genre = assign.genre;

    setTitle(assign.title);
    setYear(assign.year);

    return *this;
}

// Implementation of operator[] for starring (read-only)
const string& Movie::operator[](size_t index) const {
    return starring[index];
}

// Implementation of operator[] for starring (write)
string& Movie::operator[](size_t index) {
    return starring[index];
}

// Implementation of operator[] for genre (read-only)
const string& Movie::operator()(size_t index) const {
    return genre[index];
}

// Implementation of operator[] for genre (write)
string& Movie::operator()(size_t index) {
    return genre[index];
}


ostream& operator<<(ostream& out, const Movie& movie) {
    out << "\"" << movie.getTitle() << "\"";
    out << " ";

    out << "\"";
    out << movie.getDirector();
    out << "\"";

    out << " ";

    out << "\"";
    const vector<string>& starring = movie.getStarring();
    for (size_t i = 0; i < starring.size(); i++) {
        out << starring[i];
        if (i != starring.size() - 1)
            out << ", ";
    }
    out << "\"";

    out << " \"" << movie.getYear() << "\"";
    out << " ";

    out << "\"";
    const vector<string>& genre = movie.getGenre();
    for (size_t i = 0; i < genre.size(); i++) {
        out << genre[i];
        if (i != genre.size() - 1)
            out << ", ";
    }
    out << "\"";

    out << endl;
    return out;
}

fstream& operator<<(fstream& out, const Movie& movie) {
    out << "\"" << movie.getTitle() << "\"";
    out << " ";

    out << "\"";
    out << movie.getDirector();
    out << "\"";

    out << " ";

    out << "\"";
    const vector<string>& starring = movie.getStarring();
    for (size_t i = 0; i < starring.size(); i++) {
        out << starring[i];
        if (i != starring.size() - 1)
            out << ", ";
    }
    out << "\"";

    out << " \"" << movie.getYear() << "\"";
    out << " ";

    out << "\"";
    const vector<string>& genre = movie.getGenre();
    for (size_t i = 0; i < genre.size(); i++) {
        out << genre[i];
        if (i != genre.size() - 1)
            out << ", ";
    }
    out << "\"";

    out << endl;
    return out;
}

//cehck the fields by counting the ""
bool Movie::check_field(string& control){
    
    int counter = 0;
    for (auto i : control){
        if(i == '"'){
            counter ++;
        }
    }

    if ((counter / 2) == 5 && (counter % 2 == 0)){
        return true;
    }
    else{
        return false;
    }

    return false;
}

// take variable accorrding to PDf format and my class member
void Movie::take_variable(fstream& file , string& control){
    
    // it count " and according to number program decide that string from main string char

    int counter = 0;
    int num_genre = 0;
    int num_starring =0;

    for(auto i: control){
        if(i == '"'){
            counter++;
        }
        else{
            if(counter == 1){
                title.push_back(i);
            }
            else if(counter == 3){
                director.push_back(i);
            }
            //convert to string one by one
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
                    num_genre++;
                }
                else{
                    genre.resize( num_genre + 1);
                    genre[ num_genre].push_back(i);
                }
            }
            else if(counter == 9){
                if(i == ','){
                    num_starring ++;
                    if(i++ == ' '){
                        continue;
                    }
                }
                else{
                    starring.resize(num_starring  + 1);
                    starring[num_starring].push_back(i);
                }
            }
            else{
                
            }
        }
    }
    trim_member();

}


// to use pure virtual function

void Movie::print(){
    cout << *this;
}

// to use pure virtual function

void Movie::f_print(fstream& file){
    file << *this;
}

// reduce unnecesarry space
void Movie::trim_member() {
    director = trim_string(director);

    for (string& actor : starring) {
        actor = trim_string(actor);
    }

    for (string& g : genre) {
        g = trim_string(g);
    }
}

