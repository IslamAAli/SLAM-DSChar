import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

dirname = os.path.dirname(__file__)+'/..'

filenames1 = [
'../out_data/reports/EURO_C/[REVISIT_SCORE]EURO_C_MH_01_easy.txt'
,'../out_data/reports/EURO_C/[REVISIT_SCORE]EURO_C_MH_02_easy.txt'
,'../out_data/reports/EURO_C/[REVISIT_SCORE]EURO_C_MH_03_medium.txt'
,'../out_data/reports/EURO_C/[REVISIT_SCORE]EURO_C_MH_04_difficult.txt'
,'../out_data/reports/EURO_C/[REVISIT_SCORE]EURO_C_MH_05_difficult.txt'
,'../out_data/reports/EURO_C/[REVISIT_SCORE]EURO_C_V1_01_easy.txt'
,'../out_data/reports/EURO_C/[REVISIT_SCORE]EURO_C_V1_02_medium.txt'
,'../out_data/reports/EURO_C/[REVISIT_SCORE]EURO_C_V1_03_difficult.txt'
,'../out_data/reports/EURO_C/[REVISIT_SCORE]EURO_C_V2_01_easy.txt'
,'../out_data/reports/EURO_C/[REVISIT_SCORE]EURO_C_V2_02_medium.txt'
,'../out_data/reports/EURO_C/[REVISIT_SCORE]EURO_C_V2_03_difficult.txt'
]

filenames2 = [
'../out_data/reports/EURO_C/[REVISIT_DIST]EURO_C_MH_01_easy.txt'
,'../out_data/reports/EURO_C/[REVISIT_DIST]EURO_C_MH_02_easy.txt'
,'../out_data/reports/EURO_C/[REVISIT_DIST]EURO_C_MH_03_medium.txt'
,'../out_data/reports/EURO_C/[REVISIT_DIST]EURO_C_MH_04_difficult.txt'
,'../out_data/reports/EURO_C/[REVISIT_DIST]EURO_C_MH_05_difficult.txt'
,'../out_data/reports/EURO_C/[REVISIT_DIST]EURO_C_V1_01_easy.txt'
,'../out_data/reports/EURO_C/[REVISIT_DIST]EURO_C_V1_02_medium.txt'
,'../out_data/reports/EURO_C/[REVISIT_DIST]EURO_C_V1_03_difficult.txt'
,'../out_data/reports/EURO_C/[REVISIT_DIST]EURO_C_V2_01_easy.txt'
,'../out_data/reports/EURO_C/[REVISIT_DIST]EURO_C_V2_02_medium.txt'
,'../out_data/reports/EURO_C/[REVISIT_DIST]EURO_C_V2_03_difficult.txt'
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


empty_labels= [''] * len(dlabels)

data1 = []
for filename in filenames1:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data1.append(list(map(float, lines)))
# ============================================
data2 = []
for filename in filenames2:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data2.append(list(map(float, lines)))
# ============================================
fig1 = plt.figure('EuroC Revisit')
fig1.set_size_inches([8,6])
plt.subplot(211)
plt.boxplot(data1, labels=dlabels, showmeans=True)
plt.grid('major', axis='x')
plt.xlabel('Sequence')
plt.ylabel('Closeset Match Similarity Score')
plt.xticks(rotation=-45)

plt.subplot(212)
plt.boxplot(data2, labels=dlabels, showmeans=True)
plt.grid('major', axis='x')
plt.xlabel('Sequence')
plt.ylabel('Distance to Closest Match (Frames)')
plt.xticks(rotation=-45)

plt.tight_layout()
plt.savefig(dirname+"/../out_data/agg_figs/EuroC_revisit.png",bbox_inches='tight')
plt.show()