#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define MAX_LEN 50


void reverse_helper(char str[], char reversed[], int i, int length){
    if (i >= length){
        reversed[length] = '\0'; 
        return;
    }
    
    reversed[length - 1 - i] = str[i]; 
    
    reverse_helper(str, reversed, i + 1, length);
}

void reverse(char str[], char reversed[], int i){
    int length = strlen(str);
    reverse_helper(str, reversed, 0, length);
}


// Merge two subarrays L and M into arr
void merge(int arr[], int p, int q, int r){

	//Create L <- A[p..q] and M <- A[q+1..r]
	int n1 = q - p + 1 ;
	int n2 = r - q;

	int L[n1], M[n2];

	for(int i = 0; i < n1; i++)
		L[i] = arr[p + i];
	for(int j = 0; j < n2; j++)
		M[j] = arr[q + 1 + j];

	// Maintain current index of sub-arrays and main array
	int i, j, k;
	i = 0;
	j = 0;
	k = p; // the correct form
	
	// Until we reach either end of either L or M, pick larger among
	// elements L and M and place them in the correct position at A[p..r]

	while(i < n1 && j < n2) {
		if(L[i] <= M[j]){
			arr[k] = L[i];
			i++;
		}else{
			arr[k] = M[j];
			j++;
		}
		k++;
	}

	// When we run out of elements in either L or M,
	// pick up the remaining elements and put in A[p..r]

	while(i < n1){
		arr[k] = L[i];
		i++;
		k++;
	}

	while(j < n2){
		arr[k] = M[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int l, int r){

	if(l < r){
		int m = l + (r - l) / 2;

		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

int main(){

	// Part 1

	char original[MAX_LEN] = "Ziya Kadir";
	char reversed[MAX_LEN];

	reverse(original, reversed, 0);

	printf("original = %s\n", original);
	printf("reversed = %s\n", reversed);


	// Part 2

	int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    printf("Original array: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    
    mergeSort(arr, 0, n-1);
    
    printf("\nSorted array: ");
    
	for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
	}

	return 0;

}