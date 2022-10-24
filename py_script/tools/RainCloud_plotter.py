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

# import the titles and units dictionary
titles_dict, __, __ = sys_utils.import_dict(dirname+"/../out_data/agg_reports/dicts/", "titles_dict")
units_dict , __, __ = sys_utils.import_dict(dirname+"/../out_data/agg_reports/dicts/", "units_dict")


for tag in meta_categories:
    print("Rain Cloud Plotting: "+tag)

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

    list_data = []
    labels_list = []
    colors_list = []
    # aggregate the data in a single list of lists
    # if len(data_kitti_all) != 0:
    list_data.append(data_kitti_all)
    labels_list.append('KITTI')
    colors_list.append('#d0535f')

    # if len(data_euro_c_all) != 0:
    list_data.append(data_euro_c_all)
    labels_list.append('Euro-C MAV')
    colors_list.append('#45a679')

    # if len(data_tumvi_all) != 0:
    list_data.append(data_tumvi_all)
    labels_list.append('TUM-VI')
    colors_list.append('#30abd4')

    metric_title = titles_dict[tag]+" [$"+units_dict[tag]+"$]"
    # define plot properties to use with the rain cloud plot
    plot_props = dict(
        xlabel = metric_title,
        ylabel = 'Datasets', 
        labels = labels_list,
        colors = colors_list
    )

    # draw the rain cloud plot
    vis_fns.draw_raincloud(list_data, plot_props)

    # show the drawn figure
    plt.tight_layout()
    dirname = ds_fns.dirname
    plt.savefig(dirname+"/../out_data/agg_figs/raincloud_figs/raincloud_"+tag+".png")
    plt.close('all')
    # plt.show()