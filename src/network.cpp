
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

///////////////////////////////////
// SOLUTION FUNCTION DEFINITIONS //
///////////////////////////////////

vector<int> cimmi::network::soln_max_cut(vector<float>& state) {
    vector<int> soln = vector<int>(state.size());

    for (long unsigned int ix = 0; ix < state.size(); ix++) {
        soln[ix] = (state[ix] > 0) ? 1 : -1; 
    }

    return soln;
}

//////////////////////////////////
// NETWORK FUNCTION DEFINITIONS //
//////////////////////////////////

Network::Network() {}
Network::~Network() {}

Network::Network(int size) {
    this -> resize(size);
}

void Network::resize(int size) {
    this -> size = size;
    s_phase = new float[size];
    c_phase = new float[size];
    ds_phase = new float[size];
    dc_phase = new float[size];
    couplings = Matrix<float>(size);
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

    printf("\nReadout:\n");
    for (int ix = 0; ix < size; ix++) {
        printf("%02d: %+e %+e\n", ix, c_phase[ix], s_phase[ix]);
    }
}

// Network Calculation Functions
void Network::kraymer_moyal() {
    pump_rate = this -> get_pump_rate();

    // #pragma omp parallel for schedule(dynamic, 8)
    // #pragma omp distribute parallel for simd
    // #pragma omp parallel for
    #pragma omp parallel for schedule(dynamic, 8)
    for (int ix = 0; ix < size; ix++) {
        dc_phase[ix] = (-1 + pump_rate - (c_phase[ix]*c_phase[ix] + s_phase[ix]*s_phase[ix])) * c_phase[ix];
        // #pragma omp parallel for reduction(+:dc_phase[ix])
        for (int iy = 0; iy < size; iy++) {
            dc_phase[ix] += (couplings)[ix][iy] * c_phase[iy];
        }
    }

    // #pragma omp parallel for schedule(dynamic, 8)
    // #pragma omp distribute parallel for simd
    // #pragma omp parallel for
    // #pragma omp parallel for schedule(dynamic, 8)
    for (int ix = 0; ix < size; ix++) {
        ds_phase[ix] = (-1 - pump_rate - (c_phase[ix]*c_phase[ix] + s_phase[ix]*s_phase[ix])) * s_phase[ix];
    }
}

void Network::euler_maruyama() {
    for (int ix = 0; ix < size; ix++) {
        c_phase[ix] += dc_phase[ix] * step_size + noise_magnitude * normal(rng);
        s_phase[ix] += ds_phase[ix] * step_size + noise_magnitude * normal(rng);
    }
}

// Network Topology Functions
void Network::set_source(Graph* g) {
    source = g;
    // TODO: add check for g size is network size
}

void Network::set_problem(Problem p) {
    problem = p;
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

void Network::set_pump_rate(float p) {
    pump_rate = p;
}

float Network::get_pump_rate() {
    if (pump_schedule == NULL) {
        return pump_rate; // TODO: Float NaN
    }

    return pump_schedule(time);
}

void Network::set_noise_magnitude(float q) {
    noise_magnitude = q;
}

float Network::get_noise_magnitude() {
    return noise_magnitude;
}

void Network::set_step_size(float h) {
    step_size = h;
    normal = std::normal_distribution<float>(0.0, sqrt(h));
}


// Simulator Control Functions
void Network::configure() {
    INFO("Configuring network...");
    this -> resize(source->get_size());
    
    switch (problem)
    {
    case Problem::MAX_CUT:
        INFO("Mapping max cut {} to {}...", (void*) source, (void*) this);
        map_max_cut(*source, *this);
        INFO("Mapped max cut {} to {}.\n", (void*) source, (void*) this);
        break;
    
    default: break;
    }

    this -> restart();
    INFO("Configured network.\n");
}

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
    while (time < t_final) {
        this -> kraymer_moyal();
        this -> euler_maruyama();
        time += step_size;
    }
}

// Network Readout Functions

vector<float> Network::get_state() {
    return vector<float>(c_phase, c_phase + size);
}
