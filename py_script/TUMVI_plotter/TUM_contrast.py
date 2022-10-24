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
data1, dlabels     = ds_fns.filename_tumvi_creator("CONTRAST_CR")
data2, dlabels     = ds_fns.filename_tumvi_creator("CONTRAST_WEBER")
data3, dlabels     = ds_fns.filename_tumvi_creator("CONTRAST_MICHELSON")
data4, dlabels     = ds_fns.filename_tumvi_creator("CONTRAST_RMS")
empty_labels            = [''] * len(dlabels)

fig1 = plt.figure('TUM-VI Contrast')
fig1.set_size_inches([15,15])
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
plt.savefig(dirname+"/../out_data/agg_figs/TUMVI_contrast.png",bbox_inches='tight')
plt.show()