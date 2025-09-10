#ifndef _PASSWORD_H_

#define _PASSWORD_H_

#include <iostream>
#include <string>

namespace Authenticate {
    void inputPassword();
    std::string getPassword();
}

namespace {
    std::string password;
    
    bool isValid();
}


#endif