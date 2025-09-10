#ifndef _USER_H_

#define _USER_H_


#include <iostream>
#include <string>

namespace Authenticate {
    void inputUserName();
    std::string getUserName();
}

namespace {
    std::string username;
    
    bool isValid();
}


#endif