#include <iostream>
#include "password.h"

using namespace std;

namespace{
	
	bool isValid() {
		bool hasNonLetter = false;
		if (password.length() < 8) {
			cout << "Password must be at least 8 characters long." << endl;
			return false;
		}
		for (char c : password) {
			if (!isalpha(c)) {
				hasNonLetter = true;
				break;
			}
		}
		if (!hasNonLetter) {
			cout << "Password must contain at least one non-letter character." << endl;
			return false;
		}
		return true;
	}

}

namespace Authenticate {
    void inputPassword() {
        do {
            cout << "Enter your password (at least 8 characters and at least one non-letter)" << endl;
            cin >> password ;
        } while (!isValid());
    }
    
    string getPassword() {
        return password;
    }
}
