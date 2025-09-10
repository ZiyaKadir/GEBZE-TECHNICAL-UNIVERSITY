#include "Student.h"

#include "Course.h"

using namespace std;
using namespace PA4;

// Big tree constructors implementation
Student::Student(){
	name = "";
	ID = "";
	Courses = nullptr;
	num_course = 0;
}

Student::Student(const Student& copy){

	name = copy.get_name();
	ID = copy.get_ID();
}
Student::Student(string assign_name, string assign_ID){

	name = assign_name;
	ID = assign_ID;
}
Student::~Student(){
	delete[] Courses;
}

// getter function implementation

string Student::get_ID()const{
	return ID;
}

string Student::get_name()const{
	return name;
}

int Student::get_num()const{
	return num_course;
}

Course& Student::operator[](int index){
	return Courses[index];
}




// setter function implementation

void Student::set_name(const string assign_name){
	name = assign_name;
}

void Student::set_ID(const string assign_ID){
	ID = assign_ID;
}

const Course& Student::operator[](int index)const{
	return Courses[index];
}


// addcourse to student implemantation

void Student::add_Course(Course& Lesson){
    Course *temp = new Course[num_course + 1];

    for (int i=0; i<num_course; i++){
        temp[i] = Courses[i];
    }

    temp[num_course] = Lesson;

    delete[] Courses;

    Courses = temp;

    num_course++;
}


void Student::del_Course(Course& Lesson){
	
	Course *temp = new Course[num_course - 1];

	int control;

	for(int i=0; i < num_course; i++){
		if((Lesson.get_code() == Courses[i].get_code() )  && 
			(Courses[i].get_name() == Lesson.get_name())){
				control = i;
				break;
			}
		temp[i] = Courses[i];
	}

	for(int i=control; i < num_course -1; i++){
		temp[i] = Courses[i-1];
	} 

	delete[] Courses;

	Courses = temp;
	
	num_course --;


}

Student& Student::operator=(const Student& other) {
        if (this == &other) {
            return *this; // Handle self-assignment
        }
        name = other.name;
        ID = other.ID;
        num_course = other.num_course;

        return *this;
    }


bool operator==(const Course& first, const Course& second){
	
	if(first.get_code() != second.get_code()){
		return false;
	}
	
	if(first.get_name() != second.get_name()){
		return false;
	}

	return true;
}
