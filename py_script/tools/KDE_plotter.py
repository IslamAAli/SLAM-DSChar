import os
import sys
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import ptitprince as pt

# import the data reading and visualization package
sys.path.insert(0, os.path.dirname(__file__)+'/../')
import DS_fns as ds_fns
import visualization_fns as vis_fns
import sys_utils

# extract currenty directory name for path adjustification
dirname = os.path.dirname(__file__)+'/..'

# define datasets to be included
ds_names = ['KITTI', 'EURO_C', 'TUM_VI']
non_data_item = ["BRIGHTNESS_STATS", "BRIGHTNESS_CHANGE"]

# get meta_categories from file
meta_categories = sys_utils.import_list(dirname+"/../out_data/agg_reports/lists/meta_cat")


for tag in meta_categories:
    print("KDE Plotting: "+tag)

    # read euro_c dataset data based on selected tag
    data_euro_c, labels_euro_c = ds_fns.filenames_euroc_creator(tag)
    data_euro_c_all = sum(data_euro_c, [])

    # read kitti dataset data based on selected tag
    data_kitti, labels_kitti = ds_fns.filename_kitti_creator(tag)
    data_kitti_all = sum(data_kitti, [])

    # read KITTI-VI dataset data based on selected tag
    data_tumvi, labels_tumvi = ds_fns.filename_tumvi_creator(tag)
    data_tumvi_all = sum(data_tumvi, [])

    # create a figure and give it a proper size
    fig1 = plt.figure(tag)
    fig1.set_size_inches([6,4])

    # draw the rain cloud plot
    vis_fns.draw_KDE_plot(data_kitti_all, data_euro_c_all, data_tumvi_all, tag)

    # show the drawn figure
    plt.tight_layout()
    dirname = ds_fns.dirname
    plt.savefig(dirname+"/../out_data/agg_figs/KDEplot_figs/KDE_"+tag+".png")
    plt.close('all')
    # plt.show()

