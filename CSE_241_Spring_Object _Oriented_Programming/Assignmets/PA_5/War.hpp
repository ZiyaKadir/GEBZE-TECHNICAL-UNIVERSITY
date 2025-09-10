#ifndef WAR_HPP
#define WAR_HPP

#include "Robot.hpp"
#include<chrono>
#include<thread>

const int WORLDSIZE = 10;

class War {
public:
    War();
    ~War();

    //adding robot on the map
    void addRobot(Robot* robot, int x, int y);
    //removing robot on the map
    void removeRobot(int x, int y);
    //control location is full or not
	bool isLocationEmpty(int x, int y);
    //print the map
    void print_map();
    // battle the robot return the winning
    Robot* battle(Robot* first, Robot* second);
    // select robot from the map
    Robot* select_robot();
    
    // game simulation for one move
    void SimulateOneStep();
    //return spesific location in the map as a robot
    Robot* getRobotAt(int x, int y);
    //undraw function with usung ASCII escape code
    void undraw(int h, int latency);

private:
    Robot*** m_map;

};

#endif
