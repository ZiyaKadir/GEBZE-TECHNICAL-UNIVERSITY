#include "bulldozer.hpp"

bulldozer::bulldozer() : Robot(1,100,100,"bulldozer")
{
	num_bulldozer ++;

	num_of_robot = num_bulldozer;
}

bulldozer::bulldozer(const bulldozer& other) : Robot(other) {}

bulldozer::~bulldozer() {}



// get function
string bulldozer::getType()const
{
	return name;
}

int bulldozer::get_num()const{
	return num_bulldozer;
}

int bulldozer::get_robot_num() const{
	return num_of_robot;
}

