#ifndef BULLDOZER_HPP
#define BULLDOZER_HPP

#include "Robot.hpp"

const int INITIAL_bulldozer = 5;

class bulldozer : public Robot {
    
    public:

        bulldozer();
        
        bulldozer(const bulldozer& other);
        ~bulldozer();
        
        //get function
        
        string getType()const override;
        int get_num() const override;
        int get_robot_num() const override;

        static int num_bulldozer;
    
    private:
        int num_of_robot;
};

#endif // BULLDOZER_HPP
