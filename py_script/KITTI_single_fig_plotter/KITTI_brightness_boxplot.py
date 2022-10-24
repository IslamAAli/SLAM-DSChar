import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

dirname = os.path.dirname(__file__)+'/..'

filenames = [   '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_00.txt', 
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_01.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_02.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_03.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_04.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_05.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_06.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_07.txt', 
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_08.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_09.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_10.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_11.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_12.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_13.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_14.txt', 
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_15.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_16.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_17.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_18.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_19.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_20.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_20.txt']

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
for filename in filenames:
    fn = os.path.join(dirname, filename)
    with open(fn) as f:
        lines = f.read().splitlines()

    data.append(list(map(float, lines)))
    
# Creating plot
plt.boxplot(data, labels=dlabels, vert=False)
# plt.violinplot(data)
plt.grid('major', axis='y')
plt.ylabel('Sequence')
plt.xlabel('Brightness Score')
plt.tight_layout()
# show plot
plt.show()