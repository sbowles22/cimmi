#!/usr/bin/env python

"""
setup.py file for SWIG
"""

import os
from distutils.core import setup, Extension

SRC_DIR = '../src/'
sources = []
for file in os.listdir(SRC_DIR):
       if file.endswith(".cpp"):
              sources.append(SRC_DIR + file)  
sources.append('cimmi_wrap.cxx') 

cimmi_module = Extension('_cimmi',
                           sources=sources,
                           extra_link_args=['-lfmt'],
                           extra_compile_args=['-std=c++20', '-fopenmp'],
                           )

setup (name = 'cimmi',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Simple swig example from docs""",
       ext_modules = [cimmi_module],
       py_modules = ["cimmi"],
       )
