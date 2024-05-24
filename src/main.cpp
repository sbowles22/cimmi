#include "cimmi.hpp"
#include "graph.hpp"
#include "network.hpp"
#include "utils.hpp"

int main() {
    // cimmi::utils::Matrix<int> m;
    cimmi::graph::Graph g;
    g = *cimmi::graph::Graph::read_from_file("scripts/rudy/test_graphs/complete_2.in");
    g.print();

    cimmi::network::Network n;
    n.set_coupling_strength(1.1);
    n.set_pump_rate(0.9);
    n.set_noise_magnitude(0.0001);
    n.set_problem(cimmi::network::Problem::MAX_CUT);
    n.set_source(&g);
    n.configure();

    n.set_step_size(0.001);
    n.run(10);

    n.disp();

    return 0;
}
