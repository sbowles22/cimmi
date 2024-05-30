%include "std_vector.i"

namespace std {
   %template(vectori) vector<int>;
   %template(vectorf) vector<float>;
   %template(vectord) vector<double>;
};

%ignore cimmi::logger;
%ignore fmt;
%ignore cimmi::utils::Matrix;
%ignore *::operator[];

// %import  "../src/logger.hpp"
// %import  "../src/utils.hpp"

%module cimmi
%{
/* Includes the header in the wrapper code */
#define SWIG_FILE_WITH_INIT
#include "../src/logger.hpp"
#include "../src/utils.hpp"
#include "../src/cimmi.hpp"
#include "../src/graph.hpp"
#include "../src/network.hpp"

%}

/* Parse the header file to generate wrappers */
%include  "../src/logger.hpp"
%include  "../src/utils.hpp"
%include "../src/cimmi.hpp"
%include "../src/graph.hpp"
%include "../src/network.hpp"
