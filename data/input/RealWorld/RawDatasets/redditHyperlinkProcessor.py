import os
import pandas  as pd

file_path="./data/input/RealWorld/RawDatasets/redditHyperlinks.tsv"
data=pd.read_csv(file_path, sep="\t")
data=data[['SOURCE_SUBREDDIT', 'TARGET_SUBREDDIT']]
mappedData=[]
nodes=0
edges=0
dictio=dict()

for index, row, in data.iterrows():
    src=row['SOURCE_SUBREDDIT']
    dst=row['TARGET_SUBREDDIT']
    s=-1
    d=-1
    if src in dictio:
        s=dictio[src]
    else:
        dictio[src]=nodes
        s=nodes
        nodes=nodes+1
    if dst in dictio:
        d=dictio[dst]
    else:
        dictio[dst]=nodes
        d=nodes
        nodes=nodes+1
    l=list([s, d])
    mappedData.append(l)
    edges=edges+1

#print(mappedData)

with open('./data/input/RealWorld/redditHyperlink.txt', 'w') as f:
    f.writelines([str(nodes),' ', str(edges), '\n'])
    for md in mappedData:
        f.writelines([str(md[0]), ' ', str(md[1]), '\n'])