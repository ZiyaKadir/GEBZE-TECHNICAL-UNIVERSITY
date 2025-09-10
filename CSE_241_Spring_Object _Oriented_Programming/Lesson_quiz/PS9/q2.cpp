#include <iostream>

using namespace std;

void recursiveFunction(int Depth, int Max_value) {

    if (Depth == Max_value) {
        throw Depth;
    }
    
    if (Depth < 10) {
        recursiveFunction(Depth + 1, Max_value);
    }
}

int main() {


    int Max_value;
    
    cout << "Please enter the max value (0-10)" << endl;
    cin >> Max_value;
    
    try {
        recursiveFunction(0, Max_value);
    } catch (int depth) {
        cout << "you exceed depth" << depth << endl;
    }
    
    return 0;
}
