import matplotlib.pyplot as plt
import pandas as pd

filename="WattsStrogatz_N50000_p6_k10_50_158"
file=pd.read_csv(r"/home/sagarswap/Programming/Capstone/data/output/WattsStrogatzGraphs/"+filename+".txt", sep=" ")
fig=plt.figure(figsize=(10, 10))
plt.scatter(file["Frac"], file["DiscEdge"], c=file["Epoch"])
plt.xlabel("Opinion Density")
plt.ylabel("Number of Discordant Edges")
clb=plt.colorbar()
clb.ax.set_title("Epoch")
plt.savefig("/home/sagarswap/Programming/Capstone/visualizations/"+filename)
plt.show()
