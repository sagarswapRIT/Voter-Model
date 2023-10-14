import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

file=pd.read_csv(r"./Voter-Model/data/output001_large.txt", sep=" ")
print(file)
pop1=file['Pop1']
frac=list(file['Frac'])
val_change=[]
for i in range(len(frac)-1):
    val_change.append(abs(frac[i]-frac[i+1]))
plt.plot(val_change, label="Change in  Fraction")
#plt.plot(pop1, label= "Population 1")
plt.legend()
plt.show()