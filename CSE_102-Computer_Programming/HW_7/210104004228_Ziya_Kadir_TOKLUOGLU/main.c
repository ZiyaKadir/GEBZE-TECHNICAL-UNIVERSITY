#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_WORD 50 /* number of readed word from txt file*/
#define MAX_COLUMNS 15 /* number of columns of game board*/
#define MAX_ROWS 15   /* number of rows of game board */
#define MAX_I_WORDS 7 /* number of words, game board have */

typedef enum{
    right=1,
    left=2,
    up=3,
    down=4,
    up_right=5,
    up_left=6,
    down_right=7,
    down_left=8
  }ways;

  void red(){
  printf("\033[0;31m");
  }

  void reset(){
    printf("\033[0m");
  }

int ispalindrome(char word[]);

void read_file(char words[][10]);

void select_words(char words[][10], char select[][10]);

void clear(char words[][MAX_COLUMNS]); /* for cleaning. if the game board has garbage value inside*/

int select_way();

int control(char game_board[][MAX_COLUMNS],char word[],int x,int y,int move_x,int move_y);

void fill_board(char game_board[][MAX_COLUMNS],char word[],int x,int y,int move_x,int move_y);

void fill_random(char game_board[][MAX_COLUMNS]);

void delete_word(char game_board[][MAX_COLUMNS],int coordinates[][4],int length,int i);

void print_gameboard(char game_board[][MAX_COLUMNS]);

int startpoint_y(int moved,int length);

int startpoint_x(int moved,int length);

int main(){

int coordinates[MAX_I_WORDS][4];/* I keep the word's feature in the game_board*/
char words[MAX_WORD][10];
char s_words[MAX_I_WORDS][10];
char game_board[MAX_ROWS][MAX_COLUMNS];

int i,way,controller;
int x,y;
int point=0, life=3;
int move_x,move_y;
int user_x,user_y;
char user[15];
char t;
srand(time(NULL));

clear(game_board); /* for cleaning. if the game board has garbic value inside*/

read_file(words);

select_words(words,s_words);

  for(i=0; i<MAX_I_WORDS; i++){
    do {
      way=(rand()%8)+1; /*selecting which way to try to word assign the game_board array*/
      move_x=0; move_y=0;
      /*determining coordinates moving*/
      if(way==right || way==up_right || way==down_right) move_x=1;
      if(way==left || way==up_left || way==down_left) move_x=-1;
      if(way==up || way ==up_right || way==up_left) move_y=-1;
      if(way==down || way== down_right || way==down_left) move_y=1;
      /* 1 for increase, -1 for decrease if staying 0 that means not moving in that direction*/
      int length=strlen(s_words[i]);
      x=startpoint_x(move_x, length);
      y=startpoint_y(move_y, length);


      controller=control(game_board,s_words[i],x,y,move_x,move_y);
      if(controller==1) fill_board(game_board,s_words[i],x,y,move_x,move_y);

    } while(controller == -1);

    printf("%s\n",s_words[i]);

    coordinates[i][0]=x;
    coordinates[i][1]=y;
    coordinates[i][2]=move_x;
    coordinates[i][3]=move_y;

    printf("x:%d\n",coordinates[i][0]);
    printf("y:%d\n",coordinates[i][1]);

  /* if you want to see words' direction, you can remove the below command line*/
  /*
    printf("movex:%d\n",coordinates[i][2]);
    printf("movey:%d\n",coordinates[i][3]);
  */
    printf("--------------------------\n");


  }
  fill_random(game_board);
//  delete_word(game_board,coordinates,4,1);
int length;
int checking=0;
int check;
/* game_part*/
do {
  check=0;
  i=0;
  print_gameboard(game_board);
  printf("Enter coordinates and word:");
  /* cleaning string because the garbage value which is droped from the previous step */
  while(i<15){
    user[i]='\0';
    i++;
  }
  /* taken all chractes the user given*/
  i=0;
  while ((t=getchar()) != '\n'){
    user[i]=t;
    i++;
  }
  /* quit command*/
  if(user[0]== ':' && user[1]== 'q' && user[2]=='\0'){
    printf("Your total point is %d\n", point);
     break;
   }
   /* taking value and string from the string */
  sscanf(user,"%d %d %s", &user_x,&user_y,user);
    /* if you want to see user variable which are taken, remove below command line*/
    /*
    printf("user_x:%d\n", user_x);
    printf("user_y:%d\n", user_y);
    printf("user:%s\n", user);
    */

    /* controlling and deleting words on board */
    for(i=0; i<MAX_I_WORDS; i++){

      if(strcmp(s_words[i],user)==0 && user_x==coordinates[i][0] && user_y==coordinates[i][1]){
        length=strlen(s_words[i]);

        delete_word(game_board,coordinates,length,i);

        point+=2;
        printf("Founded! You got 2 points. Your total points %d\n", point);
        check = 1;
        break;
        }
        /*control if the word is palindrome the startpoint_x and startpoint_y should changed*/
     else if(strcmp(s_words[i],user)==0 && ispalindrome(s_words[i])==1){
        length=strlen(s_words[i]);
        if (coordinates[i][2]==1) coordinates[i][0]+=(length-1);
        else if(coordinates[i][2]==-1) coordinates[i][0]-=(length-1);
        if (coordinates[i][3]==1) coordinates[i][1]+=(length-1);
        else if(coordinates[i][3]==-1) coordinates[i][1]-=(length-1);

        coordinates[i][2]*=-1;
        coordinates[i][3]*=-1;

        delete_word(game_board,coordinates,length,i);
        point+=2;
        printf("Founded! You got 2 points. Your total points %d\n", point);
        check = 1;
      //  checking==1;
        break;
      }

    }
    if(check==0) {
      printf("Wrong choice! You have only %d lefts\n",life);
      life--;
    }
    if (point==14){
      print_gameboard(game_board);
      printf("------------YOU WON--------------\n ");
    }

} while(life >= 0 && point<14);

return 0;
}

void read_file(char words[][10]){

FILE *word;
  word=fopen("wordlist.txt","r");
  int i;
  for(i=0; i<MAX_WORD; i++){
  fscanf(word,"%s",words[i]);
  }
  fclose(word);
}

void select_words(char words[][10], char select[][10]){

int i,j,random,control;
printf("----------------------------------\n");
  for (i=0; i<MAX_I_WORDS; i++){
    random=rand()%MAX_WORD;
    strcpy(select[i],words[random]);

    for(j=i-1; j>=0; j--){
        control=strcmp(select[j],words[random]);
        if(control==0){
          i--;
          break;
        }
    }
  }
}

void clear(char game_board[][MAX_COLUMNS]){

  int i,k;

  for(i=0; i<MAX_ROWS;i++){
      for(k=0; k<MAX_COLUMNS; k++){
        game_board[i][k]=' ';
      }
  }
}

int select_way(){
  int way=(rand()%8)+1;
  return way;
}

void fill_board(char game_board[][MAX_COLUMNS],char word[],int x,int y,int move_x,int move_y)
/* increase or decrease move_x move_y for movement of x-direction and y-direction */
{
  int i=0;
  int length=strlen(word);

  while(word[i] != '\0'){

    game_board[y][x]=word[i];
    if(move_x==1) x++;
    else if(move_x==-1) x--;
    if(move_y==1) y++;
    else if(move_y==-1) y--;
    i++;
  }
}
int control(char game_board[][MAX_COLUMNS],char word[],int x,int y,int move_x,int move_y)
/* increase or decrease move_x move_y for movement of x-direction and y-direction */
{
  int i=0;
      //printf("%s", word);
      while(word[i] != '\0'){

        if(!(game_board[y][x]==' ')) return -1;

        if(move_x==1) x++;
        else if(move_x==-1) x--;
        if(move_y==1) y++;
        else if(move_y==-1) y--;
        i++;
      }
  return 1;
}

void fill_random(char game_board[][MAX_COLUMNS]){

    for(int i=0; i<15;i++){
      for(int m=0; m<15;m++){
        if(game_board[i][m] == ' ') game_board[i][m] = (rand()%26) +97; /*you can change 97 to 65 then you can see clear random letter*/
      }
    }
}

int startpoint_y(int moved,int length){
  int y;
  if(moved==1) y=(rand()%(MAX_ROWS-length));
  else if(moved==-1) y=(rand()%(MAX_ROWS-length))+length;
  else if(moved==0) y=rand()%MAX_ROWS;
  return y;
}

int startpoint_x(int moved,int length){
  int x;
  if(moved==1) x=(rand()%(MAX_COLUMNS-length));
  else if (moved==-1) x=(rand()%(MAX_COLUMNS-length))+length;
  else if(moved==0) x=rand()%MAX_COLUMNS;
  return x;
}

void delete_word(char game_board[][MAX_COLUMNS],int coordinates[][4],int length,int i){

  int k;
  int x=coordinates[i][0];
  int y=coordinates[i][1];
  int move_x=coordinates[i][2];
  int move_y=coordinates[i][3];



  for (k=0; k<length; k++){

    game_board[y][x]='X';

    if(move_x==1) x++;
    else if(move_x==-1) x--;
    if(move_y==1) y++;
    else if(move_y==-1) y--;
  }
}

void print_gameboard(char game_board[][MAX_COLUMNS]){

  int i,j;
  printf("  ");
  for (i=0; i < MAX_COLUMNS; i++) printf("%2d", i);
  printf("\n");
  for(i=0; i<MAX_ROWS; i++){
    if (i<10) {
      printf("%d ",i);
    }
    else{
      printf("%d",i);
    }
      for(j=0; j<MAX_COLUMNS; j++){
        if (game_board[i][j]<91)
        {
        /*  red();*/ /* if you want to see clearly you can use this*/
          printf("%2c",game_board[i][j]);
        /*  reset();*/ /* if you want to see clearly you can use this*/
        }
        else printf("%2c",game_board[i][j]);
      }
      printf("\n");
  }
}

int ispalindrome(char word[]){

int length=strlen(word);
int i=0;

while (i<length/2){
  if (word[i]!=word[length-1-i]) return -1;
  i++;
}
return 1;

}
