#include<stdio.h>
#include "utils.h"

int main()
{
   /* -------------- PART 1 -------------- */
   printf("\e[0;91m---------------PART 1---------------\e[0;37m\n");
    
  int f_int; /* first integer */ 
  int s_int; /* second integer */
  int div;   /* divisor */
  int f_div_num; /* first divisible number */
  int seq_num; /* sequence of the number */
  int seq_num_res; /* result of the sequent of the number */
  char s_script[2];/* superscript ordinals */
  printf("Enter the first integer: ");
  scanf("%d", &f_int);
  printf("Enter the second integer: ");
  scanf("%d", &s_int);
  printf("Enter the divisor: ");
  scanf("%d", &div);

  f_div_num = find_divisible(f_int, s_int, div);
  
  if(f_div_num == -1)
  {
  	printf("There is not any integer between %d and %d can be divided by %d\n", f_int, s_int, div);
  }
  else
  {
  printf("The first integer between %d and %d divided by %d is %d\n", f_int, s_int, div, f_div_num);
  printf("Enter the number how many next: ");
  scanf("%d", &seq_num);
  
  /* this if block we determine superscript ordinals*/
  if ((seq_num + 1) == 11 && (seq_num + 1) == 12 && (seq_num + 1) == 13)
  {
   s_script[0] = 't';
   s_script[1] = 'h';
   
  }
  else if ((seq_num + 1) % 10 == 1)
  {
   s_script[0] = 's';
   s_script[1] = 't';
  }
  else if ((seq_num + 1) % 10 == 2)
  {
   s_script[0] = 'n';
   s_script[1] = 'd';
  }
  else if ((seq_num + 1) % 10 == 3)
  {
   s_script[0] = 'r';
   s_script[1] = 'd';
  }
  else 
  {
   s_script[0] = 't';
   s_script[1] = 'h';
  }
  seq_num_res = find_nth_divisible(seq_num ,f_div_num, div);
  
  if (seq_num_res < s_int){
  printf("The %d%c%c integer between %d and %d divided by is %d \n"
  ,seq_num + 1,s_script[0],s_script[1], f_int, s_int, seq_num_res);
  }
  else 
  printf("there is not nth between %d and %d \n", f_int, s_int);
  }
  
  /* -------------- PART 2 --------------*/
   printf("\e[0;91m---------------PART 2---------------\e[0;37m\n");
  char identity_number[11];
  int password;
 printf("Enter your identity number(ID, 11 letter)\n");
 scanf("%s", identity_number);
 
 if (validate_identity_number(identity_number) == 0){
	printf("Invalid identity number\n");
	return 0; 
 }
 else {
 	printf("valid identity number\n");
 }
 printf("please enter your password (4 digits): ");
 scanf("%d", &password);
 if (password < 10000 && password > 999)
 {
   printf("valid password\n");
 }
 else 
 {
    printf("Invalid password\n");
    return 0; 
 }
 if (create_customer(identity_number, password) == 1){
 	printf("Successfully, created customer_account \n");
 }

/* --------------- PART 3 ---------------*/
 printf("\e[0;91m---------------PART 3---------------\e[0;37m\n");
float money = 0;

printf("Enter your identity number: ");
scanf("%s", identity_number);
printf("Enter your password: ");
scanf("%d", &password);
  if (check_login(identity_number, password) == 1)
  {
	printf("\n\n\e[0;92mLogin Successful\e[0;37m\n\n");
	printf("Enter your withdraw amount: ");
	scanf("%f", &money);
	printf("Withdrawable amount is %d\n", withdrawable_amount(money));
  }
  else{
  printf("Invalid identity number or password\n");
  }

return 0;
}
