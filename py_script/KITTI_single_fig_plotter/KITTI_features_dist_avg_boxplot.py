import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

dirname = os.path.dirname(__file__)+'/..'

filenames1 = [
'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_00.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_01.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_02.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_03.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_04.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_05.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_06.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_07.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_08.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_09.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_10.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_11.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_12.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_13.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_14.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_15.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_16.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_17.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_18.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_19.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_20.txt'
,'../out_data/reports/KITTI/[SIFT_DIST_AVG]KITTI_21.txt'
]

filenames2 = [
'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_00.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_01.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_02.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_03.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_04.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_05.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_06.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_07.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_08.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_09.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_10.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_11.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_12.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_13.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_14.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_15.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_16.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_17.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_18.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_19.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_20.txt'
,'../out_data/reports/KITTI/[FAST_DIST_AVG]KITTI_21.txt'
]

filenames3 = [
'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_00.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_01.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_02.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_03.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_04.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_05.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_06.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_07.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_08.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_09.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_10.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_11.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_12.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_13.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_14.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_15.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_16.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_17.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_18.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_19.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_20.txt'
,'../out_data/reports/KITTI/[ORB_DIST_AVG]KITTI_21.txt'
]

dlabels = [  '00',
            '01',
            '02',
            '03',
            '04',
            '05',
            '06',
            '07',
            '08',
            '09',
            '10',
            '11',
            '12',
            '13',
            '14',
            '15',
            '16',
            '17',
            '18',
            '19',
            '20',
            '21']


data = []
fig = plt.figure('KITTI_SIFT-_DIST_AVG_boxplot', figsize =(10, 7))
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
fig = plt.figure('KITTI_FAST-_DIST_AVG_boxplot', figsize =(10, 7))
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
fig = plt.figure('KITTI_ORB-_DIST_AVG_boxplot', figsize =(10, 7))
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