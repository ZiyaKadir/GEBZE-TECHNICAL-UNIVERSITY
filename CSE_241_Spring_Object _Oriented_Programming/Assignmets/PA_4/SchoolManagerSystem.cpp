#include "SchoolManagerSystem.h"


using namespace std;
using namespace PA4;


SchoolManagerSystem::SchoolManagerSystem(){

	num_student = 0;
	Students = nullptr;
	num_course = 0;
	Courses = nullptr;

}

SchoolManagerSystem::SchoolManagerSystem(const SchoolManagerSystem& copy){

}
SchoolManagerSystem::~SchoolManagerSystem(){
	delete[] Courses;
	delete[] Students;
}

int SchoolManagerSystem::Main_Menu(){

	int selection;

	cout << "Main_menu" << endl;
	cout << "0 exit" << endl;
	cout << "1 student" << endl;
	cout << "2 course" << endl;
	cout << "3 list_all_students" << endl;
	cout << "4 list_all_courses" << endl;
	cout << ">> ";
	
	cin >> selection;

	if(selection == 0){
		return 0;
	}
	else if(selection == 1){
		return Student_Menu();
	}
	else if(selection == 2){
		return Course_Menu();
	}
	else if(selection == 3){
		
		list_all_student();

		return Main_Menu();
	}
	else if(selection == 4){
		
		list_all_course();

		return Main_Menu();
	}

	return 0;
}

int SchoolManagerSystem::Student_Menu(){

	int selection;

	cout << "0 up" << endl;
	cout << "1 add_student" << endl;
	cout << "2 select_student" << endl;
	cout << ">> ";

	int index;

	cin >> selection;

	if (selection == 0){
		return Main_Menu();
	}
	else if(selection == 1){
		add_student();
		return Student_Menu();
	}
	else if(selection == 2){
		index = sel_student();
		Select_Menu_Student(index);
	}


	return 0;
}

int SchoolManagerSystem::Course_Menu(){

	int selection;
	int index;

	cout << "0 up" << endl;
	cout << "1 add_course" << endl;
	cout << "2 select_course" << endl;
	cout << ">> ";

	cin >> selection;

	if (selection == 0){
		return Main_Menu();
	}
	else if(selection == 1){
		add_course();
		return Course_Menu();
	}
	else if(selection == 2){
		index = sel_course();
		list_students(Courses[index]);
		return Course_Menu();
	}

	return 0;

}

void SchoolManagerSystem::add_student(){

	Student *temp = new Student[num_student + 1];
	string  sub_string;
	string  tot_name;
	string ID;

	for(int i=0; i < num_student; i++){

		temp[i] = Students[i];
	}

	cout << ">> ";
	
	do{
		cin >> sub_string;

		if(sub_string[0] >= '0' && sub_string[0] <= '9'){
			ID += sub_string ;
			break;
		}
		tot_name += sub_string + " ";
	}while(cin.peek() != 10);

	temp[num_student].set_name(tot_name);
	temp[num_student].set_ID(ID);

	delete[] Students;

	Students = temp;

	num_student ++;
}

void SchoolManagerSystem::add_course(){

	Course *temp = new Course[num_course + 1];
	string sub_string;
	string tot_name;
	string code;

	for(int i=0; i < num_course; i++){
		temp[i] = Courses[i];
	}	

	cout << ">>";

	cin >> sub_string;
	code += sub_string;
	
	do{
		cin >> sub_string;
		tot_name += sub_string;
	}while(cin.peek() != 10);

	temp[num_course].set_name(tot_name);
	temp[num_course].set_code(code);

	delete[] Courses;

	Courses = temp;

	num_course ++;
}


int SchoolManagerSystem::sel_student(){

	string sub_string;
	string tot_string;
	string ID;

	cout << ">> ";
	
	do{
	cin >> sub_string;
		if(sub_string[0] >= '0' && sub_string[0] <= '9'){
			ID += sub_string;
			break;
		}
	tot_string += sub_string + " ";

	}while(cin.peek() != 10);

	for(int i = 0; i < num_student; i++){

		
		if(ID == Students[i].get_ID() && tot_string == Students[i].get_name()){
			
			
			return i;

		}
	}

	return 0;
}

int SchoolManagerSystem::sel_course(){

	string sub_string;
	string tot_string;
	string code;

	cout << ">> ";
	
	cin >> code;
	do{
	cin >> sub_string;

	tot_string += sub_string + " ";

	}while(cin.peek() != 10);

	for(int i = 0; i < num_course; i++){

		if(code == Courses[i].get_code() && tot_string == Courses[i].get_name()){
			return i;
		}
	}

	return 0;

}


int SchoolManagerSystem::Select_Menu_Student(int index){

	int selection;

	cout << "0 up" << endl;
	cout << "1 delete_student" << endl;
	cout << "3 add_selected_student_to_a_course" << endl;
	cout << "4 drop_selected_student_from_a_course" << endl;

	cout << ">>";

	cin >> selection;

	if(selection == 0){
		return Student_Menu();
	}
	else if(selection == 1){

		delete_student(index);
		return Select_Menu_Student(index);
	}
	else if(selection == 3){
		add_course_to_student(index);
		return Select_Menu_Student(index);
	}
	else if(selection == 4){
		drop_course_to_student(index);
		return Select_Menu_Student(index);
	}

	return 0;
}

int SchoolManagerSystem::Select_Menu_Course(int index){

	int selection;

	cout << "0 up" << endl;
	cout << "1 delete_course" << endl;
	cout << "2 list_students_registered_to_the_selected_course" << endl;

	if (selection == 0){
		return Course_Menu();
	}
	else if(selection == 1){
		delete_course(index);
		return Select_Menu_Course(index);
	}
	else if(selection == 2){
		list_students(Courses[index]);
	}

	return 0;
}


void SchoolManagerSystem::delete_student(int index){

	Student *temp = new Student[num_student -1];

	for(int i=0; i < num_student - 1; i++){

		if(i < index){
			temp[i] = Students[i];
		}
		else{
			temp[i] = Students[i + 1];
		}
	}

	delete[] Students;

	Students = temp;

	num_student --;


}

void SchoolManagerSystem::delete_course(int index){

	Course *temp = new Course[num_course - 1];

	for (int i = 0; i < num_course - 1; i++){

		if(i < index){
			temp[i] = Courses[i];
		}
		else{
			temp[i] = Courses[i + 1];
		}
	}

	delete[] Courses;

	Courses = temp;
}


void SchoolManagerSystem::add_course_to_student(int index){

	int counter = 1;
	bool control = true;

	int selection;

	for(int i=0; i < num_course; i++){
		
		control = true;

		for (int k = 0; k < Students[index].get_num(); k++){
			control = true;
			if((Students[i][k].get_code() == Courses[i].get_code()) &&
				(Students[i][k].get_name() == Courses[i].get_name())){
				control = false;
			}
		}
		if (control == true){
			cout << i + 1 << Courses[i].get_code() << " " << Courses[i].get_name() << endl;
		}

	}

	cout << ">>";

	cin >> selection;


	Students[index].add_Course(Courses[selection - 1]);

	Courses[selection - 1].add_Student(Students[index]);

}

void SchoolManagerSystem::drop_course_to_student(int index){

	int selection;

	for(int i = 0; i < Students[index].get_num(); i++){
		cout << i + 1 << Students[index][i].get_code() << " " << Students[index][i].get_name() << endl;
	}

	cout << ">>";

	cin >> selection;

	Students[index].del_Course(Students[index][selection - 1]);
	
}

void SchoolManagerSystem::list_students(Course& total){

	for(int i=0; i < total.get_num(); i++){
		cout << i+1 << ". " << total[i].get_name() << " " << total[i].get_ID() << endl;
	}

}

void SchoolManagerSystem::list_all_student(){

	for(int i = 0; i < num_student; i++){
		cout << i << ". Student";
		cout << Students[i].get_name() << " " << Students[i].get_ID() << endl;
	}
}

void SchoolManagerSystem::list_all_course(){
	
	for(int i = 0; i < num_course; i++){
		cout << i << ".Course ";
		cout << Courses[i].get_name() << " " << Courses[i].get_code() << endl;
	}
}
