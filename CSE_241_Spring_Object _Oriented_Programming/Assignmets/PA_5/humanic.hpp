#ifndef HUMANIC_HPP
#define HUMANIC_HPP

#include "Robot.hpp"

class humanic : public Robot {
    public:
        humanic();
        humanic(const humanic& other);
        humanic(int newType, int newStrength, int newHit, string name);
        virtual ~humanic();

        virtual int getDamage();
        
        virtual int get_num()const = 0;

};

#endif // HUMANIC_HPP
