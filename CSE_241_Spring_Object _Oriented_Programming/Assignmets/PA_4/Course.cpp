#include "Student.h"
#include "Course.h"

using namespace std;
using namespace PA4;

// Big tree constructer
Course::Course(){

	num_student =0;
}

Course::Course(const Course& copy){

}
Course::Course(string assign_name, string assign_code){
	name = assign_name;
	code = assign_code;
	num_student ++;
}
Course::~Course(){
	delete[] Students;
}

// getter function implementation

string Course::get_name()const{
	return name;
}

string Course::get_code()const{
	return code;
}

int Course::get_num()const{
	return num_student;
}

const Student& Course::operator[](int index)const{
	return Students[index];
}

//setter function implementation

void Course::set_name(string assign_name){
	name = assign_name;
}

void  Course::set_code(string assign_code){
	code = assign_code;
}

Student& Course::operator[](int index){
	return Students[index];
}


Course& Course::operator=(const Course& other) {
        if (this == &other) {
            return *this; // Handle self-assignment
        }
        name = other.name;
        code = other.code;
        num_student = other.num_student;

        return *this;
    }

void Course::add_Student(Student& adding){

	Student *temp = new Student[num_student + 1];

	for (int i=0; i < num_student; i++){
		temp[i] = Students[i];
	}

	temp[num_student] = adding;

	delete[] Students;

	Students = temp;

	num_student ++;

}

void Course::del_Student(Student& Lesson){
	
	Student *temp = new Student[num_student - 1];

	int control;

	for(int i=0; i < num_student; i++){
		if((Lesson.get_ID() == Students[i].get_ID() )  && 
			(Students[i].get_name() == Lesson.get_name())){
				control = i;
				break;
			}
		temp[i] = Students[i];
	}

	for(int i=control; i < num_student -1; i++){
		temp[i] = Students[i-1];
	} 

	delete[] Students;

	Students = temp;

	num_student --;

}