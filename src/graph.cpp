
#include <fstream>
#include <iostream>

#include "utils.hpp"
#include "graph.hpp"

using namespace std;
using namespace cimmi::graph;
using namespace cimmi::utils;

///////////////////////////////
// Graph Problem Evaluations //
///////////////////////////////

int cimmi::graph::eval_max_cut(std::vector<int>& soln, cimmi::graph::Graph& graph) {
    int score = 0;
    
    for (long unsigned int s1 = 0; s1 < soln.size(); s1++) {
        for (long unsigned int s2 = s1 + 1; s2 < soln.size(); s2++) {
            if (soln[s1] != soln[s2]) {
                score += graph.get_edge(s1, s2);
            }
        }
    }

    return score;
}

//////////////////////////////
// Graph Method Definitions //
//////////////////////////////

Graph::Graph() {}

Graph::Graph(int size) {
    edges = Matrix<short>(size);
}

Graph::~Graph() {}

int Graph::get_size() {
    return edges.size;
}

void Graph::set_edge(int x, int y, short w) {
    edges[x][y] = w;
}

short Graph::get_edge(int x, int y) {
    return edges[x][y];
}

Graph* Graph::read_from_file(const char* filename) {
    INFO("Reading graph from {}... ", filename); 
    Graph* g;
    
    fstream f;
    f.open(filename);

    int nodes, edge_num;
    int x, y;
    short w;

    f >> nodes >> edge_num;
    INFO("Nodes: {}", nodes);
    g = new Graph(nodes);
    DEBUG("Graph object allocatied");
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            g -> set_edge(i, j, 0);
        }
    }
    DEBUG("All Graph edges set to 0");

    for (int i = 0; i < edge_num; i++) {
        f >> x >> y >> w;
        // DEBUG("X: {}, Y: {}, W: {}", x, y, w);
        g -> set_edge(x - 1, y - 1, w);
        g -> set_edge(y - 1, x - 1, w);
    }

    INFO("Done reading graph from {}.", filename);
    return g;
}

void Graph::print() {
    for (int i = 0; i < edges.size; i++) {
        for (int j = 0; j < edges.size; j++) {
        printf("%+2d", edges[i][j]);
        if (j != edges.size - 1) cout << " ";
        }
        cout << endl;
    }
}
