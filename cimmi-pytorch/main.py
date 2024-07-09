
from cim import CIM
from solvers import SG3
import torch
import matplotlib.pyplot as plt

J = torch.tensor([[0.0, 1.0, 1.0], [1.0, 0.0, 1.0], [1.0, 1.0, 0.0]])

foo = CIM(-0.1 * J, solver=SG3)
print(foo.model.state)
foo.solve()
print(foo.model.state)

# fig, ax = plt.subplots()
# ax.plot(foo.model.Result.state_history)
# fig.savefig('cim.png')
