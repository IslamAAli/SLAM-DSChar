import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

dirname = os.path.dirname(__file__)+'/..'

filenames1 = [
'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_00.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_01.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_02.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_03.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_04.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_05.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_06.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_07.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_08.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_09.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_10.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_11.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_12.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_13.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_14.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_15.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_16.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_17.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_18.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_19.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_20.txt'
,'../out_data/reports/KITTI/[REVISIT_SCORE]KITTI_21.txt'
]

filenames2 = [
'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_00.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_01.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_02.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_03.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_04.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_05.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_06.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_07.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_08.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_09.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_10.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_11.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_12.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_13.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_14.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_15.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_16.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_17.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_18.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_19.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_20.txt'
,'../out_data/reports/KITTI/[REVISIT_DIST]KITTI_21.txt'
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
fig1 = plt.figure('KITTI Revisit')
fig1.set_size_inches([8,6])
plt.subplot(211)
plt.boxplot(data1, labels=dlabels, showmeans=True)
plt.grid('major', axis='x')
plt.xlabel('Sequence')
plt.ylabel('Closeset Match Similarity Score')

plt.subplot(212)
plt.boxplot(data2, labels=dlabels, showmeans=True)
plt.grid('major', axis='x')
plt.xlabel('Sequence')
plt.ylabel('Distance to Closest Match (Frames)')

plt.tight_layout()
plt.savefig(dirname+"/../out_data/agg_figs/KITTI_revisit.png",bbox_inches='tight')
plt.show()