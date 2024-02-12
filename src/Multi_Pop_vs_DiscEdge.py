import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

folder_path = "./data/output/GT3"
files=os.listdir(folder_path)
fig=plt.figure()
ax=fig.add_subplot(111)
d0=False
d1=False
d2=False
d3=False
d4=False
d5=False
d6=False
d7=False
d8=False
d9=False
d10=False

for file in files:
    with open(os.path.join(folder_path, file), 'r') as f:
        content = pd.read_csv(folder_path+"/"+file, names=['Epoch', 'Pop', 'Frac', 'DiscEdge'], skiprows=1, sep=" ")
        # if content.size>5000:
        #     content=content.head(5000)
        file=file.split('_')
        if file[1]=='0':
            if d0==False:
                ax.scatter(content['Frac'], content['DiscEdge'], c='brown', label='0.0', s=1)
                d0=True
            else:
                ax.scatter(content['Frac'], content['DiscEdge'], c='brown', s=1)
        elif file[1]=='10':
            if d1==False:
                ax.scatter(content['Frac'], content['DiscEdge'], c='r', label='0.1', s=1)
                d1=True
            else:
                ax.scatter(content['Frac'], content['DiscEdge'], c='r', s=1)
        elif file[1]=='20':
            if d2==False:
                ax.scatter(content['Frac'], content['DiscEdge'], c='orange', label='0.2', s=1)
                d2=True
            else:
                ax.scatter(content['Frac'], content['DiscEdge'], c='orange', s=1)
        elif file[1]=='30':
            if d3==False:
                ax.scatter(content['Frac'], content['DiscEdge'], c='yellow', label='0.3', s=1)
                d3=True
            else:
                ax.scatter(content['Frac'], content['DiscEdge'], c='yellow', s=1)
        elif file[1]=='40':
            if d4==False:
                ax.scatter(content['Frac'], content['DiscEdge'], c='chartreuse', label='0.4', s=1)
                d4=True
            else:
                ax.scatter(content['Frac'], content['DiscEdge'], c='chartreuse', s=1)
        elif file[1]=='50':
            if d5==False:
                ax.scatter(content['Frac'], content['DiscEdge'], c='g', label='0.5', s=1)
                d5=True
            else:
                ax.scatter(content['Frac'], content['DiscEdge'], c='g', s=1)
        elif file[1]=='60':
            if d6==False:
                ax.scatter(content['Frac'], content['DiscEdge'], c='paleturquoise', label='0.6', s=1)
                d6=True
            else:
                ax.scatter(content['Frac'], content['DiscEdge'], c='paleturquoise', s=1)
        elif file[1]=='70':
            if d7==False:
                ax.scatter(content['Frac'], content['DiscEdge'], c='dodgerblue', label='0.7', s=1)
                d7=True
            else:
                ax.scatter(content['Frac'], content['DiscEdge'], c='dodgerblue', s=1)
        elif file[1]=='80':
            if d8==False:
                ax.scatter(content['Frac'], content['DiscEdge'], c='blueviolet', label='0.8', s=1)
                d8=True
            else:
                ax.scatter(content['Frac'], content['DiscEdge'], c='blueviolet', s=1)
        elif file[1]=='90':
            if d9==False:
                ax.scatter(content['Frac'], content['DiscEdge'], c='magenta', label='0.9', s=1)
                d9=True
            else:
                ax.scatter(content['Frac'], content['DiscEdge'], c='magenta', s=1)
        elif file[1]=='100':
            if d10==False:
                ax.scatter(content['Frac'], content['DiscEdge'], c='black', label='1.0', s=1)
                d10=True
            else:
                ax.scatter(content['Frac'], content['DiscEdge'], c='black', s=1)

plt.xlabel("Opinion Density")
plt.ylabel("Number of Discordant Edges (l01)")
plt.legend(loc='upper right')
plt.show()