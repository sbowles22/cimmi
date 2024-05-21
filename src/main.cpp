#include "cimmi.hpp"
#include "graph.hpp"

int main() {
    cimmi::graph::Graph g;
    g = cimmi::graph::Graph::read_from_file("../scripts/rudy/test_graphs/complete_5.in");
    g.print();

    return 0;
}
