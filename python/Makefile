
BUILD_FILES = build __pycache__ cimmi_wrap.cxx cimmi.py _cimmi.cpython*
RUN_FILES = LOGFILE

all: clean cimmi

cimmi:
	$(SWIG) -Wall -python -c++ cimmi.i
	python3 setup.py build_ext --inplace

clean:
	rm -rf $(BUILD_FILES)
	rm -rf $(RUN_FILES)

test:
	python3 main.py
