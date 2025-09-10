#ifndef _STUDENT_

#define _STUDENT_

#include <iostream>
#include <string>

using namespace std;


namespace PA4{
	class Course;
}

#include "Course.h"

namespace PA4 {

	class Student {

	private:

		string name;
		string ID;
		Course* Courses;
		int num_course;

	public:
		// Big tree constructor
		Student();
		Student(const Student& copy);
		Student& operator=(const Student& other);
		Student(string assign_name, string assign_ID);
		~Student();
		
		//getter
		string get_name()const;
		string get_ID()const;
		int get_num()const;

		const Course& operator[](int index)const;

		
		//setter function
		void set_name(const string assign_name);
		void set_ID(const string assign_ID);

		Course& operator[](int index);

		// add course to student
		void add_Course(Course& Lesson);

		// delete course from student
		void del_Course(Course& Lesson);


		friend bool operator==(const Course& first, const Course& second);
	};
}

#endif
