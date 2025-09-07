#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LEN 100

/**
 * @brief Finds the maximum value in an array using recursion
 * @param distanceOfCities Array of distances
 * @param start Starting index
 * @param end Ending index
 * @return Maximum distance value
 */
int findMaximumDistance(int distanceOfCities[], int start, int end){
    
    // Base case 1: Only one element
    if(start == end){
        return distanceOfCities[start];
    }
    
    // Base case 2: Two elements
    if(start + 1 == end){
        if(distanceOfCities[start] > distanceOfCities[end]){
            return distanceOfCities[start];
        }
        else{
            return distanceOfCities[end];
        }
    }
    
    // Recursive case: divide and conquer
    int mid = start + (end - start) / 2;
    
    int leftMax = findMaximumDistance(distanceOfCities, start, mid);
    int rightMax = findMaximumDistance(distanceOfCities, mid + 1, end);
    
    if(leftMax > rightMax){
        return leftMax;
    }
    else{
        return rightMax;
    }
}

/**
 * @brief Helper function to find minimum of three values
 * @param x First value
 * @param y Second value  
 * @param z Third value
 * @return Minimum of the three values
 */
int min_three(int x, int y, int z){
    if(x <= y && x <= z){
        return x;
    }
    else if(y <= x && y <= z){
        return y;
    }
    else{
        return z;
    }
}

/**
 * @brief Calculates minimum edit distance between two strings recursively
 * @param str1 First string
 * @param str2 Second string
 * @param m Length of first string
 * @param n Length of second string
 * @return Minimum number of operations needed
 */
int recursiveMinStrDiff(char str1[], char str2[], int m, int n){
    
    // Base case 1: If str1 is empty, insert all characters of str2
    if(m == 0){
        return n;
    }
    
    // Base case 2: If str2 is empty, remove all characters from str1
    if(n == 0){
        return m;
    }
    
    // Recursive case 1: If last characters are same, ignore them
    if(str1[m-1] == str2[n-1]){
        return recursiveMinStrDiff(str1, str2, m-1, n-1);
    }
    
    // Recursive case 2: If last characters are different, try all operations
    else{
        int add_op = recursiveMinStrDiff(str1, str2, m, n-1);      // Add
        int remove_op = recursiveMinStrDiff(str1, str2, m-1, n);   // Remove  
        int replace_op = recursiveMinStrDiff(str1, str2, m-1, n-1); // Replace
        
        return 1 + min_three(add_op, remove_op, replace_op);
    }
}

int main(){
    
    // Part 1: Find Maximum Distance
    printf("=== Part 1: Maximum Distance ===\n");
    
    int distanceOfCities[] = {120, 200, 105, 300, 295};
    int size = sizeof(distanceOfCities) / sizeof(distanceOfCities[0]);
    
    printf("Distance array: ");
    for(int i = 0; i < size; i++){
        printf("%d ", distanceOfCities[i]);
    }
    printf("\n");
    
    int maxDistance = findMaximumDistance(distanceOfCities, 0, size - 1);
    printf("Maximum distance: %d\n\n", maxDistance);
    
    // Part 2: Minimum String Difference
    printf("=== Part 2: Minimum String Edit Distance ===\n");
    
    char str1[] = "tesla";
    char str2[] = "test";
    
    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);
    
    int result = recursiveMinStrDiff(str1, str2, strlen(str1), strlen(str2));
    printf("Minimum operations needed: %d\n\n", result);
    
    // Additional test cases
    printf("=== Additional Test Cases ===\n");
    
    char test1[] = "monday";
    char test2[] = "sunday";
    printf("'%s' to '%s': %d operations\n", test1, test2, 
           recursiveMinStrDiff(test1, test2, strlen(test1), strlen(test2)));
    
    char test3[] = "sunday";
    char test4[] = "saturday";
    printf("'%s' to '%s': %d operations\n", test3, test4,
           recursiveMinStrDiff(test3, test4, strlen(test3), strlen(test4)));
    
    return 0;
}