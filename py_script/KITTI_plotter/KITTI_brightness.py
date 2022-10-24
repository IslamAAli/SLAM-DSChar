import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

dirname = os.path.dirname(__file__)+'/..'

filenames1 = [   '../out_data/reports/KITTI/[BRIGHTNESS]KITTI_00.txt', 
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


filenames2 = [   '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_00.txt', 
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_01.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_02.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_03.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_04.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_05.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_06.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_07.txt', 
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_08.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_09.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_10.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_11.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_12.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_13.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_14.txt', 
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_15.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_16.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_17.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_18.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_19.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_20.txt',
                '../out_data/reports/KITTI/[BRIGHTNESS_DIFF]KITTI_20.txt']

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


file_path = dirname+'/../out_data/dataset_reports/KITTI/[BRIGHTNESS]barchart_data.dat'
df = pd.read_csv(file_path)
sub_df = df[['name','count', '1sigma', '2sigma', '3sigma']]

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

empty_labels= [''] * len(dlabels)
# Creating plot
plt.subplot(221)
plt.boxplot(data1, labels=dlabels, vert=False)
plt.grid('major', axis='y')
plt.ylabel('Sequence')
plt.xlabel('Brightness Score')

# Creating plot
plt.subplot(222)
plt.boxplot(data2, labels=empty_labels, vert=False)
plt.grid('major', axis='y')
plt.xlabel('Time Derivative of Brightness Scores')

# plot grouped bar chart
ax2 = plt.subplot(212)
ax = sub_df.plot(x='name',
        kind='bar',
        stacked=False,
        width = 0.9,
        rot=-45,
        xlabel='Sequences',
        ylabel='# images',
        ax = ax2)
ax.legend(['Seq. Images', '|\u03B2|> \u03C3', '|\u03B2|> 2\u03C3', '|\u03B2|> 3\u03C3'])
ax.grid(b=True, which='major', color='lightgray', linestyle='--')

plt.tight_layout()
plt.savefig(dirname+"/../out_data/agg_figs/KITTI_brightness.png",bbox_inches='tight')
plt.show()