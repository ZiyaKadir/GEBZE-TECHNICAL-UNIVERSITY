#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STACK_BLOCK_SIZE 10

typedef struct {

    char * array;
    int currentsize;
    int maxsize;

}stack;


void push(stack *s, char d);

char pop(stack *s);

stack *init_return();

int init(stack *s);



int main(){

  int T_size; /* Tower size*/

  char temp;

  stack *stack[3];

  printf("Enter Tower size:");
  scanf("%d", &T_size);

  /*initilaziton stacks*/
  for(int i=0; i<3; i++){
      stack[i]=init_return();
  }
  /* altered the max_size */
  if (T_size > stack[0]->maxsize)
  stack[0]->maxsize=T_size;
  stack[0]->currentsize=T_size;

  /*filling the first stack*/
  for(int i= 0; i < T_size; i++)
  {
    stack[0]->array[i]= (T_size-i);
    //printf("%d\n", stack[0]->array[i]);
  }


/* ı tried the while(!(strlen(stack[3]->array == T_size)) but ı dont know why is working therefore ı control the loop with the number of move*/

  unsigned long long int num_move; /*number of move of the game*/
  num_move=pow(2,T_size);



  /* move number is special if it's left when divided by 3 decide to move around the which stack */
  for (int i = 1; i <= num_move -1; i++)
  {
    /* to carry to right stack we divided the disk number in this way we decide stack which we started*/
    if(T_size%2==1){
      if (i % 3 == 1){

        if(stack[2]->array[0] == '\0'){
          temp=pop(stack[0]);
          push(stack[2],temp);
          printf("Move the disk %d from '%d' to '%d'\n",temp,1,3);
        }
        else if(stack[0]->array[0] == '\0'){
          temp=pop(stack[2]);
          push(stack[0],temp);
          printf("Move the disk %d from '%d' to '%d'\n",temp,3,1);
        }
        else if(stack[0]->array[stack[0]->currentsize-1] < stack[2]->array[stack[2]->currentsize-1]){
          temp=pop(stack[0]);
          push(stack[2],temp);
          printf("Move the disk %d from '%d' to '%d'\n",temp,1,3);
        }
        else{
          temp=pop(stack[2]);
          push(stack[0],temp);
          printf("Move the disk %d from '%d' to '%d'\n",temp,3,1);
        }
      }

      else if (i % 3 == 2){

                if(stack[1]->array[0] == '\0'){
                  temp=pop(stack[0]);
                  push(stack[1],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,1,2);
                }
                else if(stack[0]->array[0] == '\0'){
                  temp=pop(stack[1]);
                  push(stack[0],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,2,1);
                }
                else if(stack[0]->array[stack[0]->currentsize-1] < stack[1]->array[stack[1]->currentsize-1]){
                  temp=pop(stack[0]);
                  push(stack[1],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,1,2);
                }
                else{
                  temp=pop(stack[1]);
                  push(stack[0],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,2,1);
                }
      }
      else if (i % 3 == 0){

                if(stack[1]->array[0] == '\0'){
                  temp=pop(stack[2]);
                  push(stack[1],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,3,2);
                }
                else if(stack[2]->array[0] == '\0'){
                  temp=pop(stack[1]);
                  push(stack[2],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,2,3);
                }
                else if(stack[1]->array[stack[1]->currentsize-1] < stack[2]->array[stack[2]->currentsize-1]){
                  temp=pop(stack[1]);
                  push(stack[2],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,2,3);
                }
                else{
                  temp=pop(stack[2]);
                  push(stack[1],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,3,2);
                }
      }

      /* if you want to disks on the stack you can delete the command line and check*/
    /*
      printf("1.cubuk: %s\n",stack[0]->array);
      printf("2.cubuk: %s\n",stack[1]->array);
      printf("3.cubuk: %s\n",stack[2]->array);
    */

    }
    else{

      if (i % 3 == 1){

        if(stack[1]->array[0] == '\0'){
          temp=pop(stack[0]);
          push(stack[1],temp);
          printf("Move the disk %d from '%d' to '%d'\n",temp,1,2);
        }
        else if(stack[0]->array[0] == '\0'){
          temp=pop(stack[1]);
          push(stack[0],temp);
          printf("Move the disk %d from '%d' to '%d'\n",temp,2,1);
        }
        else if(stack[0]->array[stack[0]->currentsize-1] < stack[1]->array[stack[1]->currentsize-1]){
          temp=pop(stack[0]);
          push(stack[1],temp);
          printf("Move the disk %d from '%d' to '%d'\n",temp,1,2);
        }
        else{
          temp=pop(stack[1]);
          push(stack[0],temp);
          printf("Move the disk %d from '%d' to '%d'\n",temp,2,1);
        }
      }

      else if (i % 3 == 2){

                if(stack[2]->array[0] == '\0'){
                  temp=pop(stack[0]);
                  push(stack[2],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,1,3);
                }
                else if(stack[0]->array[0] == '\0'){
                  temp=pop(stack[2]);
                  push(stack[0],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,3,1);
                }
                else if(stack[0]->array[stack[0]->currentsize-1] < stack[2]->array[stack[2]->currentsize-1]){
                  temp=pop(stack[0]);
                  push(stack[2],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,3,1);
                }
                else{
                  temp=pop(stack[2]);
                  push(stack[0],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,1,3);
                }
      }
      else if (i % 3 == 0){

                if(stack[1]->array[0] == '\0'){
                  temp=pop(stack[2]);
                  push(stack[1],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,3,2);
                }
                else if(stack[2]->array[0] == '\0'){
                  temp=pop(stack[1]);
                  push(stack[2],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,2,3);
                }
                else if(stack[1]->array[stack[1]->currentsize-1] < stack[2]->array[stack[2]->currentsize-1]){
                  temp=pop(stack[1]);
                  push(stack[2],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,2,3);
                }
                else{
                  temp=pop(stack[2]);
                  push(stack[1],temp);
                  printf("Move the disk %d from '%d' to '%d'\n",temp,3,2);
                }
      }

      /* if you want to disks on the stack you can delete the command line and check*/
      /*
      printf("1.cubuk: %s\n",stack[0]->array);
      printf("2.cubuk: %s\n",stack[1]->array);
      printf("3.cubuk: %s\n",stack[2]->array);
      */

  }
}



  return 0;
}


/* always control the currentsize and allocation according to currentsize and adding new character(disk)*/
void push(stack *s, char d){


  char *temp=(char *)calloc(s->currentsize+1,sizeof(char));

  strcpy(temp,s->array);

  temp[s->currentsize]=d;

  s->array= (char *)calloc(s->currentsize+1,sizeof(char));

  strcpy(s->array,temp);

  s->currentsize++;

}
/* always control the currentsize and allocation according to currentsize and removing last character(disk)*/
char pop(stack *s){

  int length= strlen(s->array);

  char character=s->array[length-1];

  char *temp=(char *)calloc(length-1,sizeof(char));

  strncpy(temp,s->array,length-1);

  s->array= (char *)calloc(length-1,sizeof(char));

  strcpy(s->array,temp);

  s->currentsize=length-1;

  return character;
}

stack * init_return()
{
	stack *temp= (stack *)calloc(1, sizeof(stack));

	temp->maxsize= STACK_BLOCK_SIZE;
	temp->currentsize= 0;
	temp->array=(char *)calloc(STACK_BLOCK_SIZE, sizeof(char));

	return temp;
}

/* controlling stack is emphty or not */
int init(stack *s){

  if(s == NULL) return 0;
  else return 1;

}
