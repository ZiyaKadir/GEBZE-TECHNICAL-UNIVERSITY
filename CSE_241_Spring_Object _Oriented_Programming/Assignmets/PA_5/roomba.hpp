#ifndef ROOMBA_HPP
#define ROOMBA_HPP

#include "Robot.hpp"

const int INITIAL_roomba = 5;

class roomba : public Robot {
    public:
        roomba();
        roomba(const roomba& other);
        ~roomba();

    // get function
        string getType()const override;
        int get_num()const override;
        int get_robot_num() const override;

        static int num_roomba;
    private:
        int num_of_robot;       

};
#endif // ROOMBA_HPP
