
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

simulator::simulator(int x)
{
    num = x; 
}

simulator::~simulator()
{
    std::cout << "goodbye!\n";
}

int simulator::get_x() {
    return num;
}

} // namespace cimmi

#endif