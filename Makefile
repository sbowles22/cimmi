all: setup

.PHONY: build
build:
	$(MAKE) -C python cimmi

.PHONY: setup
setup: build
	$(MAKE) -C scripts/rudy

.PHONY: clean
clean:
	$(MAKE) -C python clean
	$(MAKE) -C scripts/rudy clean
	rm -rf main LOGFILE

.PHONY: test
test: setup
	$(MAKE) -C scripts/rudy test_graphs
	$(MAKE) -C python test
	
.PHONY: wc
wc:
	wc src/*

.PHONY: cpp_test
cpp_test: build
	$(MAKE) -C scripts/rudy test_graphs
	g++ -O3 src/*.cpp -lfmt -std=c++20 -fopenmp -o main
	time ./main
