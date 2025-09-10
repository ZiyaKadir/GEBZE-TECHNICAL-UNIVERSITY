#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int dice();

int humanTurn(int humanTotalScore);

int computerTurn(int computerTotalScore);

int main(){

// QUESTION 2

// this line provide that random function generate different sequence for each run time

	srand(time(0));

	size_t c_score = 0, p_score = 0; // computer and player score

	while(c_score <= 100 && p_score <= 100){
		cout << "Player's Turn" << endl;
		p_score = humanTurn(p_score);

		cout << "Computer's Turn"<< endl ;
		c_score = computerTurn(c_score);

		cout << "Player's Score = " << p_score << "Computer's Score = " << c_score << endl;
	}

	if(p_score >= 100 && c_score < 100){
		cout << "Player wins against to computer" << endl;
	}
	else if(c_score >=100 && p_score < 100){
		cout << "Computer wins against to Player" << endl;
	}
	else if(p_score >= 100 && c_score >= 100){
		cout << "There is no winner two player exceed 100 points"<< endl;
	}


	return 0;
}

int humanTurn(int humanTotalScore){

	int num_dice; // number dice
	bool check= true; // control for the infinite loop
	char control; // to control player press button r or h 

// keep the first score if Player's dice is 1
	int temp = humanTotalScore;

	while(check == true){
		num_dice = dice();
		cout << "Players dice "<< num_dice <<endl;

// if dice is 1, return humanTotalScore which is before this turn
		if(num_dice == 1){
			check = false;
			return temp;
		}
// if dice 2-6, the Player's choose option and contunie
		else if(num_dice >=2 && num_dice  <= 6){
			// this loop for controlling correct char which Player press
			do{

			cout << "Please press r for ROLL AGAIN or h for HOLD"<< endl;
			cin >> control;

			if(!(control == 'r' || control == 'h' || control == 'R' || control == 'H')){
				cout << "Please enter the correct letter end press" << endl;
			}

			}while(!(control == 'r' || control == 'h' || control == 'R' || control == 'H'));

			if(control == 'r' || control == 'R'){
				humanTotalScore += num_dice;
				continue;;
			}
			else if(control == 'h' || control == 'H'){
				humanTotalScore += num_dice;
				break;
			}
		}
	}
	
	return humanTotalScore;
}

int computerTurn(int computerTotalScore){

	int num_dice; // dice number
	bool check= true; // control for the infinite loop

// keep the first score if Computer's dice is 1
	int temp = computerTotalScore;

	cout << "Computers dice =";
	while(check == true){
		num_dice = dice();
		cout << num_dice << " ";
// if dice is 1, return humanTotalScore which is before this turn
		if(num_dice == 1){
			check = false;
			cout << '\n';
			return temp;
		}
		else if(num_dice >=2 && num_dice  <= 6){

// Controling Computer's Score to exceed 20 or not 
			if(computerTotalScore - temp < 20){
				computerTotalScore += num_dice;
				continue;;
			}
			else {
				computerTotalScore += num_dice;
				break;
			}
		}
	}
	cout << '\n';
	return computerTotalScore;

}

int dice(){

	int result = (rand() % 6) +1;
	return result;
}