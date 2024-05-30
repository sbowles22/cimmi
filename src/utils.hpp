
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <vector>
#include "logger.hpp"

namespace cimmi::utils
{

using namespace std;

//////////////////
// Matrix Class //
//////////////////

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

template <typename T> 
Matrix<T>::Matrix() {}

template <typename T> 
Matrix<T>::Matrix(int size)
{
    this -> size = size;
    _matrix = new T*[size];
    for (int i = 0; i < size; i++) {
        _matrix[i] = new T[size];
    }
}

template <typename T> 
Matrix<T>::~Matrix() {}

template <typename T> 
T* Matrix<T>::operator[](int i) {
    return _matrix[i];
}

///////////////////////////////////////
// Iterable SWIG passthrough wrapper //
///////////////////////////////////////

// TODO: Convert to proper iterable type

template <typename T> 
class Iterable_Wrap
{
private:
    T* _array = NULL;
    int ix = 0;
public:
    Iterable_Wrap();
    ~Iterable_Wrap();
    Iterable_Wrap(T* ptr, int size);
    Iterable_Wrap(std::vector<T>);
    T operator[](int);

    T _iter();
    T _next();

    int get_ix();
    int size = -1;
};

template <typename T>
Iterable_Wrap<T>::Iterable_Wrap() {}

template <typename T> 
Iterable_Wrap<T>::Iterable_Wrap(T* ptr, int n) {
    this -> size = n;
    _array = ptr;
}

template <typename T>
Iterable_Wrap<T>::Iterable_Wrap(std::vector<T> vec) {
    this -> size = vec.size;
    _array = &vec[0];
}

template <typename T>
Iterable_Wrap<T>::~Iterable_Wrap() {}

template <typename T> 
T Iterable_Wrap<T>::operator[](int ix) {
    return _array[ix];
}

template <typename T> 
T Iterable_Wrap<T>::_iter() {
    ix = 0;
    return _array[ix];
}

template <typename T> 
T Iterable_Wrap<T>::_next() {
    ix++;
    return _array[ix];
}

template <typename T> 
int Iterable_Wrap<T>::get_ix() {
    return ix;
}

}

#endif
