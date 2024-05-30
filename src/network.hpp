
#ifndef FILE_NETWORK_H
#define FILE_NETWORK_H

#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include "utils.hpp"
#include "graph.hpp"

namespace cimmi::network 
{

using namespace std;
// using namespace cimmi::utils;

enum class Problem
{
    NONE=0, MAX_CUT=1
};

class Network
{
private:
    float* s_phase; // In-phase
    float* c_phase; // Quad-phase
    float* ds_phase;
    float* dc_phase;

    cimmi::utils::Matrix<float> couplings;

    int size;
    cimmi::graph::Graph* source = NULL;

    float time;
    Problem problem;
    
    float coupling_strenth;
    float (*pump_schedule) (float t) = NULL;
    float pump_rate;
    float noise_magnitude;

    void resize(int s);

    float step_size;
    std::default_random_engine rng;
    std::normal_distribution<float> normal;

    // Network Calculation Functions
    void kraymer_moyal();
    void euler_maruyama();
public:
    Network();
    ~Network();
    Network(int s);
    void disp();

    // Network Topology Functions
    void set_source(cimmi::graph::Graph* g);
    void set_problem(Problem p);
    int get_size();

    void set_coupling(int x, int y, float w);
    float get_coupling(int x, int y);

    // Network Parameter Functions
    void set_coupling_strength(float z);
    float get_coupling_strength();

    void set_pump_schedule(float (*f)(float t));
    void set_pump_rate(float p);
    float get_pump_rate();

    void set_noise_magnitude(float q);
    float get_noise_magnitude();

    void set_step_size(float h);

    // Simulator Control Functions
    void configure();
    void restart();
    float get_time();
    void run(float t_final);

    // Readout functions
    vector<float> get_state();
};

// Problem mapping functions
void map_max_cut(cimmi::graph::Graph& graph, Network& target);

// Problem solution functions
vector<int> soln_max_cut(vector<float>& state);

} // namespace cimmi::network

#endif

