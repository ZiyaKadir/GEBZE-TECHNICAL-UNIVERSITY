#include<stdio.h>
#include<math.h>

int sum(int n1, int n2, int flag);
int multi(int n1, int n2, int flag);
int isprime(int a);
void write_file(int number);
void sort_file();
void print_file();
FILE *num;
FILE *sort;

int main()
{
int g_operation;
printf("Select operation\n");
printf("1. Calculate sum/multipication between two numbers\n");
printf("2. Calculate prime numbers\n");
printf("3. Show number sequence in file\n");
printf("4. Sort number sequence in file\n");
scanf("%d", &g_operation);

if (g_operation == 1){

int N1,N2,flag, operation;

printf("Select operation\n");
printf("Please enter '0' for sum, '1' for multiplication.\n");
scanf("%d", &operation);
printf("Please enter '0' to work on even numbers, '1' to work on odd numbers.\n");
scanf("%d", &flag);
printf("Please enter two different number:\n");
printf("Number 1: ");
scanf("%d", &N1);
printf("Number 2: ");
scanf("%d", &N2);
printf("Results\n");

switch (operation)
{
case 0:
write_file(sum(N1,N2,flag));
break;
case 1:
write_file(multi(N1,N2,flag));
break;
}
printf("The result is written to the results.txt file.\n");
}

if(g_operation == 2){
int pr_nb; /* prime number */
printf("Please enter an integer: ");
scanf("%d", &pr_nb);

for (int num = 2; num < pr_nb; num++){
printf("%d ",num);
	if (isprime(num) == 1) printf("is a prime number.\n"); 
	else printf("is not a prime number, it is dividible by %d.\n", isprime(num));
}
}

if(g_operation == 3){

print_file();
}

if(g_operation == 4){
int count = 0;
int deneme;
num = fopen("results.txt","r");
while (feof(num) == 0){
	fscanf(num,"%d ", &deneme);
	count++;
}
if (count % 3 == 0) for(int z=0; z < (count/3); z++) {sort_file();}
else for(int z=0; z < (count/3)+1; z++) {sort_file();}
remove("results.txt");
rename("temporary_file.txt", "results.txt");
print_file();
}

return 0;
}

int sum(int n1, int n2, int flag)
{
int temp, counter, result = 0; /* temp for swap */
if(n1 > n2){
	temp = n1;
	n1 = n2;
	n2 = temp;
}
for(counter = n1+1; counter < n2; counter++){
	if (flag == 0)
	{
		if (counter % 2 == 0 && n2-counter > 2){
			printf("%d + ", counter);
			result += counter;
		}
		else if(counter % 2 == 0){
		printf("%d = ", counter);
		result += counter;
		}
	}
	if (flag == 1)
	{
		if (counter % 2 == 1 && n2-counter > 2){
			printf("%d + ", counter);
			result += counter;
		}
		else if(counter % 2 == 1){
		printf("%d = ", counter);
		result += counter;
		}
	}
}
printf("%d\n", result);
return (result);
}

int multi(int n1, int n2, int flag)
{
int temp, counter,result = 1;
if(n1 > n2){
	temp = n1;
	n1 = n2;
	n2 = temp;
}

for(counter = n1+1; counter < n2; counter++){
	if (flag == 0)
	{
		if (counter % 2 == 0 && n2-counter > 2){
			printf("%d * ", counter);
			result *= counter;
		}
		else if(counter % 2 == 0){
		printf("%d = ", counter);
		result *= counter;
		}
	}
	if (flag == 1)
	{
		if (counter % 2 == 1 && n2-counter > 2){
			printf("%d * ", counter);
			result *= counter;
		}
		else if(counter % 2 == 1){
		printf("%d = ", counter);
		result *= counter;
		}
	}
}
printf("%d\n", result);
return (result);
}

int isprime(int a){
int flag = 1;	
for(int i=2; i <= sqrt(a) && flag == 1 ; i++){
	if( a % i == 0) {flag = i;}
}
return (flag);
}


void sort_file(){
int min1= 0x7fffffff,min2= 0x7fffffff, min3= 0x7fffffff, test, temp;
/* assigned the biggest integer to min1,min2,min3 to calculate */
num = fopen("results.txt", "r+");
int po1, po2;
/* we calculate minimum tree number*/
while(feof(num) == 0){
fscanf(num,"%d  ", &temp);
if (temp < min1){
	min3 = min2;
	min2 = min1;
	min1 = temp;
	continue;
}
else if(temp == min1){
	min3 = min2;
	min2=temp;
	continue;
}
else if(temp < min2 && temp > min1){
	min3 = min2;
	min2 = temp;
	continue;
}
else if(temp == min2){
	min3 = min2;
	continue;
}
else if(temp < min3 && temp > min2 && temp > min1){
	min3 = temp;
	continue;
}
}
sort = fopen("temporary_file.txt", "a+");

/* writing in the temporary_file.txt*/
if (min1 != 0x7fffffff ) fprintf(sort,"%d ", min1);
if (min2 != 0x7fffffff ) fprintf(sort,"%d ", min2);
if (min3 != 0x7fffffff ) fprintf(sort,"%d ", min3);

fclose(sort);

/* deleting minimum tree number in the result.txt */
for (int y=0; y < 3 ; y++)
{
	rewind(num);
	while(feof(num) == 0){
		temp = ftell(num);
		fscanf(num,"%d ", &test);
		if(test == min1){
			po1= temp;
			po2=ftell(num);
			min1=0x80000000;
			break;
		}
		else if(test == min2){
			po1= temp;
			po2=ftell(num);
			min2=0x80000000;
			break;
			
		}
		else if(test == min3){
			po1= temp;
			po2=ftell(num);
			min3=0x80000000;
			break;
		}
	}
	fseek(num,po1,SEEK_SET);
	for(int x = po1; x < po2; x++) fprintf(num,"%c", ' ');
}
fclose(num);
}

void print_file(){
num = fopen("results.txt", "r");
	
int read;
	while(feof(num) == 0){
	fscanf(num,"%d ", &read);
	printf("%d ",read);
	}
fclose(num);
printf("\n");
}


void write_file(int number){
num = fopen("results.txt","a+");
fprintf(num,"%d ", number);
fclose(num);
}
