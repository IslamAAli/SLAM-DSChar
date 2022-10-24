import os
import sys
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import ptitprince as pt

# import the data reading and visualization package
sys.path.insert(0, os.path.dirname(__file__)+'/../tools/')
import DS_fns as ds_fns


# ======================================================
dataset = "KITTI"
tag = "BRIGHTNESS"

# get file names
data, labels = ds_fns.filename_kitti_creator(tag)

flat_list = [item for sublist in data for item in sublist]


for seq in data:
    sns.distplot(seq, hist = False, kde = True,
                    kde_kws = {'linewidth': 1})

sns.distplot(flat_list, hist = False, kde = True,
                    kde_kws = {'linewidth': 5})


plt.show()