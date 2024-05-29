
BUILD_FILES = build __pycache__ cimmi_wrap.cxx cimmi.py _cimmi.cpython*

all: clean cimmi

cimmi:
	$(SWIG) -Wall -python -c++ cimmi.i
	python3 setup.py build_ext --inplace

clean:
	rm -rf $(BUILD_FILES)

test:
	python3 main.py
