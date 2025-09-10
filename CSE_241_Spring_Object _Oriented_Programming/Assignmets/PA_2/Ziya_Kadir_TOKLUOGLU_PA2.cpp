#include<iostream>
#include<fstream>
#include<limits>
#include<iomanip>
#include<vector>
#include<string>

using namespace std;

class Image{

	public:
	Image();
	Image(const string name);

//Getter
	int get_x_axis() const;
	int get_y_axis() const;
//Setter
	void set_x_axis(int x_size);
	void set_y_axis(int y_size);
	void assign_name(const string name);

// controlling file format
	int control_format();

// allocate and take image to vector
	void allocate_vector(int y_axis, int x_axis);
	void take_picture(); // take data from file which contain the picture

// printing vector for control
	void print();
	void fprint(string name)const;

// conver Grayscale
	int con_gray();

	private:

	string file_name;
	vector<vector<vector<int>>> picture; // three dimensional vector first and second dimension for the 2D picture pixel and third for the rgb color  
	int x_picture; // x axis size of picture
	int y_picture; // y axis size of picture
};

class Menus{

	public:

	Menus();


	int Main_menu();
	int control_int(int initial, int last); // control the input integer and make sure integer
	int O_Image_menu(); // Open an image menu
	int S_Image_menu(); // save image data menu
	int Script_menu(); // Script menu
	int Convert_menu(); // Convert to Grayscale menu

	private:
	
	vector<Image> images;
	bool is_file_open;
	int image_number;
	int selection;

};



int main(){



	Menus graph;

	Image image;

	if (graph.Main_menu() == 0){
		return 0;
	}
	
	return 0;
}


// member function's implementation of Menus class

Menus::Menus(){
	selection = -1;
	image_number = 0;
	is_file_open =false;

}


int Menus::control_int(int initial, int last){

	bool control;

	do{
		control = true;
		cin >> selection;

		if (cin.good() == false){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			control = false;
			// return Main_menu();
		}		

		if (!(selection >=initial && selection <= last)){
			control = false;
			// return Main_menu();
		}

	}while(cin.good() ==false || control == false);

	return 0;
}

// Main menu member function

int Menus::Main_menu(){
		
	cout << "MAIN MENU" << endl;
	cout << "0 - Exit" << endl;
	cout << "1 - Open An Image(D)" << endl;
	cout << "2 - Save Image Data(D)" << endl;
	cout << "3 - Scripts(D)" << endl;
	
	control_int(0,3);

	if (selection == 0){
		return 0;
	}
	else if(selection == 1){
		return O_Image_menu();
	}
	else if(selection == 2){
		return S_Image_menu();
	}	
	else if(selection == 3){
		return Script_menu();
	}

	return Main_menu();
}

// Open image member function 

int Menus::O_Image_menu(){

	cout << "OPEN AN IMAGE MENU" << endl;
	cout << "0 - UP" << endl;
	cout << "1 - Enter The Name of The Image File" << endl;
	control_int(0,1);

	if (selection == 0){
		return Main_menu();
	}
	else if(selection == 1){

		string temp;

		int control;

		cin >> temp;

		image_number ++;
		images.resize(image_number);

		images[image_number -1].assign_name(temp);
		
		control = images[image_number -1].control_format();

		if(control == 0){
			images[image_number -1].take_picture();
			// images[image_number -1].print();

			is_file_open = true;
		}
		else{

			// cout << "E" << control << endl;
			is_file_open = false;
			return 0;
		}

		return O_Image_menu();
	}

	return Main_menu();

}

//Save Image member function 

int Menus::S_Image_menu(){
	
	cout << "SAVE IMAGE DATA MENU" << endl;
	cout << "0 - UP" << endl;
	cout << "1 - Enter A File Name" << endl;

	control_int(0,1);

	string temp;

	
	if (selection == 0 || is_file_open == false){
		return Main_menu();
	}
	else if(selection == 1){

		// cout << "Please enter the file name which saved" << endl;
		cin >> temp;

		images[image_number-1].fprint(temp);
		return S_Image_menu();
	}

	return Main_menu();

}

// Script Menu member function

int Menus::Script_menu(){

	cout << "SCRIPTS MENU" << endl;
	cout << "0 - UP" << endl;
	cout << "1 - Convert To Grayscale(D)" << endl;

	control_int(0,1);

	if (selection == 0 || is_file_open == false){
		return Main_menu();
	}
	else if(selection == 1){

		return Convert_menu();
	}
	return Main_menu();

}

// Convert Menu member function

int Menus::Convert_menu(){

	cout << "CONVERT TO GRAYSCALE MENU" << endl;

	cout << "0 - UP" << endl;
	cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels" << endl;

	control_int(0,1);
	int control;

	if (selection == 0){
		return Script_menu();
	}
	else if(selection == 1){

		control = images[image_number -1].con_gray();
		
		if (control == 0){
			
			// images[image_number -1].print();

			return Convert_menu();
		}
		else{
			
			return Main_menu();
		}
		
	}
	return Main_menu();

}

// member function of the Image class

Image::Image(){
	x_picture = 0;
	y_picture = 0;
}

Image::Image(const string name){
	file_name = name;
}

int Image::get_x_axis()const{
	return x_picture;
}
int Image::get_y_axis()const{
	return y_picture;
}

void Image::set_x_axis(int x_size){
	x_picture = x_size;
}
void Image::set_y_axis(int y_size){
	y_picture = y_size;
}
void Image::assign_name(const string name){
	file_name = name;
}


// controlling file format and return the error type

// 1 for the program format is not valid, it is not P3(Ascii format)
// 2 for not integer dimension value
// 3 wrong max color pixel of the picture, it is not 255
// 4 wrong color pixel level of the each pixel
// 5 exceed file data that means that the pixel are wrong about pixel
// 6 for the file name is not valid

// return 0 for the file is ready for openning it did not have absurd value


int Image::control_format(){

	string temp;
	int control , temp_y , temp_x;
	fstream file(file_name, ios::out | ios::in);

	if (file.is_open() == false){
		// cout << "the file is not found" << endl;
		
		return 6;
	}

	file.seekg(-1,ios::end);
	char c;
	c = file.get();
	if ( 10 == int(c)){
	// cout << "previos of the last pointer is end of line" << endl;
	// cout << "the code will work does not need append end of line" << endl;
	}
	else{
		// cout << int(c) << endl;
		// cout << "previos of the last pointer is not end of line" << endl;
		// cout << "to ensure the cin.good() works correctly we have to append end of line on the file " << endl;
		file << endl;
	}

	file.seekg(0,ios::beg);

	file >> temp;

	if ("P3" != temp){
	// cout << "file format is wrong" << endl;
		file.close();
		return 1;
	}

	file >> temp_y;
	file >> temp_x;

	if(file.good() == false){
	
	// cout << "dimension of the image are wrong please control them" << endl;
		file.close();
		return 2;
	}

	file >> control;
	if (file.good() ==false || control != 255){
	
	// cout << "This program works color pixel level for 0-255 this picture's max colot value is unvalid for this program" << endl;
		file.close();
		return 3;
	}

	for (int i=1; i <= temp_x * temp_y * 3 ; i++){
		
		file >> control;

		if(file.fail()){
		
		// cout << "Error encountered while reading file" << endl; 
			return 5;
		}
		else if (file.good() == false ||  control > 255){
		
		// cout << "Rgb index of the file are wrong" << endl;
			file.close();
			return 4;
		}
		
	}

	file.close();
	return 0;

}

void Image::allocate_vector(int y_axis, int x_axis){
	
	picture.resize(y_axis);

	for(int i=0; i < y_axis; i++){
		picture[i].resize(x_axis);
	}

// allocate 3 space for representing the RGB color in  the third dimension of picture
	for (int i=0; i < y_axis; i++){
		for (int k=0; k < x_axis; k++){
		
			picture[i][k].resize(3);
		}
	}
}

void Image::take_picture(){

	fstream file(file_name, ios::in | ios::out);

	int range;	
	string temp;

	file >> temp;

	
	file >> y_picture;
	file >> x_picture;
	
	file >> range;

	allocate_vector(y_picture,x_picture);

	for (int i=0; i < y_picture; i++){
		for(int k=0; k < x_picture; k++){
			for(int l=0; l < 3; l++){
				file >> picture[i][k][l];
			}
		}
	}

	file.close();
}

void Image::print(){

	for(int i=0; i < y_picture; i++){
		for (int k=0; k < x_picture; k++){
			for(int l=0; l < 3; l++){
				cout << picture[i][k][l] << " ";
			}

		}
		cout << endl;
	}
}

int Image::con_gray(){

	float c_r, c_g , c_b;
	bool control = true;

	do {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		// cout << "Enter three numbers between 0 and 1, separated by spaces: ";
		if (cin >> c_r >> c_g >> c_b) {
			if (c_r >= 0 && c_r < 1 && c_g >= 0 && c_g < 1 && c_b >= 0 && c_b < 1) {
				control = true;
			} else {
				// cout << "Invalid input. Numbers must be between 0 and 1." << endl;
				control = false;
			}
		} else {
			// cout << "Invalid input. Please enter three numbers separated by spaces." << endl;
			control = false;
		}
	} while (control == false);




	int output;

	for (int i=0; i < y_picture; i++){
		for (int k=0; k < x_picture; k++){
			output = ((c_r * picture[i][k][0]) + (c_g * picture[i][k][1]) + (c_b * picture[i][k][2]));
			for(int l=0; l < 3; l++){
				picture[i][k][l] = output;
				if (picture[i][k][l] > 255){
					picture[i][k][l] = 255;
				}
			}
		}
	}


	return 0;
}

void Image::fprint(string name)const{

	fstream file(name, ios::in | ios::out | ios::trunc);

	file << "P3" << endl;
	file << y_picture << " " << x_picture << endl;
	file << "255" << endl;

	for(int i=0; i < y_picture; i++){
		for (int k=0; k < x_picture; k++){
			for(int l=0; l < 3; l++){
				file << setw(3) << picture[i][k][l] << " ";
			}
		}
		file << endl;
	}
	file.close();

}