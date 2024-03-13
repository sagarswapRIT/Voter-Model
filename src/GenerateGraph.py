import networkx as nx
import pandas as pd


num_nodes = 50000
num_edges = 171002
average_degree=10
# Calculate the probability parameter 'p' for the Erdős-Rényi graph formula
#probability = num_edges / (num_nodes * (num_nodes - 1) / 2) #For number of edges
probability = average_degree / (num_nodes-1)

G=nx.erdos_renyi_graph(num_nodes, probability, seed=None, directed=False)
print(G)
nx.write_edgelist(G, "./data/input/ErdosReyni_N50000.txt", delimiter=' ', encoding='utf-8', data=False)
print(nx.degree_histogram(G))