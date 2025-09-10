// Display 10.12, Demonstration Program for PFArrayD
// The main program has not been changed, but the
// testPFArrayD() function has been changed by adding
// try-catch blocks.
// Program to demonstrate the class PFArrayD.

#include <iostream>
#include "PFARRAYD.hpp"

using namespace std;

void testPFArrayD();

int main()
{
    cout << "This program tests the class PFArrayD.\n";
    char ans;

    do
    {
    try{
        testPFArrayD();
	}
	catch(OutOfRange error){
		cout << "somethink is going weird" << endl;
        cout <<"\nmessage " << error.getMessage() << " " << error.getIndex()<< endl;
        exit(0);
	}
        cout << "Test again? (y/n) ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    
    return 0;
}


void testPFArrayD()
{
    int cap;
    cout << "Enter capacity of this super array: ";
    cin >> cap;
    PFArrayD temp(cap);
    cout << "Enter up to " << cap << " non-negative numbers.\n";
    cout << "Place a negative number at the end.\n";
    double next;
    cin >> next;
    
    while (next >= 0 && !temp.full())
    {
        temp.addElement(next);
        cin >> next;
    }
    
    cout << "You entered the following " << temp.getNumberUsed() << " numbers:\n";
    int index;
    int count = temp.getNumberUsed();
    
    for (index = 0; index < count; index++)
    {
        cout << temp[index] << " ";
        cout << endl;
    }
    
    cout << "(plus a sentinel value.)\n";
    
    // Test index out of range
    // cout << temp[-1]; // 2 * count];
    
    // Test insert beyond declared size
    temp.addElement(99999);
}
