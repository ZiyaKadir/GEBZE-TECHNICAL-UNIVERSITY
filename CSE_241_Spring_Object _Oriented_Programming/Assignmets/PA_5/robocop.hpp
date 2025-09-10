#ifndef ROBOCOP_HPP
#define ROBOCOP_HPP

#include "humanic.hpp"

const int INITIAL_robocop = 5;

class robocop : public humanic {
	public:

		robocop();
		robocop(const robocop& other);
		virtual ~robocop();

		//get functions
		string getType()const override;
		int get_num()const override;
        int get_robot_num() const override;
		
		static int num_robocop;
	private:
		int num_of_robot;
};

#endif // ROBOCOP_HPP
