#include "humanic.hpp"

humanic::humanic()
{

}
humanic::humanic(int newType, int newStrength, int newHit, string name): Robot(newType,newStrength,newHit,name)
{
	
}

humanic::humanic(const humanic& other) : Robot(other) {

}

humanic::~humanic() {

}

int humanic::getDamage(){
	
	int damage = Robot::getDamage();

	int probablity = rand() % 100;

	if (probablity < 10){
		damage += 50;
	}

	return damage;
}

