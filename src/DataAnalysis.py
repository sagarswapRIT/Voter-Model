import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

file=pd.read_csv(r"./Voter-Model/data/output.txt", sep=" ")
print(file)
pop1=file['Pop1']
pop2=file['Pop2']
plt.plot(pop1, label= "Population 1")
plt.plot(pop2, label= "Population 2")
plt.legend()
plt.show()