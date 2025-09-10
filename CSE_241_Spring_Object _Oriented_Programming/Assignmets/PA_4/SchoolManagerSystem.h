#ifndef _SCHOOLMANAGERSYSTEM_

#define _SCHOOLMANAGERSYSTEM_


namespace PA4{
	class Course;
	class Student;
}

#include "Course.h"
#include "Student.h"

namespace PA4{
	class SchoolManagerSystem{

		private:

		Student* Students;
		int num_student;
		Course*	Courses;
		int num_course;
		

		public:

		SchoolManagerSystem();
		SchoolManagerSystem(const SchoolManagerSystem& copy);
		~SchoolManagerSystem();
		
		int Main_Menu();
		int Student_Menu();
		int Course_Menu();
		int Select_Menu_Student(int index);
		int Select_Menu_Course(int index);



		void add_student(); // adding student
		void add_course();	// adding course
		int sel_student(); //select student
		int sel_course(); // select course
		
		void delete_student(int index);
		void delete_course(int index);

		void add_course_to_student(int index);
		void drop_course_to_student(int index);



		void list_all_student();
		void list_all_course();

		void list_students(Course& total);
	};
	
}


#endif