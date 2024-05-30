

#include <iostream>
#include <iomanip>

#include "cimmi.hpp"

cimmi::simulator::simulator(int x)
{
    num = x; 
}

cimmi::simulator::~simulator()
{
    INFO("Simulator: goodbye!\n");
}

int cimmi::simulator::get_x() {
    return num;
}
