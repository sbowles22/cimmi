import cimmi

s = cimmi.simulator(5)
print(s.get_x())

g = cimmi.Graph.read_from_file('../scripts/rudy/test_graphs/complete_2.in')
print(g)

n = cimmi.Network()
n.set_coupling_strength(1.1)
n.set_pump_rate(0.9)
n.set_noise_magnitude(0.0001)
n.set_problem(cimmi.Problem_MAX_CUT)
n.set_source(g)
n.configure()

n.set_step_size(0.01)
n.run(10)

n.disp()
