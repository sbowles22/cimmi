
#ifndef FILE_CIMMI_H
#define FILE_CIMMI_H

#include <iostream>
#include <iomanip>
#include <list>
#include "network.hpp"
#include "utils.hpp"

namespace cimmi
{
    
class Simulator
{
private:
    int num;
public:
    Simulator(int x);
    ~Simulator();
    int get_x();
};

} // namespace cimmi

#endif