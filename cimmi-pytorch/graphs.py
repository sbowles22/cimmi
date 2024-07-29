
import torch
from torch import tensor
import numpy as np
from itertools import product
import matplotlib.pyplot as plt
from PIL import Image, ImageFile
# ImageFile.LOAD_TRUNCATED_IMAGES = True
from typing import Callable

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
        
    return couplings

def eval_max_cut(soln, couplings):
    cut = 0
    for ix, iy in product(range(len(soln)), range(len(soln))):
        if soln[ix] > 0 and soln[iy] < 0:
           cut += couplings[ix][iy] 
           
    return cut

##############
# GRID STUFF #
##############

grid_graph_coordinate_map = lambda size, ix, iy: iy*size + ix
grid_graph_coordinate_demap = lambda size, idn: (idn % size, idn // size)
grid_graph_max_cut = lambda size: 2*(size - 1)*size
def generate_grid_graph(size: int = 5):
    couplings = torch.zeros((size**2, size**2))
    coord_map = lambda ix, iy: grid_graph_coordinate_map(size, ix, iy)
    coord_demap = lambda idn: grid_graph_coordinate_demap(size, idn)
    
    for idn in range(size**2):
        idx, idy = coord_demap(idn)
        for dx, dy in ((-1, 0), (1, 0), (0, -1), (0, 1)):
            source = idn
            target = coord_map(idx + dx, idy + dy)
            if 0 <= idx + dx < size and 0 <= idy + dy < size:
                couplings[source][target] = float(1)
                couplings[target][source] = float(1)
        
    return couplings

def render_grid_gif(states: list[tensor], *, max_time=None):
    steps = len(states)
    ims = []
    for state in states:
        fig, _ = render_grid(state)
        fig.savefig('grid.png')
        ims.append(Image.open('grid.png'))
    ims[0].save('grids.gif', save_all=True, append_images=ims, fps=60, loop=0)

###################
# GRAPHING GRAPHS # (best joke of 2016)
###################

def render_state_prog_gif(states: list[tensor], renderers: list[Callable], *,
                          filename='ising.gif', nrows=1, ncols=1, fps=60, loop=0, step=1,
                          title=None, 
                          **kwargs):
    ims = []
    for state_idx, _ in enumerate(states):
        if state_idx % step != 0:
            continue
        
        fig, _ = render_state(state_idx, states, renderers, nrows=nrows, ncols=ncols, **kwargs)
        if title: 
            fig.suptitle(title)
            
        fig.savefig('_tmp.png')
        plt.close(fig)
        ims.append(Image.open('_tmp.png'))
        
        try:
            ims[-1].load()
        except IOError:
            pass # You can always log it to logger
        
    print(len(ims))
    ims[0].save(filename, save_all=True, append_images=ims[1:], fps=fps, loop=loop)
        

def render_state(state_idx: int, states: list[tensor], renderers: list[Callable], *, nrows=1, ncols=1, **kwargs):
    assert nrows * ncols == len(renderers)
    state = states[state_idx]
    
    fig, axs = plt.subplots(nrows=nrows, ncols=ncols, layout='constrained')
    
    if nrows == 1 and ncols == 1:
        renderers[0](axs, state_idx, states, **kwargs)
        return fig, axs
    
    for ax_idx in range(len(renderers)):
        renderers[ax_idx](axs[ax_idx], state_idx, states, **kwargs)
    
    return fig, axs

def grid_renderer(ax, state_idx: int, states: list[tensor], *, with_domain_border=False, time=None, **kwargs):
    state = states[state_idx]
    size = round(np.sqrt(len(state)))
    grid_state = torch.reshape(tensor(state), (size, size))
    
    ax.imshow(grid_state)
    
    if with_domain_border:
        for x, y in product(range(size), range(size)):
            if x < size-1 and state[grid_graph_coordinate_map(size, x, y)] * state[grid_graph_coordinate_map(size, x+1, y)] > 0:
                ax.plot((x + 0.5, x + 0.5), (y + 0.5, y - 0.5), color='r')
            if y < size-1 and state[grid_graph_coordinate_map(size, x, y)] * state[grid_graph_coordinate_map(size, x, y+1)] > 0:
                ax.plot((x + 0.5, x - 0.5), (y + 0.5, y + 0.5), color='r')

def state_history_renderer(ax, state_idx: int, states: list[tensor], *, min_val=-1, max_val=1, num_rendered=20, **kwargs):
    ax.set_box_aspect(1)
    step_rendered = len(states[0]) // num_rendered
    ax.plot([state[::step_rendered] for state in states])
    ax.axvline(state_idx, min_val, max_val, linestyle='--', color='k')
    
    ax.set_ylabel("CIM Spin (a.u.)")
    ax.set_xlabel("Steps")
