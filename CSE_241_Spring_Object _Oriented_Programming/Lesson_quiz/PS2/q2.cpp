#include <iostream>
#include<cstdlib>
#include<time.h>

using namespace std;


int main(){

		char control;
		bool statement;
		int num_try;

		char number1[20];
		char number2[20];
		char sum[40];

	cout << "Please enter the first number max(20 digit)" << endl;


// getiing number1 with controlling
	
		int num_digit1 = 0;
	do{
		statement = true;
		num_try = 0;
	do{
		control = getchar();
		if(control == '0' && num_digit1 == 0){
			continue;
		}
		if(control == '\n' || control == '\0'){
			break;
		}
		else if(!(control >= 48 && control <= 57)){
			statement = false;
			cout << "Please enter the number dont enter any other character" << endl;
			break;
		}
		else{
			number1[num_digit1] = control;
			num_digit1 ++;
		}
	}while(control >= 48 && control <=57 && num_digit1 < 20);

	if (statement == true){
		break;
	}

	}while(statement == false);



// getting number 2 with controlling
		int num_digit2 = 0;
	do{
		statement = true;
		num_try = 0;
	do{
		control = getchar();
		if(control == '0' && num_digit2 == 0){
			continue;
		}
		if(control == '\n' || control == '\0'){
			break;
		}
		else if(!(control >= 48 && control <= 57)){
			statement = false;
			cout << "Please enter the number dont enter any other character" << endl;
			break;
		}
		else{
			number2[num_digit2] = control;
			num_digit2 ++;
		}
	}while(control >= 48 && control <=57 && num_digit2 < 20);

	if (statement == true){
		break;
	}

	}while(statement == false);


	cout << num_digit1 << endl;
	cout << num_digit2 << endl;
	
	int digit1;
	int digit2;

	for(int i=0; i < num_digit1 || num_digit2; i++){
		
		if (i < num_digit1){ 
			digit1 = number1[num_digit1-1-i] - 48;
			}
		else {
			num_digit1 = 0;
			}
		if (i < num_digit2)
		{
			digit2 = number2[num_digit2-1-i] - 48;
		}
		else {
			num_digit2 = 0;
		}
		
		if(num_digit1 > num_digit2)
			if (digit1 + digit2 >= 10){
				sum[num_digit1 -1 -i] = (digit1 + digit2) % 10;
				sum[num_digit1 -1 -i -1] = (digit1 + digit2) / 10;
			}
			else{
				sum[num_digit1 -1 -i] = (digit1 + digit2) % 10;

			}
		else{
			if (digit1 + digit2 >= 10){
				sum[num_digit2 -1 -i] = (digit1 + digit2) % 10;
				sum[num_digit2 -1 -i -1] = (digit1 + digit2) / 10;
			}
			else{
				sum[num_digit2 -1 -i] = (digit1 + digit2) % 10;
			}
		}
	}

	cout << sum << endl;


	
}