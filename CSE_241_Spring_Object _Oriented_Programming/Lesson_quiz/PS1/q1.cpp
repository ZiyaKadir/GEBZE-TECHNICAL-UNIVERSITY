#include <iostream>

using namespace std;

int main(){

// QUESTION 1

	bool check = true;

//this loop for control each number in range
	for (int i=3; i <= 100; i++){
		check = true;
//to control number which is prime or not
		for(int k=2; k < i; k++){
			if(i%k == 0){
				check = false;
			}
		}
// if prime print the console and continue
		if(check == true){
			cout << i << " ";
		}
	}
	cout << endl;

}