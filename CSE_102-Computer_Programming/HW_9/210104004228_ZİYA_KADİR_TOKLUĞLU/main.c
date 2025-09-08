#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


union Person
{
    char name[50];
    char address[50];
    int phone;
};

union Loan
{
  float arr[3];
};

struct BankAccount
{
    union Person Customer;
    union Loan Loans[3];
};


void listCustomer(struct BankAccount *BankAccount, int num_customer){


    for(int i=0; i<num_customer; i++){
            printf("%d.Customer Name = %s\n",i+1,BankAccount[i].Customer.name); // printing list
      }
}

/* check the file and previous users name assign to struct */
struct BankAccount *checking_file_customer(struct BankAccount *BankAccount,int *num){

    FILE *ptr;
    *num=0;
    char temp[50];
    char control1[50]="Customer ID = ";
    char control2[50]="Customer Name = ";
    ptr = fopen("customer.txt","r+");
      while(!feof(ptr)){

        fscanf(ptr," %[^\n]%*c ",temp);
       
        if(strncmp(temp,control1,14)==0){
            (*num)++;
          
        }
        else if(strncmp(temp,control2,16)==0){
          strcpy(BankAccount[(*num)-1].Customer.name,(temp+16));
        }

      }
    fclose(ptr);

  return BankAccount;
}
/* loan calculation with recursion*/
float calculateLoan(float amount, int period, float interestRate){

    if(period==0) {
      printf("%f\n",amount);
      return amount;
    }
    else {
      amount=amount*(1+interestRate);
      return calculateLoan(amount,period-1,interestRate);
    }
}

struct BankAccount *addCustomer(struct BankAccount *BankAccount,int num){

  printf("Please enter the necessary information\n");
  char temp[50];
  FILE *ptr;
  ptr=fopen("customer.txt", "a+");
  fprintf(ptr,"Customer ID = %d\n",num);
  printf("Customer Name =");
  fflush(stdin);
  scanf(" %[^\n]%*c",BankAccount[num-1].Customer.name);
  strcpy(temp,BankAccount[num-1].Customer.name);
  fprintf(ptr,"Customer Name = %s\n",BankAccount[num-1].Customer.name);

  printf("Customer Phone =");
  scanf("%d",&BankAccount[num-1].Customer.phone);
  fprintf(ptr,"Customer Phone = %d\n",BankAccount[num-1].Customer.phone);

  printf("Customer Address =");
  fflush(stdin);
  scanf(" %[^\n]%*c",BankAccount[num-1].Customer.address);
  fprintf(ptr,"Customer Address = %s\n",BankAccount[num-1].Customer.address);

  printf("Informations have been saved succesfully\n");
  printf("Your id number is %d\n",num);
  strcpy(BankAccount[num-1].Customer.name,temp);

  fclose(ptr);

return BankAccount;

}

struct BankAccount *newLoan(struct BankAccount *BankAccount,int id_num){

  int loan_num,max=0;
  float *loan_amount;
  float loan_total=0;
  float amount_total;
  FILE *ptr;
  printf("Please enter how many loans you want to have:(MAX 3 LOAN)\n");
  do {
    scanf("%d",&loan_num);
    loan_amount=(float*)malloc(loan_num*sizeof(float));
    if(!(loan_num<4 && loan_num>0)) printf("Please enter the valid number of loans\n");
  } while(!(loan_num<4 && loan_num>0));

  /*calculate loan and ID,Loan and period saved int the loans.txt*/
    ptr=fopen("Loan.txt","a+");
    fprintf(ptr,"Customer ID = %d\n{",id_num);
  for(int i=0; i<loan_num; i++){

    printf("Please enter the amount for %d. loan",i+1);
    scanf("%f",&BankAccount[id_num-1].Loans[i].arr[0]);
    printf("Please enter the period for %d. loan",i+1);
    scanf("%f",&BankAccount[id_num-1].Loans[i].arr[1]);
    printf("Please enter the interestRate for %d. loan",i+1);
    scanf("%f",&BankAccount[id_num-1].Loans[i].arr[2]);

    loan_amount[i]=calculateLoan(BankAccount[id_num-1].Loans[i].arr[0],(int)BankAccount[id_num-1].Loans[i].arr[1],BankAccount[id_num-1].Loans[i].arr[2]); // taking variables from array and calculating loan
    if(i==loan_num-1) fprintf(ptr,"%.2f}",loan_amount[i]);
    else fprintf(ptr,"%.2f + ",loan_amount[i]);


    loan_total+=loan_amount[i];
  }
    fprintf(ptr," => %.2f\n",loan_total);

    fprintf(ptr,"%d ",loan_num);
    for(int i=0; i<loan_num; i++){

        fprintf(ptr,"%.2f ",loan_amount[i]);

    }
    fprintf(ptr,"%.2f\n",loan_total);
    for(int i=0; i<loan_num; i++)
    fprintf(ptr,"%.0f ",BankAccount[id_num-1].Loans[i].arr[1]);
    fprintf(ptr,"\n");
   

    fclose(ptr);

  return BankAccount;
}


void getReport(struct BankAccount *BankAccount, int selection){


  int cus_num; /* custumer number */
  int loan; /* the loan which users want to see this */
  int num_loan; /* the loan number of the users */
  float amount[4];
  int period[3];
  int first,last;
  printf("Please enter the customer ID:");
  scanf("%d",&cus_num);


  char temp1[50];
  char temp2[50];

  char control1[50]="Customer ID ";

  int id;
  FILE *ptr,*file;

  ptr=fopen("customer.txt","r+");
  file=fopen("Loan.txt","r+");


    /*controlling ID and matching the ID with customer.txt and loan.txt*/
    /*printing custumer information and loan information generally*/
    if(selection ==1)
    {

      while(!feof(ptr)){

      fscanf(ptr,"%[^\n]%*c",temp1);
      sscanf(temp1,"%[^=]%*c %d",temp2, &id);

    
      if(id==cus_num && strncmp(temp2,control1,12)==0){


        for(int i=0; i<4; i++){

          printf("%s\n",temp1);
          fscanf(ptr,"%[^\n]%*c",temp1);
        }
        rewind(file);
        while(!feof(file)){
        fscanf(file,"%[^\n]%*c",temp1);
        sscanf(temp1,"%[^=]%*c %d",temp2, &id);

        if(id==cus_num && strncmp(temp2,control1,12)==0){

          fscanf(file,"%[^\n]%*c",temp1);
          printf("%s\n", temp1);
          break;

        }
      }

        break;
      }
    }
    }

    /*controlling ID and matching the ID with customer.txt and loan.txt*/
    /*printing users loan which users want it */
    else if(selection ==2){

      printf("Please enter the which loan you want to look:");
      scanf("%d",&loan);

      while(!feof(file)){

      fscanf(file,"%[^\n]%*c",temp1);
      sscanf(temp1,"%[^=]%*c %d",temp2, &id);


      if(id==cus_num && strncmp(temp2,control1,12)==0){

        fscanf(file,"%[^\n]%*c",temp1);
        fscanf(file,"%d",&num_loan);

        for (int i=0; i<num_loan+1; i++){
        fscanf(file,"%f",&amount[i]);
        printf("%f\n",amount[i]);
        }
        for(int i=0; i<num_loan;i++){
        fscanf(file,"%d",&period[i]);
        printf("%d\n",period[i]);
        }


        if(num_loan<loan) printf("Please enter the valid loans");
        else{


          printf("Total amount =%f\n",amount[loan-1]);

          for (int i=0; i<period[loan-1]; i++){

              printf("%d. Month installement= %f\n",i+1,amount[loan-1]/period[loan-1]);
          }
        }
        break;
      }
    }
}
  fclose(file);
  fclose(ptr);

}

int main(){

int operation;
int cus_id; /*customer id*/
int num_customer=0;
int choose;

FILE *file1, *file2;

file1 = fopen("Loan.txt", "w");
file2 = fopen("customer.txt", "w");
fclose(file1);
fclose(file2);

struct BankAccount BankAccount[50];

checking_file_customer(BankAccount,&num_customer); /* checking if the program save information in previous time */

do {

  printf("=====================================\n");
  printf("Welcome to the Bank Management System\n");
  printf("=====================================\n");


  printf("\t1. List All Customers\n");
  printf("\t2. Add New Customers\n");
  printf("\t3. New Loan Application\n");
  printf("\t4. Report Menu\n");
  printf("\t5. Exit System \n");

  scanf("%d",&operation);

  if(operation==1){

    listCustomer(BankAccount,num_customer);

  }
  else if(operation==2){

      num_customer++;
      /* if you want to add more than 50 users getting error*/
    if(num_customer<50) addCustomer(BankAccount,num_customer);
    else printf("the user can not created because bank customer limit is full\n");
  }
  else if(operation==3){
    printf("Please enter id number the which customer have to create new loan\n");

    do {
      scanf("%d",&cus_id);
      if(cus_id<=num_customer) newLoan(BankAccount,cus_id);
      else printf("Please enter the valid ID number\n");
    } while(cus_id>num_customer);


  }
  else if(operation==4){

    int selection=0;

    do {
      printf("1. Customer information\n");
      printf("2. Loan information\n");

      scanf("%d",&selection);
      if (selection>2 || selection<1) printf("Please enter the valid number\n");

    } while(selection>2 || selection<1);

    getReport(BankAccount,selection);
  }
  else if(!(operation<6 && operation>0))
   printf("Please select appropriate operation on the menu\n");

} while(operation != 5);


  return 0;
}
