

#include <iostream>
#include <iomanip>

#include "cimmi.hpp"

cimmi::Simulator::Simulator(int x)
{
    num = x; 
}

cimmi::Simulator::~Simulator()
{
    INFO("Simulator: goodbye!\n");
}

int cimmi::Simulator::get_x() {
    return num;
}
