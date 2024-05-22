
BUILD_FILES = cimmi_wrap.cxx cimmi.py

all: clean cimmi

cimmi:
	$(SWIG) -python -c++ cimmi.i
	python3 setup.py build_ext --inplace

clean:
	rm -rf $(BUILD_FILES)

test:
	python3 main.py
