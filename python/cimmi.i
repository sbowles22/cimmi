
%ignore cimmi::utils::Matrix;
%ignore *::operator[];

%module cimmi
%{
/* Includes the header in the wrapper code */
#define SWIG_FILE_WITH_INIT
#include "../src/cimmi.hpp"
#include "../src/utils.hpp"
#include "../src/graph.hpp"
#include "../src/network.hpp"

%}

/* Parse the header file to generate wrappers */
%include "../src/cimmi.hpp"
%include "../src/utils.hpp"
%include "../src/graph.hpp"
%include "../src/network.hpp"
