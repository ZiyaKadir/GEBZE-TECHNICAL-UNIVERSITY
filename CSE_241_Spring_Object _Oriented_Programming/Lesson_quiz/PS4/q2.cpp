#include <iostream>


using namespace std;

/*
Calculating the digit of the number
*/
int num_digit(int number){

	int digit = 1;

	 while ((number/10) !=0){	
		digit++;
		number /= 10;
	}
	
	return digit;
}

/* 
calculatinf power of the number with recursive
*/

int pow(int base, int power){
	
	if(power == 0){
		return 1;
	}
	else if(power < 0){
		return -1; // error code
	}
	else{
		return base * pow(base, power - 1);
	}
}

class MyInteger{

	public:

	MyInteger();
	MyInteger(int temp);


	int operator[](int index) const;

	private:

	int number;
	int n_digit;

};

int main(){

	MyInteger num(82314);

	cout << num[0] << " " << num[1] << " " << num[2] << endl;
	cout << num[3] << endl;
	cout << num[-1] << endl;



	return 0;
}


MyInteger::MyInteger(){
	number = 0;
}
MyInteger::MyInteger(int temp){
	number = temp;
	n_digit = num_digit(number);
}

int MyInteger::operator[](int index)const{

	int temp = number;

	if (index < 0){
		return -1;
	}
	else if(index >= n_digit){
		return -1;
	}
	else{
		
		temp /= pow(10,index);
	}

	return temp % 10;
}
