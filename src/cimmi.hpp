
#ifndef FILE_CIMMI_H
#define FILE_CIMMI_H

#include <iostream>
#include <iomanip>

namespace cimmi
{
    
class simulator
{
private:
    int num;
public:
    simulator(int x);
    ~simulator();
    int get_x();
};

} // namespace cimmi

#endif