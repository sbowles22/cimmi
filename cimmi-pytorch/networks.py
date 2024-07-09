
"""
Networks define any changes to coupling or feedback in the network
while still retaining a transfer function.

Examples of Modifications include:
    Chaotic Amplitude Control
    Adiabatic Hamiltonians
"""

from transfers import Transfer, DOPO
from ising import Ising
from torch import tensor
import torch
from numpy import array
import numpy as np

class Network:
    def solve(model: Ising) -> tensor:
        return None

class Control(Network):
    def __init__(self, transfer: Transfer = DOPO, **kwargs):
        self.transfer = transfer(**kwargs)
    
    def solve(self, model: Ising, 
              steps = 10000, 
              step_size = 0.01,
              noise_magnitude = 0.001, 
              **kwargs):
        for step in range(steps):
            grad = self.transfer.grad(model, step_size=step_size, time=step*step_size)
            if not step % 100:
                print(grad)
            model.state += grad * step_size + \
                           noise_magnitude * torch.normal(torch.zeros_like(model.state), np.sqrt(step_size)*torch.ones_like(model.state))
            
            model.Result.state_history.append(model.state.tolist())