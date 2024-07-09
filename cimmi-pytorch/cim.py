

from ising import Ising
# from typing import Callable
from solvers import Solver, Standard
# from schedules import schedule_constant

import torch
import numpy as np

class CIM:
    def __init__(self,
        weight_matrix: np.array, *,
        solver: Solver = Standard,
        **kwargs,
        # pump_schedule: Callable[[float], float] = schedule_constant(1.1),
        # coupling_coefficient: float = 1,
        # noise_magnitude: float = 0.001,
    ) -> None:

        # model = Ising(weight_matrix * coupling_coefficient)
        self.model = Ising(weight_matrix)
        self.solver = solver(**kwargs)

    def solve(self, **kwargs):
        self.solver.solve(self.model, **kwargs)
    