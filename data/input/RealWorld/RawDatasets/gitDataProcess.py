import pandas as pd

file_path="./data/input/RealWorld/RawDatasets/GitInteractions.csv"
output_path="./data/input/RealWorld/gitInteractions.txt"

data=pd.read_csv(file_path, sep=',')
print(data)

maxNode=-1
edges=0
dat=[]

for index, row in data.iterrows():
    src=row['id_1']
    dst=row['id_2']
    maxNode=max(maxNode, src, dst)
    edges=edges+1
    l=list([src, dst])
    dat.append(l)
    
with open(output_path, 'w') as f:
    f.writelines([str(maxNode+1), ' ', str(edges), '\n'])
    for md in dat:
        f.writelines([str(md[0]), ' ', str(md[1]), '\n'])
