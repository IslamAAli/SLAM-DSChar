import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import sys

sys.path.insert(0, os.path.dirname(__file__)+'/../tools/')
import DS_fns as ds_fns

dirname = os.path.dirname(__file__)+'/..'

# get the filenames 
data1, dlabels    = ds_fns.filename_tumvi_creator("BRIGHTNESS")
data2, dlabels    = ds_fns.filename_tumvi_creator("BRIGHTNESS_DIFF")
empty_labels      = [''] * len(dlabels)

file_path = dirname+'/../out_data/dataset_reports/TUM_VI/[BRIGHTNESS]barchart_data.dat'
df = pd.read_csv(file_path)
sub_df = df[['name','count', '1sigma', '2sigma', '3sigma']]

# Creating plot
fig1 = plt.figure('TUM-VI Brightness')
fig1.set_size_inches([10,10])
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
plt.savefig(dirname+"/../out_data/agg_figs/TUMVI_brightness.png",bbox_inches='tight')
plt.show()