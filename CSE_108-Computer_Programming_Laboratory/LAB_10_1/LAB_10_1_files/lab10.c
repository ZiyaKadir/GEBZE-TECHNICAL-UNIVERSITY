#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define PI 3.14
#define MAX_CIRCLES 10

struct coordinates {
    int x;
    int y;
};

struct circle {
    struct coordinates points[2]; 
    float radius;
    float perimeter; 
    float area;
};

/**
 * @brief Calculates distance between two points using distance formula
 * @param x1 X coordinate of first point
 * @param y1 Y coordinate of first point  
 * @param x2 X coordinate of second point
 * @param y2 Y coordinate of second point
 * @return Distance between the two points
 */
float calculate_distance(int x1, int y1, int x2, int y2){
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

/**
 * @brief Calculates radius, perimeter and area for a circle
 * @param c Pointer to circle structure
 */
void calculate_circle_properties(struct circle *c){
    c->radius = calculate_distance(c->points[0].x, c->points[0].y, 
                                  c->points[1].x, c->points[1].y);
    
    c->perimeter = 2 * PI * c->radius;
    
    c->area = PI * c->radius * c->radius;
}

/**
 * @brief Sorts array of circles by radius in ascending order (bubble sort)
 * @param circles Array of circle structures
 * @param n Number of circles
 */
void sort_circles_by_radius(struct circle circles[], int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(circles[j].radius > circles[j + 1].radius){
                struct circle temp = circles[j];
                circles[j] = circles[j + 1];
                circles[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief Recursively prints circle information in ascending order by radius
 * @param circles Array of circle structures
 * @param current_index Current index to print
 * @param total_circles Total number of circles
 */
void print_struct(struct circle circles[], int current_index, int total_circles){
    if(current_index >= total_circles){
        return;
    }
    
    printf("Circle %d\t\tRadius: %.2f\t\tPerimeter: %.2f\t\tArea: %.2f\n", 
           current_index + 1, 
           circles[current_index].radius,
           circles[current_index].perimeter, 
           circles[current_index].area);
    
    print_struct(circles, current_index + 1, total_circles);
}

/**
 * @brief Checks if a number is prime
 * @param n Number to check
 * @return 1 if prime, 0 if not prime
 */
int is_prime(int n){
    if(n <= 1){
        return 0;
    }
    
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            return 0;
        }
    }
    
    return 1;
}

/**
 * @brief Recursively finds and prints prime factorization
 * @param n Number to factorize
 * @param divisor Current divisor to try
 */
void factorization(int n, int divisor){
    if(n == 1){
        return;
    }
    
    if(n % divisor == 0 && is_prime(divisor)){
        printf("%d", divisor);
        
        if(n / divisor != 1){
            printf("*");
        }
        factorization(n / divisor, divisor);
        return;
    }
    
    factorization(n, divisor + 1);
}

int main(){
    
    printf("=== PART 1: Circle Analysis ===\n");
    
    int num_circles;
    printf("Number of circles: ");
    scanf("%d", &num_circles);
    
    struct circle circles[MAX_CIRCLES];
    
    for(int i = 0; i < num_circles; i++){
        printf("\nCircle %d...\n", i + 1);
        printf("Coordinates of center: ");
        scanf("%d %d", &circles[i].points[0].x, &circles[i].points[0].y);
        printf("Coordinates of point P: ");
        scanf("%d %d", &circles[i].points[1].x, &circles[i].points[1].y);
        
        calculate_circle_properties(&circles[i]);
    }
    
    sort_circles_by_radius(circles, num_circles);
    
    printf("\nPrinting circles in an ascending order...\n");
    print_struct(circles, 0, num_circles);
    
    printf("\n=== PART 2: Prime Factorization ===\n");
    
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    
    if(is_prime(number)){
        printf("%d is a prime number.\n", number);
    }
    else{
        printf("%d = ", number);
        factorization(number, 2);
        printf("\n");
    }
    
    return 0;
}