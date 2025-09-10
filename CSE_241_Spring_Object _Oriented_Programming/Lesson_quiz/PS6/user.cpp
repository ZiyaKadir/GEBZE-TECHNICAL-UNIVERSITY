#include <iostream>
#include "user.h"

using namespace std;

namespace{

		
	bool isValid() {
		if (username.length() != 8) {
			cout << "Username must be exactly 8 characters long." << endl;
			return false;
		}
		for (char c : username) {
			if (!isalpha(c)) {
				cout << "Username must only contain letters." << endl;
				return false;
			}
		}
		return true;
	}	
}

namespace Authenticate{
    void inputUserName() {
        do {
            cout << "Enter your username (8 letters only)" << endl;
            cin >> username;
        } while (!isValid());
    }
    
    string getUserName() {
        return username;
    }
}
