#include <iostream>
#include <cstdlib>
#include <limits>
#include <time.h>

using namespace std;



/*
	Calculating the size of array
*/
int strlen(const char* str){

	size_t i = 0;
	while (str[i] != '\0'){
		i++;
	}
	return i;
}

/*
	convert the char array to integer number after controlling the all index include number 
*/
int atoi(const char* src){

	int number = 0;
	int num_digit;

	num_digit = strlen(src);

	for(int i=0; i < num_digit; i++){
		number *= 10;
		number += (src[i] - '0');
	}

	return number;

}

/*
	controlling the array includes only number with white space
*/

bool is_all_digit(char *src){

	size_t i = 0;
	while(src[i] != '\0'){
		if(!(src[i] >= '0' && src[i] <= '9')){
			return false;
		}
		i++;
	}
	return true;
}


/*
	compare the string for controlling flag and runnig program name
*/

int strcmp(const char* dest,const char* src){

	int dest_len = strlen(dest);
	int src_len = strlen(src);

	for (int i = 0; (i < dest_len) || (i < src_len); i++){
		if(dest[i] != src[i]){
			return dest[i] - src[i];
		}
		else continue;
	}
	return 0;
}

/*
	control the number have a digit 
*/
int  cont_num(int number, int digit , int num_digit){

	int s_digit = 0;

	for (int i=0; i < num_digit; i++){
		

		if(number % 10 == digit){
			s_digit ++;
		}
		
		number /=10;
		
	}
	return s_digit;
}

/*
	Calculating the digit number of the number
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
	comparesion of two number, control how many digit's are same with step value
	-1 for error message
*/

int num_cmp(int num1, int num2){

	int s_digit = 0; // same digit number
	int n_digit;

	if(num_digit(num1) != num_digit(num2)){
		return -1;
	}
	else{
		n_digit = num_digit(num1);
	}

	for(int i=0; i < n_digit; i++){
		
		if(num1 % 10 == num2 %10){
			s_digit ++;
		}
		num1 /= 10;
		num2 /= 10;
	}

	return s_digit;
}

/*
	count how many digits are same 
*/

int cont_digit(int num1, int num2){

	int n_digit1, n_digit2;
	int s_digit=0;
	n_digit1 = num_digit(num1);
	n_digit2 = num_digit(num2);


	for(int i=0; i < n_digit2 ; i++){



		s_digit += cont_num(num1, (num2 % 10),n_digit1); 

		// if(cont_num(num1, (num2 % 10), n_digit1) != 0){
		// 	cout << "say " << endl;
		// 	s_digit ++;
		// }

		num2 /= 10;
	}	

	return s_digit;
}

/*
	Create a number which have digit(digit)
*/

int C_number(int digit)
{
	int c_digit = 0; // when we generate the number , I hold current digit number
	int R_digit = 0; // generate random number according to N : digit number
	int R_number =0;
	R_digit = rand() % 9 + 1; // the first digit %100 not zero
	R_number = R_digit;
	c_digit++;

	for (int i=0; i < digit - 1; i++){
		R_digit = rand() % 10;

		if (cont_num(R_number , R_digit, c_digit) != 0){
			i --;
			continue;
		}
		else{
			//cout << R_number << endl;
			R_number *= 10;
			R_number += R_digit;
			c_digit ++;
		}
	}
	return R_number;
}


int main(int argc, char** argv){

	int number; // number we want to find
	int n_digit;
	int g_number; // guess number
	int num_games = 0;

	srand(time(0));


	/*
	this part control the parameter are true and 
	ensures that the required number is ready for the game
	*/

	if (strcmp(argv[0],"./mastermind")== 0 || strcmp(argv[0], "mastermind.exe") == 0){
		//cout << "The program name is true" << endl;
	}
	else{
		//The program name is wrong
		cout << "E0" << endl;
		return 0;
	}

	if(argc <= 2){
		// less arguments are entered
		cout << "E0" << endl;
		return 0;
	}
	else if (argc > 3){
		// Too Many arguments are entered
			cout << "E0" << endl;
		return 0;	
	}
	else if (argc == 3){

		if (strcmp(argv[1], "-r") == 0){

			if (is_all_digit(argv[2]) == true){
				//cout << "the number entered correctly" << endl;
				n_digit = atoi(argv[2]);

				if((n_digit > 0 && n_digit < 10) && (strlen(argv[2]) == 1)){
					
					number = C_number(n_digit);
				}
				else{
					// Entered wrong digit number of the number
					cout << "E0" << endl;
					return 0;
				}

			}
			else{
				// Please enter valid number
				cout << "E0" << endl;
				return 0;
			}

		}
		else if(strcmp(argv[1], "-u") == 0){

			if (is_all_digit(argv[2]) == true && strlen(argv[2]) < 10){

				number = atoi(argv[2]);
				n_digit = num_digit(number);

				if ((n_digit > 0 && n_digit < 10) && number != 0){
					
					if(cont_digit(number,number) == n_digit){
						//cout << "The number are entered correctly as a parameter" << endl;
					}
					else{
						// the number has includes same digits in itself
						cout << "E0" << endl;
						return 0;
					}
				}
				else{
					// Entered  wrong number
					cout << "E0" << endl; 	
					return 0;
				}

			}
			else{
				// Please enter valid number
				cout << "E0" << endl;
				return 0;
			}
		}
		else{
			// The argument's flag is wrong
			cout << "E0" << endl;
			return 0;
		}

	}
	int control;
	char c;

	for(int i=1; i <= 100; i++){

		
		cin >> g_number;

		if (!cin.good() || cin.fail() == true){
			// Please enter the right value
			cout << "E2" << endl;
			break;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.clear();


		control = num_cmp(g_number,number);

		if(control == -1){
			
			// Please enter same digit number
			cout << "E1" << endl;
			break;
		}
		else if(control == n_digit){
			cout << "FOUND " << i << endl;
			return 0;
		}
		else if(i==100){
			cout << "FAILED" << endl;
			return 0;
		}
		else{
			cout << control << " " << cont_digit(number,g_number) - control << endl;

		}



	}

	return 0;
}

