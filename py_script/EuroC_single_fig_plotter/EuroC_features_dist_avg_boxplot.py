import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

dirname = os.path.dirname(__file__)+'/..'

filenames1 = [
'../out_data/reports/EURO_C/[SIFT_DIST_AVG]EURO_C_MH_01_easy.txt'
,'../out_data/reports/EURO_C/[SIFT_DIST_AVG]EURO_C_MH_02_easy.txt'
,'../out_data/reports/EURO_C/[SIFT_DIST_AVG]EURO_C_MH_03_medium.txt'
,'../out_data/reports/EURO_C/[SIFT_DIST_AVG]EURO_C_MH_04_difficult.txt'
,'../out_data/reports/EURO_C/[SIFT_DIST_AVG]EURO_C_MH_05_difficult.txt'
,'../out_data/reports/EURO_C/[SIFT_DIST_AVG]EURO_C_V1_01_easy.txt'
,'../out_data/reports/EURO_C/[SIFT_DIST_AVG]EURO_C_V1_02_medium.txt'
,'../out_data/reports/EURO_C/[SIFT_DIST_AVG]EURO_C_V1_03_difficult.txt'
,'../out_data/reports/EURO_C/[SIFT_DIST_AVG]EURO_C_V2_01_easy.txt'
,'../out_data/reports/EURO_C/[SIFT_DIST_AVG]EURO_C_V2_02_medium.txt'
,'../out_data/reports/EURO_C/[SIFT_DIST_AVG]EURO_C_V2_03_difficult.txt'
]

filenames2 = [
'../out_data/reports/EURO_C/[FAST_DIST_AVG]EURO_C_MH_01_easy.txt'
,'../out_data/reports/EURO_C/[FAST_DIST_AVG]EURO_C_MH_02_easy.txt'
,'../out_data/reports/EURO_C/[FAST_DIST_AVG]EURO_C_MH_03_medium.txt'
,'../out_data/reports/EURO_C/[FAST_DIST_AVG]EURO_C_MH_04_difficult.txt'
,'../out_data/reports/EURO_C/[FAST_DIST_AVG]EURO_C_MH_05_difficult.txt'
,'../out_data/reports/EURO_C/[FAST_DIST_AVG]EURO_C_V1_01_easy.txt'
,'../out_data/reports/EURO_C/[FAST_DIST_AVG]EURO_C_V1_02_medium.txt'
,'../out_data/reports/EURO_C/[FAST_DIST_AVG]EURO_C_V1_03_difficult.txt'
,'../out_data/reports/EURO_C/[FAST_DIST_AVG]EURO_C_V2_01_easy.txt'
,'../out_data/reports/EURO_C/[FAST_DIST_AVG]EURO_C_V2_02_medium.txt'
,'../out_data/reports/EURO_C/[FAST_DIST_AVG]EURO_C_V2_03_difficult.txt'
]

filenames3 = [
'../out_data/reports/EURO_C/[ORB_DIST_AVG]EURO_C_MH_01_easy.txt'
,'../out_data/reports/EURO_C/[ORB_DIST_AVG]EURO_C_MH_02_easy.txt'
,'../out_data/reports/EURO_C/[ORB_DIST_AVG]EURO_C_MH_03_medium.txt'
,'../out_data/reports/EURO_C/[ORB_DIST_AVG]EURO_C_MH_04_difficult.txt'
,'../out_data/reports/EURO_C/[ORB_DIST_AVG]EURO_C_MH_05_difficult.txt'
,'../out_data/reports/EURO_C/[ORB_DIST_AVG]EURO_C_V1_01_easy.txt'
,'../out_data/reports/EURO_C/[ORB_DIST_AVG]EURO_C_V1_02_medium.txt'
,'../out_data/reports/EURO_C/[ORB_DIST_AVG]EURO_C_V1_03_difficult.txt'
,'../out_data/reports/EURO_C/[ORB_DIST_AVG]EURO_C_V2_01_easy.txt'
,'../out_data/reports/EURO_C/[ORB_DIST_AVG]EURO_C_V2_02_medium.txt'
,'../out_data/reports/EURO_C/[ORB_DIST_AVG]EURO_C_V2_03_difficult.txt'
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
fig = plt.figure('EuroC_SIFT-DIST_AVG_boxplot', figsize =(10, 7))
for filename in filenames1:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data.append(list(map(float, lines)))
    
# Creating plot
plt.boxplot(data, labels=dlabels, showmeans=True)
plt.grid('major', axis='x')
plt.xlabel('Sequence')
plt.ylabel('% Spatial Features Distribution')
plt.show()

# ============================================

data = []
fig = plt.figure('EuroC_FAST-DIST_AVG_boxplot', figsize =(10, 7))
for filename in filenames2:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data.append(list(map(float, lines)))
    
# Creating plot
plt.boxplot(data, labels=dlabels, showmeans=True)
plt.grid('major', axis='x')
plt.xlabel('Sequence')
plt.ylabel('% Spatial Features Distribution')
plt.show()

# ============================================

data = []
fig = plt.figure('EuroC_ORB-DIST_AVG_boxplot', figsize =(10, 7))
for filename in filenames3:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data.append(list(map(float, lines)))
    
# Creating plot
plt.boxplot(data, labels=dlabels, showmeans=True)
plt.grid('major', axis='x')
plt.xlabel('Sequence')
plt.ylabel('% Spatial Features Distribution')
plt.show()