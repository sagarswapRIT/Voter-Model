import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

data=pd.read_csv("./data/summaryOutput/summary_facebook.csv", delimiter=",")
fig=plt.figure()
print(data.shape[1])
x=[0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
for fileno in range(1, 51):
    if data['Rewire'+str(fileno)][1]==10:
        color='C1'
    elif data['Rewire'+str(fileno)][1]==20:
        color='C2'
    elif data['Rewire'+str(fileno)][1]==30:
        color='C3'
    elif data['Rewire'+str(fileno)][1]==40:
        color='C4'
    elif data['Rewire'+str(fileno)][1]==50:
        color='C5'
    elif data['Rewire'+str(fileno)][1]==60:
        color='C6'
    elif data['Rewire'+str(fileno)][1]==70:
        color='C7'
    elif data['Rewire'+str(fileno)][1]==80:
        color='C8'
    elif data['Rewire'+str(fileno)][1]==90:
        color='C9'
    if fileno==1:
        ax=fig.add_subplot(111, label=str(fileno))
        ax.plot(data['Frac'+str(fileno)], data['DiscEdge'+str(fileno)], color=color)
        ax.set_xlabel("Majority Opinion Density")
        ax.set_ylabel("Discordant Edges")
    else:
        ax=fig.add_subplot(111, label=str(fileno), frame_on=False)
        ax.plot(data['Frac'+str(fileno)], data['DiscEdge'+str(fileno)], color=color)
plt.xticks(x)
plt.show()