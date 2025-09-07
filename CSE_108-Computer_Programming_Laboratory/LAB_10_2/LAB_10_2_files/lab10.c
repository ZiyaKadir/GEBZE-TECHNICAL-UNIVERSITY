#include<stdio.h>
#include<stdlib.h>

#define MAX_LEN 100

struct number {
    char string[MAX_LEN];
    int integer;
};

struct combination {
    struct number n;
    struct number r;
    int result;
};

/**
 * @brief Recursively calculates the length of a string
 * @param str String to measure
 * @return Length of the string
 */
int str_len(char *str){
    if(*str == '\0'){
        return 0;
    }
    return 1 + str_len(str + 1);
}

/**
 * @brief Recursively checks if string contains only digits
 * @param number_as_str String to check
 * @param length_of_str Length of the string
 * @return 1 if valid number, 0 otherwise
 */
int is_number(char *number_as_str, int length_of_str){
    if(length_of_str == 0){
        return 1;
    }
    
    if(*number_as_str < '0' || *number_as_str > '9'){
        return 0;
    }
    
    return is_number(number_as_str + 1, length_of_str - 1);
}

/**
 * @brief Recursively converts string to integer
 * @param number_as_str String representation of number
 * @param length_of_str Length of the string
 * @return Integer value of the string
 */
int parse_to_int(char *number_as_str, int length_of_str){
    if(length_of_str == 0){
        return 0;
    }
    
    if(length_of_str == 1){
        return *number_as_str - '0';
    }
    
    int first_digit = *number_as_str - '0';
    int power_of_ten = 1;
    
    for(int i = 1; i < length_of_str; i++){
        power_of_ten *= 10;
    }
    
    return first_digit * power_of_ten + parse_to_int(number_as_str + 1, length_of_str - 1);
}

/**
 * @brief Recursively calculates factorial of a number
 * @param n Number to calculate factorial for
 * @return n! (factorial of n)
 */
int factorial(int n){
    if(n <= 1){
        return 1;
    }
    return n * factorial(n - 1);
}

/**
 * @brief Calculates combination C(n,k) = n! / (k! * (n-k)!)
 * @param n Total number of items
 * @param k Number of items to choose
 * @return Combination result
 */
int calculate_combination(int n, int k){
    if(k > n || k < 0){
        return 0;
    }
    
    return factorial(n) / (factorial(k) * factorial(n - k));
}

/**
 * @brief Recursively converts decimal number to given base
 * @param decimal_number Number to convert
 * @param base Target base (2-16)
 */
void base_converter(int decimal_number, int base){
    if(decimal_number == 0){
        return;
    }
    base_converter(decimal_number / base, base);
    
    int remainder = decimal_number % base;
    if(remainder < 10){
        printf("%d", remainder);
    }
    else{
        printf("%c", 'A' + remainder - 10);  // For bases > 10
    }
}

int main(){
    
    printf("=== PART 1: Combination Calculator ===\n");
    
    struct combination comb;
    
    while(1){
        printf("n: ");
        scanf("%s", comb.n.string);
        printf("r: ");
        scanf("%s", comb.r.string);
        
        int n_length = str_len(comb.n.string);
        int r_length = str_len(comb.r.string);
        
        if(!is_number(comb.n.string, n_length) || !is_number(comb.r.string, r_length)){
            printf("Inputs are not valid. Please try again..\n");
            continue;
        }
        
        comb.n.integer = parse_to_int(comb.n.string, n_length);
        comb.r.integer = parse_to_int(comb.r.string, r_length);
        
        if(comb.n.integer < 0 || comb.r.integer < 0 || comb.r.integer > comb.n.integer){
            printf("Inputs are not valid. Please try again..\n");
            continue;
        }
        
        comb.result = calculate_combination(comb.n.integer, comb.r.integer);
        
        printf("Combination (%d,%d) = %d.000000\n", comb.n.integer, comb.r.integer, comb.result);
        break;
    }
    
    // PART 2: Base Converter
    printf("\n=== PART 2: Base Converter ===\n");
    
    int decimal_number, base;
    
    printf("Decimal number: ");
    scanf("%d", &decimal_number);
    printf("Base: ");
    scanf("%d", &base);
    
    printf("%d in base %d is: ", decimal_number, base);
    
    if(decimal_number == 0){
        printf("0");
    }
    else{
        base_converter(decimal_number, base);
    }
    printf("\n");
    
    return 0;
}