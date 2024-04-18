import pandas as pd

file_path="./data/input/RealWorld/RawDatasets/twitch/"
filename=["DE/musae_DE_edges.csv", "ENGB/musae_ENGB_edges.csv", "ES/musae_ES_edges.csv", "FR/musae_FR_edges.csv", "PTBR/musae_PTBR_edges.csv", "RU/musae_RU_edges.csv"]
output_path="./data/input/RealWorld/"
outputname={"DE/musae_DE_edges.csv":"twitch_DE.txt", "ENGB/musae_ENGB_edges.csv":"Twitch_ENGB.txt", "ES/musae_ES_edges.csv":"twitch_ES.txt", "FR/musae_FR_edges.csv":"twitch_FR.txt", "PTBR/musae_PTBR_edges.csv":"twitch_PTBR.txt", "RU/musae_RU_edges.csv":"twitch_RU.txt"}

for fileN in filename:
    data=pd.read_csv(file_path+fileN, sep=',')
    print(fileN)
    print(data)

    maxNode=-1
    edges=0
    dat=[]

    for index, row in data.iterrows():
        src=row['from']
        dst=row['to']
        maxNode=max(maxNode, src, dst)
        edges=edges+1
        l=list([src, dst])
        dat.append(l)
    
    with open(output_path+outputname[fileN], 'w') as f:
        f.writelines([str(maxNode+1), ' ', str(edges), '\n'])
        for md in dat:
            f.writelines([str(md[0]), ' ', str(md[1]), '\n'])
