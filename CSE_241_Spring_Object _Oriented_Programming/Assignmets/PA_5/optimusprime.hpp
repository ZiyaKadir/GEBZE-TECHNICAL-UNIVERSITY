#ifndef OPTIMUSPRIME_HPP
#define OPTIMUSPRIME_HPP

#include "humanic.hpp"

const int INITIAL_optimusprime = 5;

class optimusprime : public humanic {
    
    public:
        optimusprime();
        optimusprime(const optimusprime& other);
        virtual ~optimusprime();

        // get functions
        string getType()const override;
        int get_num()const override;
        int get_robot_num() const override;
        int getDamage() override;
        
        static int num_optimus;
    private:
        int num_of_robot;
};

#endif // OPTIMUSPRIME_HPP
