# cimmi
Coherent Ising Machine Modeling Interface (CIMMI)

## Graph Generation

CIMMI uses the rudy graph generator and the Gset for its testing. To generate the Gset, simply navigate to `scripts/rudy` and run the `make` command.

## Todo

- [ ] Build Process
    - [X] Initial Build Process (Spencer)
    - [ ] Setuptools Conversion (?)
    - [ ] Autotools Makefile.am (?)
- [ ] Simulator Object
    - [ ] Initial Object (Spencer)
    - [ ] Network Readout
        - [ ] Iterator Wrapper
            - [X] Initial Object (Spencer)
            - [ ] Convert to proper c++ iterator (?)
            - [ ] Add SWIG Wrapping (?)
        - [ ] File reporting (?)
    - [ ] SWIG Interface (?)
- [ ] Network Object
    - [X] Initial Object (Spencer)
    - [ ] Kramer Moyal
        - [X] Initial Function (Spencer)
        - [ ] GPU Acceleration (Spencer)
    - [X] Random Number Generation (Spencer)
    - [X] Euler Maruyama (Spencer)
    - [ ] Add transfer function switching (?) 
    - [ ] Error Handling (?)
- [ ] Graph Object 
    - [X] Initial Object (Spencer)
    - [ ] Automatic Solution Evaluation (?)
- [X] Logging (Spencer)
- [ ] Graphs 
    - [X] Rudy Generation (Spencer)
    - [X] Importing (Spencer)
    - [ ] Problem Conversion (Vidisha)
    - [ ] Random Graph Generation (?)
- [ ] Additional Solvers
    - [ ] Sahini-Gonzales (?)
    - [ ] Simulated Annealing (?)
    - [ ] SNN *Possibly* (?)
    - [ ] Semidefinite Programming *Possibly* (?)
- [ ] Python Tests
    - [ ] 2-OPO Network Evolution .gif (?)
    - [ ] GSET Evaluations *Later* (?)