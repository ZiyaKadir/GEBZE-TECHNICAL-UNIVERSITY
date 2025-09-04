#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void print_menu(){

	printf("Choose the matrix operation : \n");
	printf("============================= \n");
	printf("1. Convolutional Filter for 1D array \n");
	printf("2. Multiplication \n");
	printf("3. Trace \n");
	printf("4. Transpose \n");
	printf("5. Exit \n");
	printf("============================= \n");
	printf("Enter your choice : ");
}

void display_1D(int *array, int size){

	for(int i = 0; i < size; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

int* get_numbers(int num){

	int *array = (int*)malloc(num * sizeof(int));
	if(array == NULL){
		printf("Memory allocation failed\n");
		exit(1);
	}

	printf("Please enter the numbers: ");
	for(int i = 0; i < num; i++){
		scanf("%d", &array[i]);
	}
	printf("You entered: ");
	display_1D(array, num);
	return array;
}

void display_2D(int **array, int rows, int cols){

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
}

int**get_numbers_2D(int rows, int cols){

	int **array = (int**)malloc(rows * sizeof(int*));
	if(array == NULL){
		printf("Memory allocation failed\n");
		exit(1);
	}

	for(int i = 0; i < rows; i++){
		array[i] = (int*)malloc(cols * sizeof(int));
		if(array[i] == NULL){
			printf("Memory allocation failed\n");
			exit(1);
		}
	}

	printf("Please enter the numbers: \n");
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			scanf("%d", &array[i][j]);
		}
	}
	printf("You entered: \n");
	display_2D(array, rows, cols);
	return array;
}










int* convolutional_filter_1D(int* array, int* conv, int array_size, int conv_size){

	int i, j;
	int* result = (int*)malloc((array_size - conv_size + 1) * sizeof(int));

	for(i = 0; i <= array_size - conv_size; i++){
		result[i] = 0;
		for(j = 0; j < conv_size; j++){
			result[i] += array[i + j] * conv[j];
		}
	}

	return result;
}


int main(){

	int choice;
	
	

	do{
		print_menu();
		scanf("%d", &choice);

		if(choice == 1){
			int num_arr; // array's number
			printf("Please enter the size of the array: ");
			scanf("%d", &num_arr);
			int* arr = get_numbers(num_arr);

			int num_conv; // convolution's number
			printf("Please enter the size of the convolution: ");
			scanf("%d", &num_conv);
			int* conv = get_numbers(num_conv);
			
			int* result = convolutional_filter_1D(arr, conv, num_arr, num_conv);
			printf("Result of convolution: ");
			display_1D(result, num_arr - num_conv + 1);
			free(arr);
			free(conv);
			free(result);	
		}
		else if(choice == 2 || choice == 3 || choice == 4){

			int rows1, cols1;
			printf("Please enter the number of rows and columns for the first matrix: ");
			scanf("%d %d", &rows1, &cols1);
			int **matrix1 = get_numbers_2D(rows1, cols1);

			int rows2, cols2;
			printf("Please enter the number of rows and columns for the second matrix: ");
			scanf("%d %d", &rows2, &cols2);
			int **matrix2 = get_numbers_2D(rows2, cols2);
		
			if (choice == 2){
				if(cols1 != rows2){
					printf("Matrix multiplication is not possible with these dimensions.\n");
					free(matrix1);
					free(matrix2);
					continue;
				}

				int **result = (int**)malloc(rows1 * sizeof(int*));
				for(int i = 0; i < rows1; i++){
					result[i] = (int*)malloc(cols2 * sizeof(int));
					for(int j = 0; j < cols2; j++){
						result[i][j] = 0;
						for(int k = 0; k < cols1; k++){
							result[i][j] += matrix1[i][k] * matrix2[k][j];
						}
					}
				}

				printf("Result of multiplication: \n");
				display_2D(result, rows1, cols2);

				for(int i = 0; i < rows1; i++){
					free(result[i]);
				}
				free(result);

			}
			else if(choice == 3){

				if(rows1 != cols1){
					printf("Trace is only defined for square matrices.\n");
					free(matrix1);
					free(matrix2);
					continue;
				}
				if(rows1 != rows2 || cols1 != cols2){
					printf("Matrices must be of the same size to calculate trace.\n");
					free(matrix1);
					free(matrix2);
					continue;
				}

				int trace = 0;
				for(int i = 0; i < rows1; i++){
					trace += matrix1[i][i];
				}
				printf("Trace of the matrix: %d\n", trace);
				int trace2 = 0;
				for(int i = 0; i < rows2; i++){
					trace2 += matrix2[i][i];
				}
				printf("Trace of the second matrix: %d\n", trace2);

				
			}
			else if(choice == 4){

				int **transpose = (int**)malloc(cols1 * sizeof(int*));
				for(int i = 0; i < cols1; i++){
					transpose[i] = (int*)malloc(rows1 * sizeof(int));
					for(int j = 0; j < rows1; j++){
						transpose[i][j] = matrix1[j][i];
					}
				}

				printf("Transpose of the first matrix: \n");
				display_2D(transpose, cols1, rows1);
				for(int i = 0; i < cols1; i++){
					free(transpose[i]);
				}
				free(transpose);

				transpose = (int**)malloc(cols2 * sizeof(int*));

				for(int i = 0; i < cols2; i++){
					transpose[i] = (int*)malloc(rows2 * sizeof(int));
					for(int j = 0; j < rows2; j++){
						transpose[i][j] = matrix2[j][i];
					}
				}

				printf("Transpose of the second matrix: \n");
				display_2D(transpose, cols2, rows2);

				for(int i = 0; i < cols2; i++){
					free(transpose[i]);
				}

				free(transpose);
			}

			for(int i = 0; i < rows1; i++){
				free(matrix1[i]);
			}
			for(int i = 0; i < rows2; i++){
				free(matrix2[i]);
			}
			free(matrix1);
			free(matrix2);
		}

	}while(choice != 5);


	return 0;
}