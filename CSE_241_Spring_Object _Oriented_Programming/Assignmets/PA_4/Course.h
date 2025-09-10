#ifndef _COURSE_
#define _COURSE_

#include <iostream>
#include <string>

using namespace std;

namespace PA4{
  
  class Student;
}

#include "Student.h"

namespace PA4 {
  
    class Course {
      
      private:
        string name;
        string code;
        Student* Students;
        
        int num_student;

      public:
        Course();
        Course(string assign_name, string assign_code);
        Course& operator=(const Course& other);
        Course(const Course& copy);
        ~Course();


        // getter function
        string get_name()const;
        string get_code()const;
        int get_num()const;

        const Student& operator[](int index)const;

        // setter function
        void set_name(string assign_name);
        void set_code(string assign_code);

        Student& operator[](int index);

        void add_Student(Student& adding);
        void del_Student(Student& adding);

      };
}

#endif
