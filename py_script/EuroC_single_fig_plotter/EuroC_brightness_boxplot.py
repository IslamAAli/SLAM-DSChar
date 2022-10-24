import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

dirname = os.path.dirname(__file__)+'/..'

filenames = [
'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_MH_01_easy.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_MH_02_easy.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_MH_03_medium.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_MH_04_difficult.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_MH_05_difficult.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_V1_01_easy.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_V1_02_medium.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_V1_03_difficult.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_V2_01_easy.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_V2_02_medium.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_V2_03_difficult.txt'
]

dlabels = [
'MH_01_easy'
,'MH_02_easy'
,'MH_03_medium'
,'MH_04_difficult'
,'MH_05_difficult'
,'V1_01_easy'
,'V1_02_medium'
,'V1_03_difficult'
,'V2_01_easy'
,'V2_02_medium'
,'V2_03_difficult'
]


data = []
for filename in filenames:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data.append(list(map(float, lines)))
    
# Creating plot
plt.subplot(2,2,1)
plt.boxplot(data, labels=dlabels, vert=False)
# plt.violinplot(data)
plt.grid('major', axis='x')
plt.ylabel('Sequence')
plt.xlabel('Brightness Score')
plt.tight_layout()
plt.show()