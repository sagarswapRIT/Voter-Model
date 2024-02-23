import os
import pandas as pd
import numpy as np


# specify the path to the folder containing the files
folder_path = "./data/output/facebook2/"

# list all the files in the folder
files = os.listdir(folder_path)

# iterate over each file and read its content
fileno=1
df=pd.DataFrame()
for file in files:
    with open(os.path.join(folder_path, file), 'r') as f:
        content = pd.read_csv(folder_path+"/"+file, names=['Epoch', 'Pop', 'Frac'+str(fileno), 'DiscEdge'+str(fileno)], skiprows=1, sep=" ")
        content=content.drop(['Epoch', 'Pop'], axis=1)    
        last_row_content=content.iloc[-1, 0]
        if last_row_content<0.5:
            content['Frac'+str(fileno)]=1-content['Frac'+str(fileno)]
        row, col=content.shape
        #print(f"File Name: {file}\nContent: {content}\n")
        file=file.split("_")

        if last_row_content<0.5:
            print(file[1], '%', 1-last_row_content)
        else:
            print(file[1], '%', last_row_content)


        ncol=np.ones(row, dtype=int)
        ncol.fill(file[1])
        ncol=pd.DataFrame(ncol, columns=['Rewire'+str(fileno)])
        content=pd.merge(content, ncol, left_index=True, right_index=True)
        #print(content)
    fileno=fileno+1
    df=pd.merge(df, content, left_index=True, right_index=True, how='outer')
df.to_csv('./data/summaryOutput/summary_facebook2.csv')