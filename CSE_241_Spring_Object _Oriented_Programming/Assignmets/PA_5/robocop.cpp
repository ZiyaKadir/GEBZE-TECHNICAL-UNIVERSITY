#include "robocop.hpp"

robocop::robocop(): humanic(4,30,40,"robocop")
{
	num_robocop ++;
	num_of_robot = num_robocop;
}

robocop::robocop(const robocop& other) : humanic(other) 
{

}

robocop::~robocop()
{

}
// getter
string robocop::getType()const
{
	return name;
}

int robocop::get_num()const{
	return num_robocop;
}
int robocop::get_robot_num() const {
	return num_of_robot;
}

