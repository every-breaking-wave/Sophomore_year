#ifndef ERROR_H
#define ERROR_H
#include <iostream>
#include <string>

static void error(std::string msg){
    throw msg;
}

#endif // ERROR_H
