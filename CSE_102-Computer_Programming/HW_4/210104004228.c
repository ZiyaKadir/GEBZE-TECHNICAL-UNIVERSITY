#include<stdio.h>

int main()
{
int operation, a, b, c;
FILE *kok;
do{
    printf("\n\n\nSelect an operation....\n");
    printf("1. -> Enter the coefficients.\n");
    printf("2. -> Draw the graph.\n");
    printf("3. -> Print the graph into a .txt file.\n");
    printf("4. -> Exit\n");

    printf("Choice: ");
    scanf("%d", &operation);

        if (operation == 1){
            printf("Please enter the coefficient for the following equation: x=a*(y*y) + b*y + c\n");
            printf("\n\na: ");          
            scanf("%d", &a);
            printf("b: ");
            scanf("%d", &b);
            printf("c: ");
            scanf("%d", &c);

            kok = fopen("coefficients.txt","w+");
            if (kok == NULL)
            {
                printf("Error : coefficient.txt file has not been created\n");
            }
            else printf("coefficient.txt file has been created\n");
            
            fprintf(kok,"%d\n", a);
            fprintf(kok,"%d\n", b);
            fprintf(kok,"%d\n", c);
            fclose(kok);
        }
else if (operation == 2)
{
           
int a,b,c; /* coefficient from the coefficient file */
int x,y; /* coordinates*/
int next_1,next_2; /* to understand next partof  the the sign (#)which I used for drawing 
                    because I dont want to print numbers on the line */

FILE *kok;
    kok = fopen("coefficients.txt","r");
     if (kok == NULL){
       printf("the coefficients.txt file does not exist\n"); continue;
    }
        fscanf(kok, "%d", &a); /* taking value of one of coefficient from the file*/
        fscanf(kok, "%d", &b); /* taking value of one of coefficient from the file*/
        fscanf(kok, "%d", &c); /* taking value of one of coefficient from the file*/
        fclose(kok);
    printf("Printing the graph of x = %d*(y*y) + %d*y + %d.\n", a, b, c);
    for(y=16; y >= -16; y--){

            for(x=-55; x <= 55; x++){
                if(x == a*(y*y) + b*y +c){
                        printf("\033[1;34m"); /* change the text to blue */
						printf("#");
						printf("\033[0m");/* Resets the text to default color*/
                        next_1=x+1;
                        next_2=x+2;
                }
                else if(y%5==0 && x==-2 && y != 0){ 
                        printf("\033[1;31m"); /* change the text to red */
						printf("\033[1;33m"); /* change the text to yellow */
                        if (y > 0 && y < 10) printf("%d",y);
                        else if (y > 9) {
                            if (x != next_1) printf("\b%d",y);
                            else printf(" ");
                        }
                        else if (y < 0 && y > -10) {
                            if (x != next_1) printf("\b%d",y);
                            else printf(" ");
                        }
                        else if (y < -9){
                            if (x != next_1 && x != next_2)  printf("\b\b%d",y);
                            else printf(" ");
                            
                        } 
                        printf("\033[0m"); /* Resets the text to default color*/
                }
                else if((x%10==9 || x%10==-1) && y==-1){
                        printf("\033[1;31m"); /* change the text to red */
						printf("\033[1;33m"); /* change the text to yellow */
                        if (x > -1 && x < 9) printf("%d",x+1);
                        else if (x > 8) {
                            if (x != next_1) printf("\b%d",x+1);
                            else printf(" ");
                        }
                        else if (x == -1){
                            if (x != next_1) printf("%d",x+1);
                            else printf(" ");

                        }
                        else if (x < -8){
                            if (x != next_1 && x != next_2)  printf("\b\b%d",x+1);
                            else printf(" ");
                            
                        } 
                        printf("\033[0m"); /* Resets the text to default color*/
                }
                else if(y==16 && x==0) printf("^");
                else if(y==-16 && x==0) printf("v");
                else if(x == -55 && y==0) printf("<");
                else if(x == 55 && y==0) printf(">"); 
                else if(x==0) printf("|");
                else if(y == 0 ) printf("-");
                else printf(" ");

                if (x == 55) printf("\n");
            }
    }
}
else if(operation==3)
{
int a,b,c;
int x,y;
int result;
FILE *pri;
FILE *kok;
    kok = fopen("coefficients.txt","r");
     if (kok == NULL){
       printf("the coefficients.txt file does not exist\n");
    }
        fscanf(kok, "%d", &a);
        fscanf(kok, "%d", &b);
        fscanf(kok, "%d", &c);
        printf("Coefficients has been read from the coefficient file.\n");
        fclose(kok);
    pri=fopen("graph.txt", "w");
        for(y=16; y >= -16; y--){

            for(x=-55; x <= 55; x++){
                if(x == a*(y*y) + b*y +c){
                    fprintf(kok,"#");
                }
                else{
                    if(y==16 && x==0) fprintf(kok,"^");
                    else if(y==-16 && x==0) fprintf(kok,"v");
                    else if (x==0) fprintf(kok,"|");
                    else if (x == -55 && y==0) fprintf(kok,"<");
                    else if (x == 55 && y==0) fprintf(kok,">");
                    else if(y == 0 ) fprintf(kok,"-");
                    else fprintf(kok," ");
                }
                if (x == 55) fprintf(kok,"\n");
            }
    }
    printf("The graph of x = %d*(y*y) + %d*y + %d has been written to graph.txt file.\n\n", a, b, c);
    fclose(pri);
}
}while(operation != 4);

return 0;
}
