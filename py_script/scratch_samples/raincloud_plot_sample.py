import os
import sys
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import ptitprince as pt

# import the data reading and visualization package
sys.path.insert(0, os.path.dirname(__file__)+'/../tools/')
import DS_fns as ds_fns, visualization_fns

# define the metric to extract data for
tag = 'ORB_COUNT'

# read euro_c dataset data based on selected tag
data_euro_c, labels_euro_c = ds_fns.filenames_euroc_creator(tag)
data_euro_c_all = sum(data_euro_c, [])

# read kitti dataset data based on selected tag
data_kitti, labels_kitti = ds_fns.filename_kitti_creator(tag)
data_kitti_all = sum(data_kitti, [])

# read KITTI-VI dataset data based on selected tag

# create a figure and give it a proper size
fig1 = plt.figure(tag)
fig1.set_size_inches([14,7])

# aggregate the data in a single list of lists
list_data = [data_kitti_all, data_euro_c_all]
# list_data = [data_kitti_all, data_euro_c_all, data_euro_c_all]

# define plot properties to use with the rain cloud plot
plot_props = dict(
    xlabel = 'Number of Fast Features',
    ylabel = 'Datasets', 
    labels = ['KITTI', 'Euro-C MAV']
)

# plot_props = dict(
#     xlabel = 'Contrast Score',
#     ylabel = 'Datasets', 
#     labels = ['KITTI', 'Euro-C MAV', 'TUM-VI']
# )
# draw the rain cloud plot
visualization_fns.draw_raincloud(list_data, plot_props)

# show the drawn figure
plt.tight_layout()
plt.show()