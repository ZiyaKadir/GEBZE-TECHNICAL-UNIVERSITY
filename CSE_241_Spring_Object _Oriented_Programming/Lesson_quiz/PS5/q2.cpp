#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Student {
public:
    Student();
    Student(const Student& copy);
    ~Student();

    Student& operator=(const Student& assign);

    void InputData();
    void OutputData() const;
    void ResetClasses();

private:
    string name;
    int numClasses;
    string* classList;
};

int main() {
    Student s1, s2;
    s1.InputData();
    // Input data for student 1
    cout << "Student 1's data:" << endl;
    s1.OutputData();
    // Output data for student 1
    cout << endl;

    s2 = s1;
    cout << "Student 2's data after assignment from student 1:" << endl;
    s2.OutputData();
    // Should output same data as for student 1

    s1.ResetClasses();
    cout << "Student 1's data after reset:" << endl;
    s1.OutputData();
    // Should have no classes

    cout << "Student 2's data, should still have original classes:" << endl;
    s2.OutputData();
    // Should still have original classes

    return 0;
}

Student::Student() {
    name = "";
    numClasses = 0;
    classList = nullptr;
}

Student::Student(const Student& copy) {
    name = copy.name;
    numClasses = copy.numClasses;
    classList = new string[numClasses];
    for (int i = 0; i < numClasses; i++) {
        classList[i] = copy.classList[i];
    }
}

Student::~Student() {
    delete[] classList;
}

Student& Student::operator=(const Student& assign) {
    if (this != &assign) {
        delete[] classList;
        name = assign.name;
        numClasses = assign.numClasses;
        classList = new string[numClasses];
        for (int i = 0; i < numClasses; i++) {
            classList[i] = assign.classList[i];
        }
    }
    return *this;
}

void Student::InputData() {
    cout << "Please enter student name: " << endl;
    cin >> name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter number of classes: " << endl;
    cin >> numClasses;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    classList = new string[numClasses];
    for (int i = 0; i < numClasses; i++) {
        cout << "Enter name of class " << i+1 << ": " << endl;
        cin >> classList[i];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Student::OutputData() const {
    cout << "Name: " << name << endl;
    cout << "Number of classes: " << numClasses << endl;
    cout << "Class list: " << endl;
    for (int i = 0; i < numClasses; i++) {
        cout << classList[i] << endl;
    }
}

void Student::ResetClasses() {
    numClasses = 0;
    delete[] classList;
    classList = nullptr;
}
