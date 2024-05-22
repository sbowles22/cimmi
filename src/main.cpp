#include "cimmi.hpp"
#include "graph.hpp"
#include "network.hpp"
#include "utils.hpp"

int main() {
    // cimmi::utils::Matrix<int> m;
    cimmi::graph::Graph g;
    g = cimmi::graph::Graph::read_from_file("scripts/rudy/test_graphs/complete_5.in");
    g.print();

    cimmi::network::Network n;
    n.set_source(g);

    return 0;
}
