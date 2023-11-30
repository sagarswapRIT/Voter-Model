import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

#data=pd.read_csv("./data/summaryOutput/summary_facebook.csv", delimiter=",")

data10=[0.6103, 0.658084, 0.514979, 0.749691, 0.508047]
data20=[0.68309, 0.531072, 0.664769, 0.56821, 0.682347]
#data20=[0.733066, 0.741611, 0.812016, 0.753182, 0.771473, 0.75514]
data30=[0.814063, 0.866799, 0.679624, 0.66774, 0.697697, 0.832632, 0.743253]
data40=[0.710572, 0.61946, 0.588017, 0.644219, 0.623669, 0.521911]
data50=[0.608566, 0.599901, 0.721961, 0.527358, 0.831641, 0.676405]
#data50=[0.76413, 0.74664, 0.642902, 0.749088, 0.747219]
data60=[0.636791, 0.84204,0.887101, 0.626393, 0.694231, 0.766031]
data70=[0.680119, 0.645704, 0.653627, 0.618718, 0.700421]
data80=[0.726417, 0.58158, 0.733597, 0.748948, 0.659074, 0.616737]
#data80=[0.686471, 0.66769, 0.711749, 0.666266, ]
data90=[0.688784, 0.641, 0.831889, 0.602624, 0.769002]

my_dict={'0.1':data10, '0.2':data20, '0.3':data30, '0.4':data40, '0.5':data50, '0.6':data60, '0.7':data70, '0.8':data80, '0.9':data90}

fig, ax = plt.subplots()
ax.boxplot(my_dict.values())
ax.set_xticklabels(my_dict.keys())
ax.set_xlabel("Rewiring Rate")
ax.set_ylabel("Majority Opinion Density")
plt.show()