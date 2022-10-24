import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

dirname = os.path.dirname(__file__)+'/..'

filenames1 = [
'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_MH_01_easy.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_MH_02_easy.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_MH_03_medium.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_MH_04_difficult.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_MH_05_difficult.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_V1_01_easy.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_V1_02_medium.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_V1_03_difficult.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_V2_01_easy.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_V2_02_medium.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS]EURO_C_V2_03_difficult.txt'
]

filenames2 = [
'../out_data/reports/EURO_C/[BRIGHTNESS_DIFF]EURO_C_MH_01_easy.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS_DIFF]EURO_C_MH_02_easy.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS_DIFF]EURO_C_MH_03_medium.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS_DIFF]EURO_C_MH_04_difficult.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS_DIFF]EURO_C_MH_05_difficult.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS_DIFF]EURO_C_V1_01_easy.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS_DIFF]EURO_C_V1_02_medium.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS_DIFF]EURO_C_V1_03_difficult.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS_DIFF]EURO_C_V2_01_easy.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS_DIFF]EURO_C_V2_02_medium.txt'
,'../out_data/reports/EURO_C/[BRIGHTNESS_DIFF]EURO_C_V2_03_difficult.txt'
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

file_path = dirname+'/../out_data/dataset_reports/EURO_C/[BRIGHTNESS]barchart_data.dat'
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
plt.savefig(dirname+"/../out_data/agg_figs/EuroC_brightness.png",bbox_inches='tight')
plt.show()