
#ifndef FILE_GRAPH_H
#define FILE_GRAPH_H

#include <fstream>
#include <iostream>

namespace cimmi::graph 
{

using namespace std;


template <typename T> 
class Matrix
{
private:
    T** _matrix;
public:
    Matrix();
    ~Matrix();
    Matrix(int size);
    T* operator[](int);

    int size;
};


class Graph
{
private:
    Matrix<short> edges;
    void set_edge(int x, int y, short w);
    short get_edge(int x, int y);
public:
    Graph();
    ~Graph();
    Graph(int size);
    static Graph read_from_file(const char* filename);
    void print();
};


}

#endif

