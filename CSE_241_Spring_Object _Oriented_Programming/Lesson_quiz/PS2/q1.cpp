#include <iostream>
#include <cstdlib>
#include <cstring>
#include <time.h>

using namespace std;


typedef struct Gladiator{
	char name[10];
	int num , denum;
	bool alive = true;
	int num_wins = 0;

}Gladiator;

bool hit_or_not(int num, int denum){
	int pos;
	pos = (rand() % denum) + 1;
	if(pos <= num){
		return true;
	}
	else{
		return false;
	}
}


int select(Gladiator players[],int num_player){

	int ind_player = 0; // dangerest player index

	for(int i =0; i < num_player -1; i++){
		if( float(players[i].num / players[i].denum) > float(players[i+1].num / players[i+1].denum)){
			ind_player = i;
		}
		else{
			ind_player = i+1;
		}
	}

	return ind_player;

}

int main(){

srand(time(0));

	int counter = 0 ;

	Gladiator gladiators[3];


	// assigning gladiators name and printing on the screen 

	strcpy(gladiators[0].name, "Aeron");
	strcpy(gladiators[1].name, "Bob");
	strcpy(gladiators[2].name, "Charlie");

	cout << "=============Gladiators============" << endl;

	for (int i=0; i < 3; i++){
		cout << i+1 << ". gladiators =" << gladiators[i].name << endl;
	}

 //assigning the probablity of gladiators 1 = 1\3
	gladiators[0].num = 1;
	gladiators[0].denum = 3;
 //assigning the probablity of gladiators 2 = 1\2
	gladiators[1].num = 1;
	gladiators[1].denum = 2;
 //assigning the probablity of gladiators 3 = 1\1
	gladiators[2].num = 1;
	gladiators[2].denum = 1;


	int player_alive=3;
	int attack;
	bool success;

	while (counter < 1000){

		for(int i=0; i < 3; i++){
			gladiators[i].alive = true;
		}
		for (int i=0; i < 3; i++){
			if (gladiators[i].alive == true){
				attack = select(gladiators,3);
				success = hit_or_not(gladiators[i].num ,gladiators[i].denum);
				if (true == success){
					gladiators[attack].alive = false;
				}
				else{
					continue;
				}
			}
			else{
				continue;
			}

		}
		for(int i=0; i<3; i++){
			if(gladiators[i].alive == false) player_alive --;  
		}
		if(player_alive <=1){
			for(int i=0; i < 3; i++){
				if(gladiators[i].alive == true){
					gladiators[i].num_wins ++;
				}
			}
		}
	counter ++;
	}

	for (int i=0; i < 3; i++){
		cout << gladiators[i].name << " " << gladiators[i].num_wins << endl;
	}




}