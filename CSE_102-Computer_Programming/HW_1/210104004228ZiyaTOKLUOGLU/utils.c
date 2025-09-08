#include<stdio.h>
#include"utils.h"

int find_divisible(int x,int y,int z)
{
   int f_div_num = 4;
   int check = 1;
   
   while(x < y)
   {
   	if(x % z == 0)
   	{
   	  f_div_num = x;
   	  check = -1;
   	  break;
   	}
   x++;
   }
   if (check == 1) return (-1);
   
   
  return (f_div_num);
}

int find_nth_divisible(int n,int f_i, int z)
{
  int result = f_i + n*z; /* determine how much number next according to n (nth) number */
  
  return (result);
}

int validate_identity_number(char identity_number[])
{
  int counter = 0; /* for using in while and for integer, generally for checking elements of arrays */
  int mistake_counter = 0; /* to count mistake on identity number step by step */ 
  int length = 0; /* to control size of identity number */
  int sum_of_odd = 0; /* in identity number,sum of single digit numbers */
  int sum_of_even = 0;/* in identity number, sum of double digit numbers */
  int sum_of_ten = 0; /* in identity number, sum of first ten digit numbers */
  int check = 0; /* to use some calculation,which is used for checking */
  
  /* ---------- FIRST AND SECOND STEPS FOR CHECKİNG -------------*/
  while(counter < 11)
  {
  	if (identity_number[counter] >= '0' && identity_number[counter] <= '9')
  	{
  		length++;
  	}
  counter++;
  }
  if (length != 11)
  {
     mistake_counter++;
  }
  
  /* -----------FINISH FIRST AND SECOND STEPS FOR CHECKİNG ----------*/
  
  /* ---------- THIRD STEP FOR CHECKİNG -------------*/
  
  if (identity_number[0] == '0')
  {
	mistake_counter++;  
  }
  /* ---------- FINISH THIRD STEP FOR CHECKİNG -------------*/
  /* ---------- FOURTH STEP FOR CHECKİNG -------------*/
  counter = 0;
  while(counter < 9)
  {
  	if ( counter % 2 == 0)
  	{
  	  sum_of_odd += (identity_number[counter] - 48);
  	}
  	else
  	{
  	  sum_of_even += (identity_number[counter] - 48);
  	}
  counter++;
  }
  
  check = ((sum_of_odd * 7)- sum_of_even) % 10;
  
  if (check != (identity_number[9] -48))
  {
      mistake_counter++;
  }
  /* ---------- FINISH FOURTH STEP FOR CHECKİNG -------------*/
  
  /* ---------- FIFTH STEP FOR CHECKİNG -------------*/
  counter = 0;
  while(counter < 10)
  {
  	sum_of_ten += (identity_number[counter] -48);
  	counter++;
  }
  if ((sum_of_ten % 10) != (identity_number[10] -48))
  {
  	mistake_counter++;
  }
  /*---------- FINISH FIFTH STEP FOR CHECKİNG -------------*/
  if (mistake_counter == 0) /* to find the mistakes if it is exist */
  {
      return 1;  
  }
  else
  {
  return 0;
  }
}

int create_customer(char identity_number[], int password)
{
   FILE *customer;
   
   customer = fopen("customeraccount.txt","w");
   
   fprintf(customer,"%s,%d", identity_number, password);
   
   fclose(customer);
   
   return 1;
}

int check_login(char identity_number [], int password)
{
	FILE *c_customer;
	int counter = 0;
	int c_password; /* the password for checking */
	char c_id[11]; /* the id for checking */
	c_customer = fopen("customeraccount.txt", "r");
	
	fscanf(c_customer,"%[^,]%*c %d", c_id, &c_password); /* read string and integer seperately with using delimineter */
	fclose(c_customer);
	while(counter < 11) /* checking all char character */
	{
		if(identity_number[counter] != c_id[counter])
		{
		 return 0;
		}
	 counter++;
	}
	if (password != c_password)
	{
	  return 0;
	}
return 1;
}

int withdrawable_amount(float cash_amount){

	int wd_amount = (int) (cash_amount - ((int)cash_amount % 10)); /* to calculate withdrawable amount */
return (wd_amount);
}
