
#ifndef FILE_CIMMI
#define FILE_CIMMI

#include <iostream>
#include <iomanip>

#include "cimmi.hpp"

cimmi::simulator::simulator(int x)
{
    num = x; 
}

cimmi::simulator::~simulator()
{
    std::cout << "goodbye!\n";
}

int cimmi::simulator::get_x() {
    return num;
}

#endif