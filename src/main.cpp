#include "cimmi.hpp"
#include "graph.hpp"
#include "network.hpp"
#include "utils.hpp"
#include "logger.hpp"
#include "omp.h"

int main() {
    INFO("Start program.");
    cimmi::graph::Graph g;
    g = *cimmi::graph::Graph::read_from_file("scripts/rudy/test_graphs/complete_2.in");
    g.print();

    cimmi::network::Network n;
    n.set_coupling_strength(1.1);
    n.set_pump_rate(0.9);
    n.set_noise_magnitude(0.0001);
    DEBUG("Noise Magnitude: {}", n.get_noise_magnitude())
    n.set_problem(cimmi::network::Problem::MAX_CUT);
    n.set_source(&g);
    n.configure();

    n.set_step_size(0.001);
    n.run(10);

    #pragma omp parallel for
    for (int i = 0; i < 100; i++) {
        INFO("Logging event {}", i);
    }

    n.disp();
    INFO("End program.");

    // std::FILE* file = std::fopen("out.txt","w");
    // fmt::print(file, "The answer is {}.", 42);
    // std::fclose(file);

    return 0;
}
