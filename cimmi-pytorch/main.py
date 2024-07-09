
from cim import CIM
from solvers import SG3
from graphs import read_graph_from_rudy, eval_max_cut
from schedules import schedule_linear
import torch
import numpy as np
import matplotlib.pyplot as plt

# J = torch.tensor([[0.0, 1.0, 1.0], [1.0, 0.0, 1.0], [1.0, 1.0, 0.0]])
J = read_graph_from_rudy("../scripts/biqmac/graphs/rudy/pm1s_80.0")

foo = CIM(-0.1 * J, solver=SG3)
foo.solve()
print(foo.model.state)
print("SG3:", eval_max_cut(foo.model.state.tolist(), J))

foo = CIM(-0.00 * J)
foo.model.state += 0.001 * torch.normal(torch.zeros_like(foo.model.state), torch.ones_like(foo.model.state))
foo.solve(noise_magnitude = 0)
print(foo.model.state)
print("DOPO:", eval_max_cut(foo.model.state.tolist(), J))

fig, ax = plt.subplots()
ax.plot(foo.model.Result.state_history)
fig.savefig('cim.png')
