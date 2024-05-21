all: setup

.PHONY: build
build:
	$(MAKE) -C python

.PHONY: setup
setup: build
	$(MAKE) -C scripts/rudy

.PHONY: clean
clean:
	$(MAKE) -C python clean
	$(MAKE) -C scripts/rudy clean

.PHONY: test
test:
	$(MAKE) -C scripts/rudy test_graphs
	$(MAKE) -C python test
	
