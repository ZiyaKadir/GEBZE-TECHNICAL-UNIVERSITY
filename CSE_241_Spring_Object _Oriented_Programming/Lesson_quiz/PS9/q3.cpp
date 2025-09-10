#include <iostream>
#include "STACK.cpp"

using namespace std;

int main()
{
    try {
        Stack<int> stack;
        stack.push(5);
        stack.push(10);
        stack.pop();
        stack.pop(); 

        cout << "Popped value: " << stack.pop() << endl;
    }
    catch (const PopEmptyStackException& e) {
		cout << "Cannot be pop because stack is emphty" << endl;
    }

    return 0;
}
