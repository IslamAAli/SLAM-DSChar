import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

dirname = os.path.dirname(__file__)+'/..'

filenames1 = [
'../out_data/reports/EURO_C/[CONTRAST_CR]EURO_C_MH_01_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_CR]EURO_C_MH_02_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_CR]EURO_C_MH_03_medium.txt'
,'../out_data/reports/EURO_C/[CONTRAST_CR]EURO_C_MH_04_difficult.txt'
,'../out_data/reports/EURO_C/[CONTRAST_CR]EURO_C_MH_05_difficult.txt'
,'../out_data/reports/EURO_C/[CONTRAST_CR]EURO_C_V1_01_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_CR]EURO_C_V1_02_medium.txt'
,'../out_data/reports/EURO_C/[CONTRAST_CR]EURO_C_V1_03_difficult.txt'
,'../out_data/reports/EURO_C/[CONTRAST_CR]EURO_C_V2_01_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_CR]EURO_C_V2_02_medium.txt'
,'../out_data/reports/EURO_C/[CONTRAST_CR]EURO_C_V2_03_difficult.txt'
]

filenames2 = [
'../out_data/reports/EURO_C/[CONTRAST_WEBER]EURO_C_MH_01_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_WEBER]EURO_C_MH_02_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_WEBER]EURO_C_MH_03_medium.txt'
,'../out_data/reports/EURO_C/[CONTRAST_WEBER]EURO_C_MH_04_difficult.txt'
,'../out_data/reports/EURO_C/[CONTRAST_WEBER]EURO_C_MH_05_difficult.txt'
,'../out_data/reports/EURO_C/[CONTRAST_WEBER]EURO_C_V1_01_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_WEBER]EURO_C_V1_02_medium.txt'
,'../out_data/reports/EURO_C/[CONTRAST_WEBER]EURO_C_V1_03_difficult.txt'
,'../out_data/reports/EURO_C/[CONTRAST_WEBER]EURO_C_V2_01_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_WEBER]EURO_C_V2_02_medium.txt'
,'../out_data/reports/EURO_C/[CONTRAST_WEBER]EURO_C_V2_03_difficult.txt'
]

filenames3 = [
'../out_data/reports/EURO_C/[CONTRAST_MICHELSON]EURO_C_MH_01_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_MICHELSON]EURO_C_MH_02_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_MICHELSON]EURO_C_MH_03_medium.txt'
,'../out_data/reports/EURO_C/[CONTRAST_MICHELSON]EURO_C_MH_04_difficult.txt'
,'../out_data/reports/EURO_C/[CONTRAST_MICHELSON]EURO_C_MH_05_difficult.txt'
,'../out_data/reports/EURO_C/[CONTRAST_MICHELSON]EURO_C_V1_01_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_MICHELSON]EURO_C_V1_02_medium.txt'
,'../out_data/reports/EURO_C/[CONTRAST_MICHELSON]EURO_C_V1_03_difficult.txt'
,'../out_data/reports/EURO_C/[CONTRAST_MICHELSON]EURO_C_V2_01_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_MICHELSON]EURO_C_V2_02_medium.txt'
,'../out_data/reports/EURO_C/[CONTRAST_MICHELSON]EURO_C_V2_03_difficult.txt'
]

filenames4 = [
'../out_data/reports/EURO_C/[CONTRAST_RMS]EURO_C_MH_01_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_RMS]EURO_C_MH_02_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_RMS]EURO_C_MH_03_medium.txt'
,'../out_data/reports/EURO_C/[CONTRAST_RMS]EURO_C_MH_04_difficult.txt'
,'../out_data/reports/EURO_C/[CONTRAST_RMS]EURO_C_MH_05_difficult.txt'
,'../out_data/reports/EURO_C/[CONTRAST_RMS]EURO_C_V1_01_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_RMS]EURO_C_V1_02_medium.txt'
,'../out_data/reports/EURO_C/[CONTRAST_RMS]EURO_C_V1_03_difficult.txt'
,'../out_data/reports/EURO_C/[CONTRAST_RMS]EURO_C_V2_01_easy.txt'
,'../out_data/reports/EURO_C/[CONTRAST_RMS]EURO_C_V2_02_medium.txt'
,'../out_data/reports/EURO_C/[CONTRAST_RMS]EURO_C_V2_03_difficult.txt'
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

data1 = []
for filename in filenames1:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data1.append(list(map(float, lines)))

data2 = []
fig = plt.figure(figsize =(10, 7))
for filename in filenames2:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data2.append(list(map(float, lines)))

data3 = []
for filename in filenames3:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data3.append(list(map(float, lines)))

data4 = []
fig = plt.figure(figsize =(10, 7))
for filename in filenames4:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data4.append(list(map(float, lines)))


empty_labels= [''] * len(dlabels)

# Creating plot
plt.subplot(221)
plt.boxplot(data1, labels=dlabels, vert=False)
plt.grid('major', axis='y')
plt.ylabel('Sequence')
plt.xlabel('CR Contrast Score')

# Creating plot
plt.subplot(222)
plt.boxplot(data2, labels=empty_labels, vert=False)
plt.grid('major', axis='y')
plt.xlabel('Weber Contrast Score')

# Creating plot
plt.subplot(223)
plt.boxplot(data3, labels=dlabels, vert=False)
plt.grid('major', axis='y')
plt.ylabel('Sequence')
plt.xlabel('Michelson Contrast Score')

# Creating plot
plt.subplot(224)
plt.boxplot(data4, labels=empty_labels, vert=False)
plt.grid('major', axis='y')
plt.xlabel('RMS Contrast Score')


plt.tight_layout()
plt.savefig(dirname+"/../out_data/agg_figs/EuroC_contrast.png",bbox_inches='tight')
plt.show()