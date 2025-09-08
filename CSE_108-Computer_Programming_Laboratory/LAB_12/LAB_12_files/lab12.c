#include<stdio.h>
#include<stdlib.h>

/**
 * @brief Structure to hold dynamic array and its current size
 */
typedef struct {
    int *array;
    int currentsize;
} dynamic_array;

/**
 * @brief Resizes the dynamic array by increasing its size by 1
 * @param arr Pointer to the integer array
 * @param currentsize Current size of the array
 * @return Pointer to the resized array
 */
int* resize_array(int *arr, int currentsize) {
    arr = (int*)realloc(arr, (currentsize + 1) * sizeof(int));
    if(arr == NULL) {
        printf("Memory reallocation failed!\n");
        exit(1);
    }
    return arr;
}

/**
 * @brief Reads integers from a file and stores them in dynamic array
 * @param filename Name of the file to read from
 * @param arr Dynamic array structure to store the data
 * @return Updated dynamic array structure
 */
dynamic_array read_from_file(char *filename, dynamic_array arr) {
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        exit(1);
    }
    
    arr.currentsize = 0;
    arr.array = NULL;
    
    int value;
    while(fscanf(file, "%d", &value) == 1) {

		arr.array = resize_array(arr.array, arr.currentsize);
        
        arr.array[arr.currentsize] = value;
        arr.currentsize++;
    }
    
    fclose(file);
    return arr;
}

/**
 * @brief Removes the first occurrence of a number from the dynamic array
 * @param arr Dynamic array structure
 * @param number Number to be removed
 * @return Updated dynamic array structure
 */
dynamic_array removeData(dynamic_array arr, int number) {
    int found_index = -1;
    
    for(int i = 0; i < arr.currentsize; i++) {
        if(arr.array[i] == number) {
            found_index = i;
            break;
        }
    }
    
    if(found_index != -1) {

		for(int i = found_index; i < arr.currentsize - 1; i++) {
            arr.array[i] = arr.array[i + 1];
        }

		arr.currentsize--;
    }
    
    return arr;
}

/**
 * @brief Prints all elements in the dynamic array
 * @param arr Dynamic array structure to print
 */
void print_array(dynamic_array arr) {
    printf("******************\n");
    for(int i = 0; i < arr.currentsize; i++) {
        printf("%d\n", arr.array[i]);
    }
    printf("******************\n");
}

/**
 * @brief Creates a sample data file for testing
 */
void create_sample_file() {
    FILE *file = fopen("data.txt", "r");
    if(file == NULL) {
        printf("Error creating sample file\n");
        return;
    }
    
    fclose(file);
}

int main() {
    dynamic_array my_array;
    
    create_sample_file();
    
    printf("Data in source file\n");
    my_array = read_from_file("data.txt", my_array);
    
    print_array(my_array);
    
    int number_to_delete;
    printf("Enter the number you want to be deleted: ");
    scanf("%d", &number_to_delete);
    
    my_array = removeData(my_array, number_to_delete);
    
    printf("Array after deletion\n");
    print_array(my_array);
    
    free(my_array.array);
    
    return 0;
}