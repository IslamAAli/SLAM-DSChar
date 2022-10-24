import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

dirname = os.path.dirname(__file__)+'/..'

filenames1 = [
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

filenames2 = [
'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_00.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_01.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_02.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_03.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_04.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_05.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_06.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_07.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_08.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_09.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_10.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_11.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_12.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_13.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_14.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_15.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_16.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_17.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_18.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_19.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_20.txt'
,'../out_data/reports/KITTI/[CONTRAST_WEBER]KITTI_21.txt'
]

filenames3 = [
'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_00.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_01.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_02.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_03.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_04.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_05.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_06.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_07.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_08.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_09.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_10.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_11.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_12.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_13.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_14.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_15.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_16.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_17.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_18.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_19.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_20.txt'
,'../out_data/reports/KITTI/[CONTRAST_MICHELSON]KITTI_21.txt'
]

filenames4 = [
'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_00.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_01.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_02.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_03.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_04.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_05.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_06.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_07.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_08.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_09.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_10.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_11.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_12.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_13.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_14.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_15.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_16.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_17.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_18.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_19.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_20.txt'
,'../out_data/reports/KITTI/[CONTRAST_RMS]KITTI_21.txt'
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
plt.savefig(dirname+"/../out_data/agg_figs/KITTI_contrast.png",bbox_inches='tight')
plt.show()