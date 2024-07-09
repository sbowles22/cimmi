
"""
Solvers contain all information for the method of solving a particular problem.
This includes both standard methods (DOPO Network) and non-standard (Sahni-Gonzales).
"""

from dataclasses import dataclass
from transfers import DOPO
from networks import Network, Control
from itertools import product

class Solver:
    def __init__(self, **kwargs) -> None:
        pass
    
    def solve(self, model, **kwargs):
        pass
    

class NetworkSolver(Solver):
    def __init__(self, network = Control, **kwargs) -> None:
        super().__init__(**kwargs)
        self.network = network(**kwargs)
    
    def solve(self, model, **kwargs):
        self.network.solve(model, **kwargs)

class Standard(NetworkSolver):
    """
    Represents model with no Coupling Modifications
    """

    def __init__(self, **kwargs) -> None:
        super().__init__(**kwargs)
        self.network = Control(**kwargs)
        
class SG3(Solver):
    def __init__(self, **kwargs) -> None:
        super().__init__(**kwargs)
    
    def solve(self, model, **kwargs):
        unallocated = list(range(model.size))
        S1, S2 = [], []
        
        mx, my = 0, 0
        max_weight = float('-inf')
        for ix, iy in product(range(model.size), range(model.size)):
            if ix == iy:
                continue
            if jxy := model.couplings[iy][ix] > max_weight:
                mx, my = ix, iy
                max_weight = jxy
        
        unallocated.remove(mx)
        unallocated.remove(my)
        S1.append(mx)
        S2.append(my)
        
        while unallocated:
            # print(len(unallocated))
            max_score_spin = unallocated[0]
            max_score = float('inf')
            for spin in unallocated:
                sum_1 = sum((model.couplings[spin][ix] for ix in S1))
                sum_2 = sum((model.couplings[spin][ix] for ix in S2))
                
                # score = min(sum_1, sum_2)
                score = -abs(sum_1 - sum_2)
                if score < max_score:
                    max_score_spin = spin
                    max_score = score
            
            sum_1 = sum((model.couplings[max_score_spin][ix] for ix in S1))
            sum_2 = sum((model.couplings[max_score_spin][ix] for ix in S2))
            
            unallocated.remove(max_score_spin)
            if sum_1 < sum_2:
                S2.append(max_score_spin)
            else:
                S1.append(max_score_spin)
        
        for ix in range(model.size):
            model.state[ix] = 1.0 if ix in S1 else -1.0