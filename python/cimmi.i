%module cimmi
%{
/* Includes the header in the wrapper code */
#define SWIG_FILE_WITH_INIT
#include "../src/cimmi.hpp"
%}

/* Parse the header file to generate wrappers */
%include "../src/cimmi.hpp"
