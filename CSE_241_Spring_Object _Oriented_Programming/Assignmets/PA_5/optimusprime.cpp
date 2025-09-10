#include "optimusprime.hpp"

optimusprime::optimusprime() : humanic(3,100,100, "optimusprime"){
	num_optimus ++;
	num_of_robot = num_optimus;
}

optimusprime::optimusprime(const optimusprime& other) : humanic(other) {}

optimusprime::~optimusprime() {}


// getter function
string optimusprime::getType()const
{
	return name;
}

int optimusprime::get_num()const{
	return num_optimus;
}

int optimusprime::getDamage(){

	int damage =humanic::getDamage();

	int probablity = rand() % 100;

	if (probablity < 15){
		damage *= 2;
	}

	return damage;
}

int optimusprime::get_robot_num() const{
	return num_of_robot;
}
