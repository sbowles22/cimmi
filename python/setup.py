#!/usr/bin/env python

"""
setup.py file for SWIG
"""

import os
from distutils.core import setup, Extension

SRC_DIR = '../src/'
sources = ['cimmi_wrap.cxx']
for file in os.listdir(SRC_DIR):
       if file.endswith(".cpp"):
              sources.append(SRC_DIR + file)   

cimmi_module = Extension('_cimmi',
                           sources=sources,
                           )

setup (name = 'cimmi',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Simple swig example from docs""",
       ext_modules = [cimmi_module],
       py_modules = ["cimmi"],
       )
