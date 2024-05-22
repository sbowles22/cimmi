
#include "utils.hpp"
#include "graph.hpp"
#include "network.hpp"

using namespace std;
using namespace cimmi::utils;
using namespace cimmi::graph;
using namespace cimmi::network;

//////////////////////////////////
// MAPPING FUNCTION DEFINITIONS //
//////////////////////////////////

void cimmi::network::map_max_cut(Graph& graph, Network& target) {
    for (int ix = 0; ix < target.get_size(); ix++) {
        for (int iy = 0; iy < target.get_size(); iy++) {
            float c = -graph.get_edge(ix, iy) * target.get_coupling_strength();
            target.set_coupling(ix, iy, c);
        }
    }
}

//////////////////////////////////
// NETWORK FUNCTION DEFINITIONS //
//////////////////////////////////

Network::Network() {}
Network::~Network() {}

Network::Network(int size) {
    this -> size = size;
    s_phase = new float[size];
    c_phase = new float[size];
    ds_phase = new float[size];
    dc_phase = new float[size];
    couplings = Matrix<float>(size);
    
    // this->restart();
}

void Network::disp() {

    printf("SIZE: %d\n", size);
    printf("TIME: %f\n", time);
    printf("PROB: %d\n", (int) problem);
    
    printf("Coupling strength: %e\n", coupling_strenth);
    printf("Pump Rate: %e\n", this->get_pump_rate());
    printf("Noise Magnitude: %e\n", noise_magnitude);

    printf("\nCouplings:\n");
    for (int ix = 0; ix < size; ix++) {
        for (int iy = 0; iy < size; iy++) {
            printf("%+6e ", couplings[ix][iy]);
        }
        cout << endl;
    }
}

// Network Topology Functions
void Network::set_source(Graph& g) {
    source = &g;
    // TODO: add check for g size is network size

    switch (problem)
    {
    case MAX_CUT:
        map_max_cut(*source, *this);
        break;
    
    default: break;
    }
}

void Network::set_problem(problem_t problem) {
    problem = problem;
}
int Network::get_size() {
    return size;
}

void Network::set_coupling(int x, int y, float w) {
    couplings[x][y] = w;
}

float Network::get_coupling(int x, int y) {
    return couplings[x][y];
}

// Network Parameter Functions
void Network::set_coupling_strength(float z) {
    coupling_strenth = z;
}

float Network::get_coupling_strength() {
    return coupling_strenth;
}

void Network::set_pump_schedule(float (*f)(float t)) {
    pump_schedule = f;
}

float Network::get_pump_rate() {
    if (pump_schedule == NULL) {
        return 0; // TODO: Float NaN
    }

    return pump_schedule(time);
}

void Network::set_noise_magnitude(float q) {
    noise_magnitude = q;
}

float Network::get_noise_magnitude() {
    return noise_magnitude;
}

// Simulator Control Functions
void Network::restart() {
    time = 0;
    for (int i = 0; i < size; i++) {
        s_phase[i] = 0;
        c_phase[i] = 0;
    }
}

float Network::get_time() {
    return time;
}

void Network::run(float t_final) {
    // TODO
    time = t_final;
}
