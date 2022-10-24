import os
import sys
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import ptitprince as pt

# ==================================================================
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


dict_list = ["entropy_dict", "SDI_D", "SDI_oneMinusD", "SDI_oneOverD"]
dict_str  = ['Shannon Entropy', 'SDI - D', 'SDI - 1-D', 'SDI - 1/D']
dict_folder= ['entropy_barchart_figs', 'SDI_D_barchart_figs', 'SDI_1-D_barchart_figs', 'SDI_1overD_barchart_figs']
ylim_vals = [0, 1, 1, 1]

for list_name, list_titl, list_folder, ylim_value in zip (dict_list, dict_str, dict_folder, ylim_vals):
    # get the entropy values for plotting
    npy_dict, json_dict, pkl_dict = sys_utils.import_dict(dirname+"/../out_data/agg_reports/dicts/", list_name)
    vis_fns.bar_plotting(npy_dict, list_titl, list_folder, ylim_value)