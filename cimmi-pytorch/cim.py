

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
        init_state = None,
        **kwargs,
        # pump_schedule: Callable[[float], float] = schedule_constant(1.1),
        # coupling_coefficient: float = 1,
        # noise_magnitude: float = 0.001,
    ) -> None:

        # model = Ising(weight_matrix * coupling_coefficient)
        self.saved_init_state = init_state
        self.model = Ising(weight_matrix, init_state=self.saved_init_state)
        self.solver = solver(**kwargs)

    def solve(self, **kwargs):
        self.model.set_state(self.saved_init_state)
        self.model.result.state_history = []
        self.model.result.energy_history = []
        self.model.result.minimum_energy = float('inf')
        self.model.result.minimum_energy_state = None
        self.solver.solve(self.model, **kwargs)
    