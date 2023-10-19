import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

file=pd.read_csv(r"./Voter-Model/data/output/facebook_medium_100_812.txt", sep=" ")
fig=plt.figure(figsize=(10, 10))
plt.scatter(file["Pop"], file["DiscEdge"], c=file["Epoch"])
plt.xlabel("Opinion Density")
plt.ylabel("Number of Discordant Edges")
clb=plt.colorbar()
clb.ax.set_title("Epoch")
plt.show()
