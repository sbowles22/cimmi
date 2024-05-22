
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

namespace cimmi::utils
{

// using namespace std;

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

}

#endif
