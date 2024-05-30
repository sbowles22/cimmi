
#include <vector>
#include "cimmi.hpp"
#include "graph.hpp"
#include "network.hpp"
#include "utils.hpp"
#include "logger.hpp"
#include "omp.h"

int main() {
    INFO("Start program.");

    omp_set_num_threads(8);
    INFO("OMP_NUM_THREADS: {}", omp_get_num_threads());
    
    cimmi::graph::Graph g;
    // g = *cimmi::graph::Graph::read_from_file("scripts/rudy/test_graphs/complete_16.in");
    g = *cimmi::graph::Graph::read_from_file("scripts/rudy/graphs/g07.in");
    // g.print();

    cimmi::network::Network n;
    n.set_coupling_strength(1.1);
    n.set_pump_rate(0.9);
    n.set_noise_magnitude(0.01);
    DEBUG("Noise Magnitude: {}", n.get_noise_magnitude())
    n.set_problem(cimmi::network::Problem::MAX_CUT);
    n.set_source(&g);
    n.configure();

    n.set_step_size(0.001);
    
    for (int ix = 0; ix < 10; ix++) {
        n.restart();
        for (float t = 0.0; t <= 10; t += 0.10) {
            n.run(t);
            // std::vector<float> state = n.get_state();
            // std::vector<int> soln = cimmi::network::soln_max_cut(state);
            // int score = cimmi::graph::eval_max_cut(soln, g);
            // INFO("Score @({:4.1f}): {:5d}", t, score);
        }
        std::vector<float> state = n.get_state();
        std::vector<int> soln = cimmi::network::soln_max_cut(state);
        int score = cimmi::graph::eval_max_cut(soln, g);
        INFO("Trial {:03d}: {:4d}", ix, score);
    }

    // n.disp();
    INFO("End program.");

    return 0;
}
