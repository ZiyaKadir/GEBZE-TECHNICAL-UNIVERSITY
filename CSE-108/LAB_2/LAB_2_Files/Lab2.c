#include <stdio.h>
#include <math.h>

double find_mean(FILE *file){
	
	fseek(file, 0, SEEK_SET);
	int total = 0;
	int number;
	int counter = 0;

	while(!feof(file)){
		fscanf(file,"%d", &number);
		total += number;
		counter ++;
	}

	return (double)(total / counter);
}

void write_file(FILE *file, int number){
	
	fprintf(file, " %d", number);
}

int GCD_calculator(int num1, int num2){ // Greatest common divider

	int GCD = 1; // assigning 1 because 1 is the all number common diviser
	int i = 2; // counter for finding gcd

	while(i <= num1 && i <= num2){

		if(num1 % i == 0 && num2 % i == 0){
			GCD = i;
		}
		i++;
	}

	printf("GCD of given numbers: %d \n", GCD);
	printf("The result is written to the results.txt file\n");

	return GCD;
}


int LCM_calculator(int num1, int num2){ // Least common multiple calculator

	int GCD = GCD_calculator(num1,num2);

	return ((num1*num2) / GCD); // General formula in the PDF
}

int SD_calculator(FILE *file)//Standart Deviation calculator
{
	int  mean = find_mean(file);
	double total = 0;
	int number;
	int counter = 0;

	fseek(file, 0, SEEK_SET);

	while (!feof(file)){
		fscanf(file, "%d", &number);
		total += pow(2, (number - mean));
		counter++;

		printf("%d.number = %d \n", counter, number);
	}

	return (sqrt(total / counter));
}

int main(){


	int num1, num2, selection , result;

	FILE * file = fopen("results.txt", "w+");
	
	do{

		printf("Enter the calculater type \n");
		printf("1. GCD Calculator \n");
		printf("2. LCM Calculator via GCD \n");
		printf("3. Standard Deviation Calculator \n");
		printf("--------------------------- \n ");

		scanf("%d", &selection);

		if(selection == 1){

			printf("Please enter the first number \n");
			scanf("%d", &num1);
			printf("Please enter the second number \n");	
			scanf("%d", &num2);

			result = GCD_calculator(num1,num2);
			write_file(file, result);
		}
		else if(selection == 2){
			printf("Please enter the first number \n");
			scanf("%d", &num1);
			printf("Please enter the second number \n");	
			scanf("%d", &num2);

			result = LCM_calculator(num1, num2);
			write_file(file, result);
		}
		else if(selection == 3){
			result = SD_calculator(file);
			printf("The Standart Deviation = %d\n", result);
		}


	}while(selection < 4 && selection > 0);

	fclose(file);


	return 0;
}