#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>



using namespace std;



class Robot {
    public:
        Robot();
        Robot(const Robot& other);
        Robot(int newType, int newStrength, int newHit, string new_name);
        virtual ~Robot();

        virtual string getType() const = 0;

        virtual int get_num() const = 0;
        virtual int get_robot_num() const = 0;
        virtual int getDamage();

        int get_total_number()const;

    
        int getStrength() const;
        int getHitpoints() const;
        string getName() const;
        bool get_selected()const;
        int get_X() const;
        int get_Y() const;

        void set_type(int n_type);
        void set_strength(int n_strength);
        void set_hitpoints(int n_hitpoints);
        void set_name(string n_name);
        void set_selected(bool choose);
        void set_X(int temp_x);
        void set_Y(int temp_y);		// if location emphty add else continue



        void takeDamage(int damage);

        static int num_total_robot;

    protected:

    int type;
    int strength;
    int hitpoints;
    string name;
    bool selected;

    int position_x;
    int position_y;
};

#endif // ROBOT_HPP
