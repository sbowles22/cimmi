from ising import Ising
from schedules import schedule_constant
from typing import Callable
from numpy import array
import numpy as np
import torch

"""
Various transfer functions used by different CIMs
"""

class Transfer:
    def __init__(self, **kwargs) -> None:
        pass
    
    def grad(self, model: Ising, **kwargs) -> array:
        return np.size(model.size)

class DOPO(Transfer):
    def __init__(self, 
                 pump_schedule: Callable [[float], float] = schedule_constant(),
                 **kwargs) -> None:
        super().__init__(**kwargs)
        self.pump_schedule = pump_schedule
        self.s_phase = None
    
    def grad(self, model: Ising, step_size: float = 0, time=0, **kwargs) -> array:
        if self.s_phase is None:
            self.s_phase = torch.zeros_like(model.state)
        dcdt = (-1 + self.pump_schedule(time) - (model.state**2 + self.s_phase**2)) * model.state
        dcdt += model.state @ model.couplings
        
        dsdt = (-1 - self.pump_schedule(time) - (model.state**2 + self.s_phase**2)) * self.s_phase
        dsdt += self.s_phase @ model.couplings
        self.s_phase += dsdt * step_size
        
        return dcdt #, dsdt
    
class Clipped(Transfer):
    def __init__(self, 
                 pump_schedule: Callable [[float], float] = schedule_constant(),
                 **kwargs) -> None:
        super().__init__(**kwargs)
        self.pump_schedule = pump_schedule
    
    def grad(self, model: Ising, time=0, **kwargs) -> array:
        
        clip = lambda x: -x * (-1 + self.pump_schedule(time)) if abs(x) < 1 else x
        
        dcdt = -model.state
        for idx, c in enumerate(dcdt):
            dcdt[idx] = clip(c)
        dcdt += model.state @ model.couplings
        
        return dcdt
