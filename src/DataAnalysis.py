import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

file=pd.read_csv(r"./Voter-Model/data/output.txt", sep=" ")
print(file)
pop1=file['Pop1']
pop2=file['Pop2']
fig, ax1 =plt.subplots()
ax1.plot(pop1, color='blue')
ax2=ax1.twinx()
ax2.plot(pop2, color='red')
#plt.plot(pop1)
plt.show()