
#include <vector>
#include "cimmi.hpp"
#include "graph.hpp"
#include "network.hpp"
#include "utils.hpp"
#include "logger.hpp"
#include "omp.h"

int main() {
    INFO("Start program.");
    cimmi::graph::Graph g;
    g = *cimmi::graph::Graph::read_from_file("scripts/rudy/test_graphs/complete_16.in");
    // g.print();

    cimmi::network::Network n;
    n.set_coupling_strength(1.1);
    n.set_pump_rate(0.9);
    n.set_noise_magnitude(0.0001);
    DEBUG("Noise Magnitude: {}", n.get_noise_magnitude())
    n.set_problem(cimmi::network::Problem::MAX_CUT);
    n.set_source(&g);
    n.configure();

    n.set_step_size(0.001);
    
    for (int ix = 0; ix < 100; ix++) {
        n.restart();
        for (float t = 0.0; t <= 10; t += 0.10) {
            n.run(t);
            // INFO("Score @({:4.1f}): {:5d}", t, score);
        }
        std::vector<float> state = n.get_state();
        std::vector<int> soln = cimmi::network::soln_max_cut(state);
        int score = cimmi::graph::eval_max_cut(soln, g);
        INFO("Trial {:03d}: {:4d}", ix, score);
    }


    #pragma omp parallel for
    for (int i = 0; i < 10; i++) {
        INFO("Logging event {}", i);
    }

    // n.disp();
    INFO("End program.");

    // std::FILE* file = std::fopen("out.txt","w");
    // fmt::print(file, "The answer is {}.", 42);
    // std::fclose(file);

    return 0;
}
