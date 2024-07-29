
"""
Networks define any changes to coupling or feedback in the network
while still retaining a transfer function.

Examples of Modifications include:
    Chaotic Amplitude Control
    Adiabatic Hamiltonians
"""

from transfers import Transfer, TraditionalDOPO
from ising import Ising
from torch import tensor
import torch
from numpy import array
import numpy as np
from graphs import eval_max_cut

class Network:
    def solve(model: Ising) -> tensor:
        return None

class Control(Network):
    def __init__(self, transfer: Transfer = TraditionalDOPO, **kwargs):
        self.transfer = transfer(**kwargs)
    
    def solve(self, model: Ising, 
              steps = 20000, 
              step_size = 0.01,
              noise_magnitude = 0.000, 
              **kwargs):
        for step in range(steps):
            grad = self.transfer.grad(model, step_size=step_size, time=step*step_size)
            # if not step % 100:
            #     print(grad)
            model.state += grad * step_size + \
                           noise_magnitude * torch.normal(torch.zeros_like(model.state), np.sqrt(step_size)*torch.ones_like(model.state))
            
            energy = eval_max_cut(model.state.tolist(), model.couplings)
            
            model.result.state_history.append(model.state.tolist())
            model.result.energy_history.append(energy)
            if energy < model.result.minimum_energy:
                model.result.minimum_energy = energy
                model.result.minimum_energy_state = model.state.tolist()