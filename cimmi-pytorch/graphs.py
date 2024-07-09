
import torch

def read_graph_from_rudy(filename):
    with open(filename, "r") as f:
        size = int(f.readline())
        edges = int(f.readline())
        edge_list = f.readlines()
    
    edge_list = [tuple(map(int, edge.split(" "))) for edge in edge_list]
    couplings = torch.zeros((size, size))
    for x, y, w in edge_list:
        couplings[x][y] = float(w)
        couplings[y][x] = float(w)

    