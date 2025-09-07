#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define MAX_LEN 100

int find_len(char str[]){

	int i=0;
	while(str[i] != '\0'){
		i++;
	}
	return i;
}

void show_list(const char  arr[][MAX_LEN], int size){
	for (int i=0; i < size; i++){
		printf("%d: %s \n",i,arr[i]);
	}
}


/**
 * @brief 
 * it sort the arrays according to their ascii values
 * 
 * @param arr 
 * @param n 
 */
void alphabeticSORT(char arr[][MAX_LEN], int n){

	char temp[MAX_LEN];

	for(int i=0; i < n - 1; i++){
		for(int k =i+1; k < n; k++){
			if(strcmp(arr[i], arr[k]) > 0){
				strcpy(temp, arr[i]);
				strcpy(arr[i], arr[k]);
				strcpy(arr[k], temp);
			}
		}
	}
}

/**
 * @brief 
 * accordinf to array length implement the differnet parsing functions
 * 
 * @param temp 
 * @param arr 
 */
void generateTagParser(char temp[], char arr[]){
	int size = find_len(arr);

	if(size < 5){
		strcat(temp, "<<");
		strcat(temp, arr);
		strcat(temp, ">>");
	}
	else if(size >= 5 && size < 10){
		strcat(temp, "*");
		strcat(temp, arr);
		strcat(temp, "*");
	}
	else{
		strcat(temp, "/+");
		strcat(temp, arr);
		strcat(temp, "+/");
	}
}


int main(){


	// Part 1

	int num_entries;
	printf("Enter the count of how many strings you will enter \n");
	scanf("%d", &num_entries);


	char arr_strings[num_entries][MAX_LEN];

	printf("Enter strings \n");
	for(int i = 0; i < num_entries; i++){
		scanf("%s", arr_strings[i]);
	}

	printf("Given array is \n");
	show_list(arr_strings, num_entries);

	printf("Sorted array is \n");
	alphabeticSORT(arr_strings, num_entries);
	show_list(arr_strings, num_entries);


	// Part 2

	char temp[MAX_LEN] = "";   
	char temp1[MAX_LEN] = "";  
	char temp2[MAX_LEN] = "";  

	char arr[MAX_LEN];

	printf("Enter a string: ");
	scanf("%s", arr);
	generateTagParser(temp, arr);
	printf("%s\n", temp);

	printf("Enter a string: ");
	scanf("%s", arr);
	generateTagParser(temp1, arr);
	printf("%s\n", temp1);


	printf("Enter a string: ");
	scanf("%s", arr);
	generateTagParser(temp2, arr);
	printf("%s\n", temp2);




	return 0; 
}