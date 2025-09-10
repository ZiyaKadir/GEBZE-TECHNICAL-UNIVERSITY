#include "Robot.hpp"

Robot::Robot(){

}


Robot::Robot(const Robot& other){

}
Robot::Robot(int newType, int newStrength, int newHit, string new_name){
	type = newType;
	strength = newStrength;
	hitpoints = newHit;
	name = new_name;

	selected = false;
	num_total_robot ++;
}


Robot::~Robot(){

}


// Setter

void Robot::set_type(int n_type){
	type = n_type;
}
void Robot::set_strength(int n_strength){
	strength = n_strength;
}
void Robot::set_hitpoints(int n_hitpoints){
	hitpoints = n_hitpoints;
}
void Robot::set_name(string n_name){
	name = n_name;
}
void Robot::set_selected(bool choose){
	selected =choose;
}

void Robot::set_X(int temp_x){
	position_x = temp_x;
}
void Robot::set_Y(int temp_y){
	position_y = temp_y;
}


// when robot have taken damage then decrease the hitpoints to until get 0 

void Robot::takeDamage(int damage){
	hitpoints -= damage;

	if (hitpoints < 0){
		hitpoints = 0;
	}
}

//Getter

int Robot::getStrength() const{
	return strength;
}

int Robot::getHitpoints() const{
	return hitpoints;
}
string Robot::getName()const{
	return name;
}

bool Robot::get_selected()const{
	return selected;
}

int Robot::getDamage(){

	int damage;

	damage = (rand() %strength) + 1;
	
	return damage;
}

int Robot::get_total_number()const{
	return num_total_robot;
}

int Robot::get_X() const{
	return position_x;
}
int Robot::get_Y() const{
	return position_y;
}