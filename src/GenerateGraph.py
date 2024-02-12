import networkx as nx
import pandas as pd

G=nx.erdos_renyi_graph(25000, 0.001, seed=None, directed=False)
print(G)
nx.write_edgelist(G, "./data/input/GT3.txt", delimiter=' ', encoding='utf-8', data=False)
print(nx.degree_histogram(G))