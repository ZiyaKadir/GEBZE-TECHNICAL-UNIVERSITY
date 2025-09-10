#include "War.hpp"

#include <iostream>

using namespace std;

// colored function for following robot moved easily
void orange(){
    cout << "\033[0;33m";
}

void green(){
    cout << "\033[0;32m";
}

void red(){
    cout << "\033[0;31m";
}

void blue(){
    cout << "\033[0;34m";
}

void reset(){
    cout << "\033[0m";
}

War::War() {

    m_map = new Robot**[WORLDSIZE];

    for (int i = 0; i < WORLDSIZE; i++) {
        m_map[i] = new Robot*[WORLDSIZE];
        for (int j = 0; j < WORLDSIZE; j++) {
            m_map[i][j] = nullptr;
        }
    }
}

War::~War() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            delete m_map[i][j];
        }
        delete[] m_map[i];
    }
    delete[] m_map;
}
// adding robot
void War::addRobot(Robot* robot, int x, int y) {

    if (x < 0 || x >= WORLDSIZE || y < 0 || y >= WORLDSIZE) {
        // cout << "Robot position out of range" << endl;
        return;
    }
    if (m_map[x][y] != nullptr){
        // "This place is full";
    }

    robot->set_X(x);
    robot->set_Y(y);
    m_map[x][y] = robot;
    
}
// removing robot
void War::removeRobot(int x, int y) {

    if (x < 0 || x >= WORLDSIZE || y < 0 || y >= WORLDSIZE) {
        // cout << "Robot position out of range" << endl;
        return;
    }

    if (m_map[x][y] == nullptr) {
        // cout << "No robot at specified position" << endl;
        return;
    }


    m_map[x][y] = nullptr;
}


//return sepesific location
Robot* War::getRobotAt(int x, int y) {

    if (x < 0 || x >= WORLDSIZE || y < 0 || y >= WORLDSIZE) {
        // cout << "Robot position out of range" << endl;
        return nullptr;
    }

    return m_map[x][y];
}

//control location is emphty or not
bool War::isLocationEmpty(int x, int y) {

    if (x < 0 || x >= WORLDSIZE || y < 0 || y >= WORLDSIZE) {
        //  cout << "Invalid location!" << endl;
        return false;
    }

    if (m_map[x][y] == nullptr) {
        // cout << "Location is empty." << endl;
        return true;
    }
    else {
        // cout << "Location is not empty." << endl;
        return false;
    }
}



void War::SimulateOneStep() {

    //select robot
    Robot *selected = select_robot();

    //selected robot location and type
    // cout << selected->getType() << " ";
    // cout << selected->get_X() << " " ;
    // cout << selected->get_Y() << " " << endl;

    int previous_x = selected->get_X();
    int previous_y = selected->get_Y();

    int next_x = selected->get_X();
    int next_y = selected->get_Y();

    int direction; 

    bool bounds = true;

    //if bounds is false keep going until the get correct boundiries
    do {

        bounds = true;

        //choose direction randomly
        direction = rand() % 4 + 1;

    //chosing direction
        //south 
        if (direction == 1) {
            next_x++;
        } 
        //east
        else if (direction == 2) {
            next_y++;
        } 
        //north
        else if (direction == 3) {
            next_x--;
        } 
        // west
        else if (direction == 4) {
            next_y--;
        }
        // control the boundries
        if (next_x < 0 || next_x >= WORLDSIZE || next_y < 0 || next_y >= WORLDSIZE) {
            next_x = previous_x;
            next_y = previous_y;
            bounds = false;
        }
        //control the direction
        if (direction < 1 || direction > 4){
            bounds = false;
        }

    } while (bounds == false);

        selected->set_X(next_x);
        selected->set_Y(next_y);

    if (m_map[next_x][next_y] == nullptr) {
        // removing previous location
        removeRobot(previous_x,previous_y);
        //adding next location
        addRobot(selected,next_x,next_y);

    }
    else{
        // removing previous location
        removeRobot(previous_x,previous_y);
        // adding next location
        addRobot(battle(selected,m_map[next_x][next_y]),next_x,next_y);
    }

}

Robot* War::battle(Robot* first, Robot* second) {


    if (first == nullptr || second == nullptr) {
        // cout << "Can not battle because location are nullptr" << endl;
    }

    int damage;

    while(true){
        int i =0; 
       
       // using this while for roomba 
       // if roomba turns 2 times
       // if not turns one time
        while(i < 2){

            // if robot is not roomba then i ++ because the roomba only have chance to attack two times
            if (first->getType() != "roomba") {i++;}

            //printing mesage
            cout << first->getType() << "_" << first->get_robot_num() << "(" << first->getHitpoints()<< ")" << " hits " 
            << second->getType() << "_"<<  second->get_robot_num() << "(" << second->getHitpoints() <<")";

            damage = first->getDamage();
            second->takeDamage(damage);

            cout << " with " << damage << endl;

            cout << "The new hitpoints of " << second->getType() << "_" << second->get_robot_num() << " "<< second->getHitpoints() << endl;

            //undraw(2,5000);
            
            if(second->getHitpoints() <= 0 ){
                return first;
            }
            i++;
        }

        i = 0;

       // using this while for roomba 
       // if roomba turns 2 times
       // if not turns one time
        while(i < 2){

            if (second->getType() != "roomba") {i++;}

            // printing mesage
            cout << second->getType() << "_" << second->get_robot_num() << "(" << second->getHitpoints()<< ")" << " hits " 
            << first->getType() << "_"<<  first->get_robot_num() << "(" << first->getHitpoints() <<")";

            damage = second->getDamage();
            first->takeDamage(damage);

            cout << " with " << damage << endl;

            cout << "The new hitpoints of " << first->getType() << "_" << first->get_robot_num() << " " << first->getHitpoints() << endl;
            

            //undraw(2,5000);

            if(first->getHitpoints() <= 0 ){
                return second;
            }
            i++;
        }

    }


}

Robot* War::select_robot(){

    bool is_selected = false;

    int x,y;

    int number = 0;

    for(int i=0; i < WORLDSIZE; i++){
        for(int k=0; k < WORLDSIZE; k++){
            if (m_map[i][k] != nullptr){
                    number++;
            }
        }
    }
    if(number == 1){
        //robot number is 1 than you finish the program
        cout << "The game is over" << endl;
        exit(1);
    }

while(true){
// control the is there selected robot and selected flag is removing
    for(int i=0; i < WORLDSIZE; i++){
        for(int k=0; k < WORLDSIZE; k++){
            if (m_map[i][k] != nullptr && m_map[i][k]->get_selected() == true){
                is_selected = true; 
                m_map[i][k]->set_selected(false);
                x = i;
                y = k;
            }
        }
    }

// select the robot 
    for(int i=0; i < WORLDSIZE; i++){
        for(int k=0; k < WORLDSIZE; k++){
            if (m_map[i][k] != nullptr){

                // control for not choosing previous robot
                if (is_selected == true){
                    //choosing robot
                    if(m_map[i][k]->get_selected() == false && !(x == i && y == k)){
                        m_map[i][k]->set_selected(true); 
                        return m_map[i][k];
                    }
                }
                else{
                    // choosing robot
                    if(m_map[i][k]->get_selected() == false){
                        m_map[i][k]->set_selected(true); 
                        return m_map[i][k];
                    }
                }
            }
        }
    }
}

}

// printng map with different color by using color functions which are global
void War::print_map(){

    cout << "Printing map" << endl << endl;
    

    for(int i=0; i < WORLDSIZE; i++){
        for(int k = 0; k < WORLDSIZE; k++){

            reset();
            if(m_map[i][k] == nullptr){
                cout << "=";
            }
            else if(m_map[i][k]->getType() == "bulldozer"){
                orange();
                cout << "B";
            //this commont line maybe ypu want to see selected robot 
            // if (m_map[i][k]->get_selected() == true){
            //         cout << "|";
            //     }
            }
            else if(m_map[i][k]->getType() == "roomba"){
                green();
 
               cout << "R";
                // if (m_map[i][k]->get_selected() == true){
                //     cout << "|";
                // }
            }
            else if(m_map[i][k]->getType() == "optimusprime"){
                red();
                cout << "O";
                // if (m_map[i][k]->get_selected() == true){
                //     cout << "|";
                // }
            }
            else if(m_map[i][k]->getType() == "robocop"){
                blue();
                cout << "R";
                // if (m_map[i][k]->get_selected() == true){
                //     cout << "|";
                // }
            }

        }
        reset();
        cout << endl;
    }
    
}

// if you want to see robot's movement this prevent printing multiple tables in terminal
void War::undraw(int h, int latency){

this_thread::sleep_for(chrono::milliseconds(latency));


    cout << "\033" << "[" << h + 2 << "A";
	cout << "\033[G";
	cout << "\033[J";

}

