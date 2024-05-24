
#ifndef FILE_GRAPH_H
#define FILE_GRAPH_H

#include <fstream>
#include <iostream>
#include "utils.hpp"

namespace cimmi::graph 
{

using namespace std;
using namespace cimmi::utils;


class Graph
{
private:
    Matrix<short> edges;
public:
    Graph();
    ~Graph();
    Graph(int size);

    int get_size();

    void set_edge(int x, int y, short w);
    short get_edge(int x, int y);

    static Graph* read_from_file(const char* filename);
    void print();
};


}

#endif

