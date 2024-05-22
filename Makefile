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

.PHONY: test
test: setup
	$(MAKE) -C scripts/rudy test_graphs
	$(MAKE) -C python test
	
.PHONY: wc
wc:
	wc src/*

.PHONY: cpp_test
cpp_test:
	g++ src/*.cpp -o main
	./main
