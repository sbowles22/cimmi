
import torch
from itertools import product

def read_graph_from_rudy(filename):
    with open(filename, "r") as f:
        size, edges = tuple(map(int, f.readline().strip().split(" "))) 
        edge_list = f.readlines()
    
    edge_list = [tuple(map(int, edge.strip().split(" "))) for edge in edge_list]
    couplings = torch.zeros((size, size))
    for x, y, w in edge_list:
        x -= 1
        y -= 1
        couplings[x][y] = float(w)
        couplings[y][x] = float(w)
        
    print(couplings)
    return couplings

def eval_max_cut(soln, couplings):
    cut = 0
    for ix, iy in product(range(len(soln)), range(len(soln))):
        if soln[ix] > 0 and soln[iy] < 0:
           cut += couplings[ix][iy] 
           
    return cut