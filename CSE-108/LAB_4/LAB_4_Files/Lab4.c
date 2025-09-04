#include<stdio.h>

typedef struct Products{
	harddisk,
	monitor,
	keyboard,
	mouse
}Products;


typedef enum Days{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
}Days;

int Main_menu(){

	int selection;

	printf("Welcome to the TechMarket.\n");
	printf("1. Buy Product\n");
	printf("2. Orders Prices\n");
	printf("3. All Orders Prices\n");
	printf("4. Exit\n");

	printf("---------------------------------\n");
	scanf("%d", &selection);

	return selection;
}

void Buy_Product(){

	int selection;

	printf("0. Harddisk\n");
	printf("1. Monitor\n");
	printf("2. Keyboard\n");
	printf("3. Mouse\n");
	printf("4. GO TO MAIN MENU\n");

	printf("---------------------------------\n");
	scanf("%d", &selection);

	return selection;
}


int main()
{
	int selection;



	do{

		selection = Main_menu();


		if(selection == 1){
			selection = Buy_Product();

			if
		}

	}while(selection != 4)

	return 0;
}