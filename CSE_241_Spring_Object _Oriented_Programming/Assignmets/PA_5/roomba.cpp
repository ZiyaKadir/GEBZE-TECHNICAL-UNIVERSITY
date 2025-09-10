#include "roomba.hpp"

roomba::roomba() : Robot(2,3, 10, "roomba") {
	num_roomba ++;
	num_of_robot = num_roomba;
}

roomba::roomba(const roomba& other) : Robot(other) {}

roomba::~roomba() {}


// get function
string roomba::getType()const{
	return name;
}

int roomba::get_num()const{
	return num_roomba;
}

int roomba::get_robot_num() const {
	return num_of_robot;
}

