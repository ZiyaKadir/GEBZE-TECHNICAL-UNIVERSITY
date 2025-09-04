#include<stdio.h>

void x_star_display(){
	int n;
	printf("Enter an odd integer as the height:");
	scanf("%d", &n);

	if(n % 2 == 0){
		printf("Please enter an odd integer!\n");
		return;
	}

	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(i == j || i + j == n - 1){
				printf("*");
			}else{
				printf(" ");
			}
		}
		printf("\n");
	}
}

void diamond_star_display(){
	int n;
	printf("Enter an odd integer as the height:");
	scanf("%d", &n);

	if(n % 2 == 0){
		printf("Please enter an odd integer!\n");
		return;
	}

	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(i + j == n / 2 || i - j == n / 2 || j - i == n / 2 || i + j == n + (n / 2) -1){
				printf("*");
			}else{
				printf(" ");
			}
		}
		printf("\n");
	}
}

void multiplication_table_display(){
	int n;
	printf("Enter an integer as the size: ");
	scanf("%d", &n);

	int i, j;
	for (int i=0; i<=n; i++){
		if (i==0){
			printf("\t");
		}
		else{
			printf("%d\t", i);
		}
	}
	printf("\n");
	for(int i=0; i<=n; i++){
		printf("-------");
	}
	printf("\n");
	for(i = 1; i <= n; i++){
		printf("%d*\t", i);
		for(j = 1; j <= n; j++){
			printf("%d\t", i * j);
		}
		printf("\n");
	}

}

void palindrome_check_number(){
	int n;
	printf("Enter an integer as the palindrome: ");
	scanf("%d", &n);

	int temp = n;
	int reverse = 0;

	while(temp != 0){
		reverse = reverse * 10 + temp % 10;
		temp = temp / 10;
	}

	if(reverse == n){
		printf("%d is a palindrome\n", n);
	}
	else{
		printf("%d is not a palindrome\n", n);
	}

}


int main(){

	int option;

	do{
		printf("===============================================\n");
		printf("Enter option 1 to x_star_display \n");
		printf("Enter option 2 to diamond_star_display \n");
		printf("Enter option 3 to multiplication_table_display \n");
		printf("Enter option 4 to palindrome check number \n");
		printf("Enter option -1 to exit! \n");

		

		scanf("%d", &option);

		if(option == 1){
			x_star_display();
		}else if(option == 2){
			diamond_star_display();
		}else if(option == 3){
			multiplication_table_display();
		}else if(option == 4){
			palindrome_check_number();
		}
		else if(option == -1){
			printf("Exiting the program!\n");
		}
		else{
			printf("Invalid option!\n");
			printf("Please enter a valid option!\n");
		}

	}while(option != -1);


	return 0;
}