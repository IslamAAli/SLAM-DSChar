import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

dirname = os.path.dirname(__file__)+'/..'

filenames = [
'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_00.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_01.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_02.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_03.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_04.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_05.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_06.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_07.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_08.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_09.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_10.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_11.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_12.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_13.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_14.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_15.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_16.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_17.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_18.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_19.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_20.txt'
,'../out_data/reports/KITTI/[CONTRAST_CR]KITTI_21.txt'
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
fig = plt.figure(figsize =(10, 7))
for filename in filenames:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data.append(list(map(float, lines)))
    
# Creating plot
plt.boxplot(data, labels=dlabels, showmeans=True)
# plt.violinplot(data)
plt.grid('major', axis='x')
plt.xlabel('Sequence')
plt.ylabel('Contrast Score')
# show plot
plt.show()