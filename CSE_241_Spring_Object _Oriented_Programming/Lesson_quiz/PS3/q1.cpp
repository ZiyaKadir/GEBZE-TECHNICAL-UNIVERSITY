#include <iostream>
#include <cstdlib>
#include <time.h>


using namespace std;

class HotDogStand{

	public:

		HotDogStand();
		HotDogStand(int ID);
		HotDogStand(int ID, int has_sold);


		void set_ID(int ID);

		int get_hot_dogs()const;
		int get_total_hot_dogs()const;

		void JustSold();


		static int num_total_hot_dogs;
	
	private:

		int num_hot_dogs;
		int ID_stand;	

};


int HotDogStand::num_total_hot_dogs = 0;


int main(){

// crearing tree object for HotDogstand by using different constructer;
	HotDogStand Stand1; // default ID and num_hot_dogs = 0
	HotDogStand Stand2(2); // default num_hot_dogs= 0
	HotDogStand Stand3(3,12);





	Stand1.set_ID(1);

	// increase 7 times  the hot dog number for Stand2
	cout << "Before increasing 7 times" << endl;
	cout << "Stand1's hotdog number has sold = " << Stand1.get_hot_dogs() << endl;
	for (int i=0; i < 7; i++){
		Stand1.JustSold();
	}
	cout << "After incresing" << endl;
	cout << "Stand1's hotdog number has sold = " << Stand1.get_hot_dogs() << endl << endl;



	// increase 13 times  the hot dog number for Stand3
	cout << "Before increasing 13 times" << endl;
	cout << "Stand1's hotdog number has sold = " << Stand3.get_hot_dogs() << endl;
	for (int i=0; i < 13; i++){
		Stand3.JustSold();
	}
	cout << "After incresing" << endl;
	cout << "Stand1's hotdog number has sold = " << Stand3.get_hot_dogs() << endl << endl;


	cout << "The total number hotdogs = " << Stand2.get_total_hot_dogs() << endl;




	return 0;
}


// implementation member function and constructer

HotDogStand::HotDogStand(){
	ID_stand=0;
	num_hot_dogs = 0;

}

HotDogStand::HotDogStand(int ID){
	ID_stand = ID;	
	num_hot_dogs = 0; 
}

HotDogStand::HotDogStand(int ID, int has_sold){
	ID_stand = ID;
	num_hot_dogs = has_sold;
	num_total_hot_dogs += has_sold;
}

void HotDogStand::JustSold(){
	num_hot_dogs ++;
	num_total_hot_dogs ++;
}

int HotDogStand::get_hot_dogs()const{
	return num_hot_dogs;
}
int HotDogStand::get_total_hot_dogs()const{
	return num_total_hot_dogs;
}

void HotDogStand::set_ID(int ID){
	ID_stand = ID;
}