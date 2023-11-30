import networkx as nx
import pandas as pd

G=nx.erdos_renyi_graph(8000, 0.0001, seed=None, directed=False)
print(G)
nx.write_edgelist(G, "./data/input/createdGraph.txt", delimiter=' ', encoding='utf-8', data=False)
print(nx.degree_histogram(G))