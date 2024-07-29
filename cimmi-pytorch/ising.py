
from torch import tensor
import torch
import numpy as np

class Ising:
    """
    Class to store fundementals of Ising Model
    """
    def __init__(self, couplings: tensor, *, init_state = None):
        assert couplings.dim() == 2 # is matrix
        assert couplings.size(dim=0) == couplings.size(dim=1) # is square
        if init_state:
            assert init_state.size(dim=0) == couplings.size(dim=0) # init state is correct size if used
        
        self.couplings = couplings
        self.state = init_state if init_state else torch.zeros(couplings.size(dim=0))
        self.size = self.state.size(dim=0)
        self.Result.state_history = []
        
    def set_state(self, state: tensor = None):
        self.state = state if state else torch.zeros(self.couplings.size(dim=0))
                
    class Result(dict):
        """
        Subclass to store model results
        """
        
        def __getattr__(self, key):
            try:
                return self[key]
            except KeyError as e:
                raise AttributeError(key) from e

        __setattr__ = dict.__setitem__
        __delattr__ = dict.__delitem__

        def __dir__(self):
            return list(self.keys())