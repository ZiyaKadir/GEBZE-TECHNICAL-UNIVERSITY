#include <iostream>
#include <stdlib.h>
#include <time.h>


#include "Robot.hpp"
#include "roomba.hpp"
#include "robocop.hpp"
#include "optimusprime.hpp"
#include "bulldozer.hpp"
#include "War.hpp"



using namespace std;

int optimusprime::num_optimus = 0;
int bulldozer::num_bulldozer = 0;
int robocop::num_robocop = 0;
int roomba::num_roomba = 0;
int Robot::num_total_robot = 0;


int main(){

	srand(time(NULL));
	int x,y;
	string temp;
	War robot_fight;

	//creating robot types according to their initial number value in the map
	
	Robot** R_bulldozer = new Robot*[INITIAL_bulldozer];
		for(int k=0; k< INITIAL_bulldozer; k++){
			R_bulldozer[k] = new bulldozer; 
		}
	for(int i=0; i < INITIAL_bulldozer; i++){
		x = rand() % 10;
		y = rand() % 10;
		// if location emphty add else continue
		if(robot_fight.isLocationEmpty(x,y) == true){
			robot_fight.addRobot(R_bulldozer[i],x,y);
		}
		else{
			i --;
		}
	}


	Robot** R_roomba = new Robot*[INITIAL_roomba];
		for(int k=0; k< INITIAL_roomba; k++){
			R_roomba[k] = new roomba; 
		}
	for(int i=0; i < INITIAL_roomba; i++){
		x = rand() % 10;
		y = rand() % 10;
		// if location emphty add else continue
		if(robot_fight.isLocationEmpty(x,y) == true){
			robot_fight.addRobot(R_roomba[i],x,y);
		}
		else{
			i --;
		}
	}


	Robot** R_robocop = new Robot*[INITIAL_robocop];
		for(int k=0; k< INITIAL_robocop; k++){
			R_robocop[k] = new robocop; 
		}
	for(int i=0; i < INITIAL_robocop; i++){
		x = rand() % 10;
		y = rand() % 10;
		// if location emphty add else continue
		if(robot_fight.isLocationEmpty(x,y) == true){
			robot_fight.addRobot(R_robocop[i],x,y);
		}
		else{
			i --;
		}
	}

	Robot** R_optimusprime = new Robot*[INITIAL_optimusprime];
		for(int k=0; k< INITIAL_optimusprime; k++){
			R_optimusprime[k] = new optimusprime; 
		}
	for(int i=0; i < INITIAL_optimusprime; i++){
		x = rand() % 10;
		y = rand() % 10;
		// if location emphty add else continue
		if(robot_fight.isLocationEmpty(x,y) == true){
			robot_fight.addRobot(R_optimusprime[i],x,y);
		}
		else{
			i --;
		}
	}

	// robot_fight.print_map();
	// infinite loop for game
	while(true){
		// getline(cin,temp);
		// robot_fight.print_map();
		//robot_fight.undraw(WORLDSIZE + 3, 150);
		robot_fight.SimulateOneStep();
		
		if(robot_fight.getRobotAt(0,0)->get_total_number() <=1){
			cout << "Game is over" << endl;
			robot_fight.print_map();
		}
	}

	return 0;
}

