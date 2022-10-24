import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

dirname = os.path.dirname(__file__)+'/..'

filenames1 = [
'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_00.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_01.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_02.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_03.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_04.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_05.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_06.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_07.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_08.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_09.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_10.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_11.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_12.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_13.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_14.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_15.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_16.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_17.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_18.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_19.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_20.txt'
,'../out_data/reports/KITTI/[SIFT_COUNT]KITTI_21.txt'
]

filenames2 = [
'../out_data/reports/KITTI/[FAST_COUNT]KITTI_00.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_01.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_02.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_03.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_04.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_05.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_06.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_07.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_08.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_09.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_10.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_11.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_12.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_13.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_14.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_15.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_16.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_17.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_18.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_19.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_20.txt'
,'../out_data/reports/KITTI/[FAST_COUNT]KITTI_21.txt'
]

filenames3 = [
'../out_data/reports/KITTI/[ORB_COUNT]KITTI_00.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_01.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_02.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_03.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_04.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_05.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_06.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_07.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_08.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_09.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_10.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_11.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_12.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_13.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_14.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_15.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_16.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_17.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_18.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_19.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_20.txt'
,'../out_data/reports/KITTI/[ORB_COUNT]KITTI_21.txt'
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
fig = plt.figure('SIFT-COUNT', figsize =(10, 7))
for filename in filenames1:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data.append(list(map(float, lines)))
    
# Creating plot
plt.boxplot(data, labels=dlabels, showmeans=True)
plt.grid('major', axis='x')
plt.xlabel('Sequence')
plt.ylabel('# Visual Features')
plt.show()

# ============================================

data = []
fig = plt.figure('FAST-COUNT', figsize =(10, 7))
for filename in filenames2:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data.append(list(map(float, lines)))
    
# Creating plot
plt.boxplot(data, labels=dlabels, showmeans=True)
plt.grid('major', axis='x')
plt.xlabel('Sequence')
plt.ylabel('# Visual Features')
plt.show()

# ============================================

data = []
fig = plt.figure('ORB-COUNT', figsize =(10, 7))
for filename in filenames3:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data.append(list(map(float, lines)))
    
# Creating plot
plt.boxplot(data, labels=dlabels, showmeans=True)
plt.grid('major', axis='x')
plt.xlabel('Sequence')
plt.ylabel('# Visual Features')
plt.show()