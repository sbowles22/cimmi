#include <fstream>
#include <iostream>

#include "graph.hpp"

using namespace std;
using namespace cimmi::graph;

template <typename T> 
Matrix<T>::Matrix() {}

template <typename T> 
Matrix<T>::Matrix(int size)
{
    this -> size = size;
    _matrix = new short*[size];
    for (int i = 0; i < size; i++) {
        _matrix[i] = new short[size];
    }
}

template <typename T> 
Matrix<T>::~Matrix() {}

template <typename T> 
T* Matrix<T>::operator[](int i) {
    return _matrix[i];
}

Graph::Graph() {}

Graph::Graph(int size) {
    edges = Matrix<short>(size);
}

Graph::~Graph() {}

void Graph::set_edge(int x, int y, short w) {
    edges[x][y] = w;
}

short Graph::get_edge(int x, int y) {
    return edges[x][y];
}

Graph Graph::read_from_file(const char* filename) {
    cout << "Reading... " << filename << endl; 
    Graph g;
    
    fstream f;
    f.open(filename);

    int nodes, edge_num;
    int x, y;
    short w;

    f >> nodes >> edge_num;
    cout << nodes << endl;
    g = Graph(nodes);
    cout << "Done Creating" << endl;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            g.set_edge(i, j, 0);
        }
    }
    cout << "Edges set to 0" << endl;

    for (int i = 0; i < edge_num; i++) {
        f >> x >> y >> w;
        cout << "X: " << x << ", Y: " << y << ", W: " << w << endl;
        g.set_edge(x - 1, y - 1, w);
        g.set_edge(y - 1, x - 1, w);
    }

    cout << "Starting Printing" << endl;
    g.print();
    cout << "Done Printing" << endl;
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