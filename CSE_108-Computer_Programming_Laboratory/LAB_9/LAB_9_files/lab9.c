#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LEN 100

int* findMaximumDistance(int distanceOfCities[], int start, int end){
    
    static int result[2];
    
    if(start == end){
        result[0] = distanceOfCities[start];
        result[1] = distanceOfCities[start]; 
        return result;
    }
    
    if(start + 1 == end){
        result[0] = distanceOfCities[start];
        result[1] = distanceOfCities[end];
        return result;
    }
    
    int mid = start + (end - start) / 2;
    
    int* left_result = findMaximumDistance(distanceOfCities, start, mid);
    int* right_result = findMaximumDistance(distanceOfCities, mid + 1, end);
    
    int left_distance = abs(left_result[0] - left_result[1]);
    int right_distance = abs(right_result[0] - right_result[1]);
    
    int cross_dist1 = abs(left_result[0] - right_result[0]);
    int cross_dist2 = abs(left_result[0] - right_result[1]);
    int cross_dist3 = abs(left_result[1] - right_result[0]);
    int cross_dist4 = abs(left_result[1] - right_result[1]);
    
    int max_distance = left_distance;
    result[0] = left_result[0];
    result[1] = left_result[1];
    
    if(right_distance > max_distance){
        max_distance = right_distance;
        result[0] = right_result[0];
        result[1] = right_result[1];
    }
    
    if(cross_dist1 > max_distance){
        max_distance = cross_dist1;
        result[0] = left_result[0];
        result[1] = right_result[0];
    }
    
    if(cross_dist2 > max_distance){
        max_distance = cross_dist2;
        result[0] = left_result[0];
        result[1] = right_result[1];
    }
    
    if(cross_dist3 > max_distance){
        max_distance = cross_dist3;
        result[0] = left_result[1];
        result[1] = right_result[0];
    }
    
    if(cross_dist4 > max_distance){
        max_distance = cross_dist4;
        result[0] = left_result[1];
        result[1] = right_result[1];
    }
    
    return result;
}

int min_of_three(int a, int b, int c){
    if(a <= b && a <= c){
        return a;
    }
    else if(b <= a && b <= c){
        return b; 
    }
    else{
        return c;
    }
}

int recursiveMinStrDiff(char str1[], char str2[], int m, int n){
    
    if(m == 0){
        return n;
    }
    
    if(n == 0){
        return m;
    }
    
    if(str1[m-1] == str2[n-1]){
        return recursiveMinStrDiff(str1, str2, m-1, n-1);
    }
    
    else{
        int add_cost = recursiveMinStrDiff(str1, str2, m, n-1);
        int remove_cost = recursiveMinStrDiff(str1, str2, m-1, n);
        int replace_cost = recursiveMinStrDiff(str1, str2, m-1, n-1);
        
        return 1 + min_of_three(add_cost, remove_cost, replace_cost);
    }
}

int main(){
    
    printf("Part 1: Find Maximum Distance\n");
    
    int distanceOfCities[] = {120, 200, 105, 300, 295};
    int size = sizeof(distanceOfCities) / sizeof(distanceOfCities[0]);
    
    printf("Array: ");
    for(int i = 0; i < size; i++){
        printf("%d ", distanceOfCities[i]);
    }
    printf("\n");
    
    int* max_pair = findMaximumDistance(distanceOfCities, 0, size - 1);
    printf("Maximum distance pair: {%d, %d}\n", max_pair[0], max_pair[1]);
    printf("Distance: %d\n\n", abs(max_pair[0] - max_pair[1]));
    
    printf("Part 2: String Edit Distance\n");
    
    char str1[] = "tesla";
    char str2[] = "test";
    
    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);
    
    int operations = recursiveMinStrDiff(str1, str2, strlen(str1), strlen(str2));
    printf("Minimum operations: %d\n\n", operations);
    
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