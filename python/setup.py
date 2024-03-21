#!/usr/bin/env python

"""
setup.py file for SWIG
"""

from distutils.core import setup, Extension


cimmi_module = Extension('_cimmi',
                           sources=['cimmi_wrap.cxx'],
                           )

setup (name = 'cimmi',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Simple swig example from docs""",
       ext_modules = [cimmi_module],
       py_modules = ["cimmi"],
       )
