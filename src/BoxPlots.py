import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import os

folder_path = "./data/output/GT3/"
files=os.listdir(folder_path)

data0=[]
data10=[]
data20=[]
data30=[]
data40=[]
data50=[]
data60=[]
data70=[]
data80=[]
data90=[]
data100=[]

for file in files:
    with open(os.path.join(folder_path, file), 'r') as f:
        content = pd.read_csv(folder_path+"/"+file, names=['Epoch', 'Pop', 'Frac', 'DiscEdge'], skiprows=1, sep=" ")
        file=file.split('_')
        content=content.drop(['Epoch', 'Pop'], axis=1)    
        last_row_content=content.iloc[-1, 0]
        if last_row_content<0.5:
            last_row_content=1-last_row_content
        if file[1]=='0':
            data0.append(float(last_row_content))
        elif file[1]=='10':
            data10.append(float(last_row_content))
        elif file[1]=='20':
            data20.append(float(last_row_content))
        elif file[1]=='30':
            data30.append(float(last_row_content))
        elif file[1]=='40':
            data40.append(float(last_row_content))
        elif file[1]=='50':
            data50.append(float(last_row_content))
        elif file[1]=='60':
            data60.append(float(last_row_content))
        elif file[1]=='70':
            data70.append(float(last_row_content))
        elif file[1]=='80':
            data80.append(float(last_row_content))
        elif file[1]=='90':
            data90.append(float(last_row_content))
        elif file[1]=='100':
            data100.append(float(last_row_content))

my_dict={'0.0':data0, '0.1':data10, '0.2':data20, '0.3':data30, '0.4':data40, '0.5':data50, '0.6':data60, '0.7':data70, '0.8':data80, '0.9':data90, '1.0':data100}
print(my_dict)

fig, ax = plt.subplots()
ax.boxplot(my_dict.values())
ax.set_xticklabels(my_dict.keys())
ax.set_xlabel("Rewiring Rate")
ax.set_ylabel("Majority Opinion Density")
plt.show()