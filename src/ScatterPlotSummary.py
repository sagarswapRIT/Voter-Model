import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

file=pd.read_csv(r"/home/sagarswap/Programming/Capstone/data/output/summary.txt", sep=" ")
file["y"]=np.where(file["y"]<0.5, 1-file["y"], file["y"])
print(file)
plt.scatter(file["x"], file["y"])
plt.ylabel("Opinion Density")
plt.xlabel("Rewiring Probability")
plt.show()