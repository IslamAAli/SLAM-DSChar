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
blur_scores, labels     = ds_fns.filenames_euroc_creator("BLUR_SCORE")
blur_percent, labels    = ds_fns.filenames_euroc_creator("BLUR_PERCENT")
empty_labels            = [''] * len(labels)


vert_val = True
fig1 = plt.figure('EuroC Revisit')
fig1.set_size_inches([8,6])
# Creating plot
plt.subplot(211)
plt.boxplot(blur_scores, labels=labels, vert=vert_val)
plt.grid('major', axis='y')
plt.xlabel('Sequence')
plt.ylabel('Blur Score')
plt.xticks(rotation=-45)

# Creating plot
plt.subplot(212)
plt.boxplot(blur_percent, labels=labels, vert=vert_val)
plt.grid('major', axis='y')
plt.xlabel('Sequence')
plt.ylabel('Blur Percentage %')
plt.xticks(rotation=-45)


plt.tight_layout()
plt.savefig(dirname+"/../out_data/agg_figs/EuroC_blur.png",bbox_inches='tight')
plt.show()