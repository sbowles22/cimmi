
#ifndef FILE_NETWORK_H
#define FILE_NETWORK_H

#include <fstream>
#include <iostream>
#include "utils.hpp"
#include "graph.hpp"

namespace cimmi::network 
{

using namespace std;
// using namespace cimmi::utils;

typedef enum {
    NONE=0,
    MAX_CUT=1
} problem_t;

class Network
{
private:
    float* s_phase; // In-phase
    float* c_phase; // Quad-phase
    float* ds_phase;
    float* dc_phase;

    cimmi::utils::Matrix<float> couplings;

    int size;
    cimmi::graph::Graph* source;

    float time;
    problem_t problem;
    
    float coupling_strenth;
    float (*pump_schedule) (float t);
    float pump_rate;
    float noise_magnitude;
public:
    Network();
    ~Network();
    Network(int size);
    void disp();

    // Network Topology Functions
    void set_source(cimmi::graph::Graph& g);
    void set_problem(problem_t problem);
    int get_size();

    void set_coupling(int x, int y, float w);
    float get_coupling(int x, int y);

    // Network Parameter Functions
    void set_coupling_strength(float z);
    float get_coupling_strength();

    void set_pump_schedule(float (*f)(float t));
    float get_pump_rate();

    void set_noise_magnitude(float q);
    float get_noise_magnitude();

    // Simulator Control Functions
    void restart();
    float get_time();
    void run(float t_final);

    // Readout functions
};

// Problem mapping functions
void map_max_cut(cimmi::graph::Graph& graph, Network& target);

}

#endif

