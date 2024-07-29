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

class TraditionalDOPO(Transfer):
    """
    DOPO Using both a c and s phase
    TODO: add clearing function to remove state between trials
    """
    
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
    
class DOPO(Transfer):
    """
    DOPO Using only a c phase
    """
    
    def __init__(self, 
                 pump_schedule: Callable [[float], float] = schedule_constant(),
                 **kwargs) -> None:
        super().__init__(**kwargs)
        self.pump_schedule = pump_schedule
    
    def grad(self, model: Ising, step_size: float = 0, time=0, **kwargs) -> array:
        dcdt = (-1 + self.pump_schedule(time) - (model.state**2)) * model.state
        dcdt += model.state @ model.couplings
        
        return dcdt
    
class FifthOrder(Transfer):
    """
    DOPO Using a fifth order transfer function
    """
    
    def __init__(self, 
                 pump_schedule: Callable [[float], float] = schedule_constant(), *,
                 fifth_order_param = 0.1,
                 **kwargs) -> None:
        super().__init__(**kwargs)
        self.pump_schedule = pump_schedule
        self.fifth_order_param = fifth_order_param
    
    def grad(self, model: Ising, step_size: float = 0, time=0, **kwargs) -> array:
        dcdt = (-1 + self.pump_schedule(time) - (model.state**2) + self.fifth_order_param * (model.state**4)) * model.state
        dcdt += model.state @ model.couplings
        
        return dcdt
    
class SNN(Transfer):
    """
    SNN-based DOPO
    """
        
    def __init__(self, 
                 pump_schedule: Callable [[float], float] = schedule_constant(), *,
                 linear_loss_param = 0.1,
                 **kwargs) -> None:
        super().__init__(**kwargs)
        self.pump_schedule = pump_schedule
        self.linear_loss_param = linear_loss_param
        self.b_phase = None
    
    def grad(self, model: Ising, step_size: float = 0, time=0, **kwargs) -> array:
        if self.b_phase is None:
            self.b_phase = torch.zeros_like(model.state)
        
        dcdt = (-1 + self.pump_schedule(time)) * model.state - (model.state**3) - self.linear_loss_param * self.b_phase
        dcdt += model.state @ model.couplings
        
        dbdt = -self.linear_loss_param * self.b_phase + model.state
        self.b_phase += dbdt * step_size
        
        return dcdt
    
class Clipped(Transfer):
    """
    "Stable" linear clipped function
    Similar to Bohm clipped
    """
    
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


transfer_dict = {
    'TraditionalDOPO': TraditionalDOPO,
    'DOPO': DOPO,
    'FifthOrder': FifthOrder,
    'SNN': SNN,
    'Clipped': Clipped,
}
