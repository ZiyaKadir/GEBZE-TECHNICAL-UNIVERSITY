#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void red(){
printf("\033[0;31m");
}
void green(){
printf("\033[0;32m");
}
void blue(){
printf("\033[0;34m");
}
void yellow(){
  printf("\033[0;33m");
}
void reset () {
  printf("\033[0m");
}
typedef enum{
space=0,
v_line=1, /* vertical line*/
h_line=2, /* horizental line */
p_point = 3,/* penalty point*/
f_point = 4,/* finish point */
f_player = 5,/* first player */
s_player = 6 /* second player */
}Signs;

int dice(void){
char c= getchar();
int dice=rand()%6+1;
printf("DICE: %d\n", dice);
  return dice;
}

int startGame(){

int d1,d2; /* player 1 and player 2 dice */
int decide=0; /* who is going to be first*/
do{/* continue until the determine who is going to be first*/
yellow();
printf("Player 1... press ENTER to dice");
d1=dice();
reset();
blue();
printf("Player 2... press ENTER to dice");
d2=dice();
reset();
if (d1 == d2) printf("Same dice value... Please try again.\n");
else if(d1 > d2) decide=1;
else decide = 2;

}while(decide==0);
  return decide;
}

void printMap(int map[][30]){

  for (int i=0; i < 15; i++){
    for(int k=0; k<30; k++)
    {
      if(map[i][k]== f_player){
        yellow();
        printf("1");
        reset();
      }
      else if(map[i][k]== s_player) {
        blue();
        printf("2");
        reset();
      }
      else if(map[i][k]== f_point)
      {
        green();
        printf("_");
        reset();
      }
      else if(map[i][k]== p_point)
      {
        red();
        printf("X");
        reset();
      }
      else if(map[i][k]== v_line) printf("|");
      else if(map[i][k]== h_line) printf("-");
      else if(map[i][k]== space) printf(" ");

    }
    printf("\n");
  }

}

int main() {
  int decide;
  int dice1,dice2;
  srand(time(NULL));
  int m1=0,m2=0;/* movement of the Player 1 and Player 2*/
  int map[15][30];
/* assigned value of the array of map to draw a map */
for (int i=0; i < 15; i++)/*drawing map with fundamental character*/
{
  for(int k=0; k<30; k++)
  {
    if (i==1 && k==1) map[i][k]=f_player;
    else if (i==3 && k==3) map[i][k]=s_player;

    else if (i==2 && k==1) map[i][k]=f_point;
    else if (i==4 && k==3) map[i][k]=f_point;

    else if (i==1 && k==14) map[i][k]=p_point;
    else if (i==7 && k==28) map[i][k]=p_point;
    else if (i==13 && k==14) map[i][k]=p_point;
    else if (i==3 && k==10) map[i][k]=p_point;
    else if (i==3 && k==18) map[i][k]=p_point;
    else if (i==5 && k==26) map[i][k]=p_point;
    else if (i==10 && k==26) map[i][k]=p_point;
    else if (i==11 && k==10) map[i][k]=p_point;
    else if (i==11 && k==18) map[i][k]=p_point;

    else if(i==0 && k<=29 && k>=0) map[i][k]=h_line;
    else if(i==14 && k<=29 && k>=0) map[i][k]=h_line;
    else if(k==0 && i<14 && i>0) map[i][k]=v_line;
    else if(k==29 && i<14 && i>0) map[i][k]=v_line;

    else if(i==2 && k<=27 && k>=2) map[i][k]=h_line;
    else if(i==12 && k<=27 && k>=2) map[i][k]=h_line;
    else if(k==2 && i<12 && i>2) map[i][k]=v_line;
    else if(k==27 && i<12 && i>2) map[i][k]=v_line;

    else if(i==4 && k<=25 && k>=4) map[i][k]=h_line;
    else if(i==10 && k<=25 && k>=4) map[i][k]=h_line;
    else if(k==4 && i<10 && i>4) map[i][k]=v_line;
    else if(k==25 && i<10 && i>4) map[i][k]=v_line;
    else map[i][k]=space;
  }
}

printf("\n\n\n\n");
printMap(map);
printf("\n\n\n");
printf("To start to game, players should dice and decide who is going to start first according to it...\n");

decide=startGame(); /* to decide which is going to be first */
if (decide == 1) printf("*** PLAYER 1 will start the game... *** \n");
else if(decide == 2) printf("*** PLAYER 2 will start the game... *** \n");

int k=1,l=1; /* the place of player 1 in array */
int m=3,n=3; /* the place of player 2 in array */
do{ /* to move player 1 and player 2 in array */
int controller=1; /* to control if one of players finish the other player should not play */
int temp=0; /* to keep the value of k l m n int this way ı protect the place of players*/
  if(decide == 1){
    yellow();
    printf("PLAYER 1... press ENTER to dice...");
    dice1=dice();
    reset();
   if(l==1 && k > 1 ){
      temp=k;
      k-=dice1;
      if(k < 2) controller=0;

        k=temp;
    }

    if(controller == 1){
      blue();
    printf("PLAYER 2... press ENTER to dice...");
    dice2=dice();
    reset();
    if(n==3 && m > 3 ){
       temp=m;
       m-=dice2;
       if(m < 4) controller=-1;

         m=temp;
     }
  }
}
  else if(decide == 2){
    blue();
    printf("PLAYER 2... press ENTER to dice...");
    dice2=dice();
    reset();
    if(n==3 && m > 3 ){
       temp=m;
       m-=dice2;
       if(m < 4) controller=-1;
         m=temp;
     }
     if(controller == 1){
       yellow();
        printf("PLAYER 1... press ENTER to dice...");
        dice1=dice();
        reset();
            if(l==1 && k > 1 ){
            temp=k;
            k-=dice1;
                if(k < 2) controller=0;
            k=temp;
            }
        }
  }
  map[k][l]=space; /* to delete previous place of the player 1 on each turn*/
  map[m][n]=space; /* to delete previous place of the player 2 on each turn*/
  while(dice1 > 0){ /* to move of player 1*/
    if(k==1 && l < 28) l++;
    else if(l==28 && k < 13) k++;
    else if(k==13 && l > 1) l--;
    else if(l==1 && k > 1) k--;
    dice1--;
  }
  yellow();

  if (k==1 && l==14) {/* controlling if player 1 in the penalty point*/
    map[k][l]=p_point;
    l-=2;
    printf("Penalty for player 1...\n");
  }
  else if (k==7 && l==28) {
    map[k][l]=p_point;
    k-=2;
    printf("Penalty for player 1...\n");
  }
  else if (k==13 && l==14) {
    map[k][l]=p_point;
    l+=2;
    printf("Penalty for player 1...\n");
  }
  reset();

  while(dice2 > 0){ /*to move of player 2*/
    if(m == 3 && n < 26) n++;
    else if(n == 26 && m < 11) m++;
    else if(m == 11 && n > 3) n--;
    else if(n == 3 && m > 3) m--;
    dice2--;
  }

  blue();
  if (m==3 && n==10) {/* controlling if player 2 in the penalty point*/
    map[m][n]=p_point;
    n-=2;
    printf("Penalty for player 2...\n");
  }
  else if (m==3 && n==18) {
    map[m][n]=p_point;
    n-=2;
    printf("Penalty for player 2...\n");
  }
  else if (m==5 && n==26) {
    map[m][n]=p_point;
    m-= 2;
    printf("Penalty for player 2...\n");
  }
  else if (m==10 && n==26) {
    map[m][n]=p_point;
    m-=2;
    printf("Penalty for player 2...\n");
    }
  else if (m==11 && n==10) {
    map[m][n]=p_point;
    n+=2;
    printf("Penalty for player 2...\n");
   }
  else if (m==11 && n==18) {
    map[m][n]=p_point;
    n+=2;
    printf("Penalty for player 2...\n");
  }
  reset();

  map[k][l]=f_player; /* the last place of player 1 after moving */
  map[m][n]=s_player; /* the last place of player 2 after moving */
  if (controller==0){
    printf("\n\n ***PLAYER 1 WON THE GAME *** \n");
    map[2][1]=f_point; /*if player 1 delete final point, final point assigned again*/
    map[4][3]=f_point; /*if player 2 delete final point, final point assigned again*/
    printMap(map);
    break;
  }
   if(controller==-1){
    printf("\n\n ***PLAYER 2 WON THE GAME *** \n");
    map[2][1]=f_point;  /*if player 1 delete final point, final point assigned again*/
    map[4][3]=f_point;  /*if player 2 delete final point, final point assigned again*/
    printMap(map);
    break;
  }
  printMap(map);

}while(1);

  return 0;
}
