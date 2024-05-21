import cimmi

s = cimmi.simulator(5)
print(s.get_x())

g = cimmi.Graph.read_from_file('../scripts/rudy/test_graphs/complete_5.in')
