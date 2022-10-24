from curses import meta
import os
import sys
from matplotlib import markers
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import ptitprince as pt
import matplotlib

# import the data reading and visualization package
sys.path.insert(0, os.path.dirname(__file__)+'/../')
import DS_fns as ds_fns
import visualization_fns as vis_fns
import sys_utils

# extract currenty directory name for path adjustification
dirname = os.path.dirname(__file__)+'/..'

# define datasets to be included
ds_names = ['KITTI', 'EURO_C', 'TUM_VI']
metric = 'BLUR_SCORE'

# get data of each dataset for the blurring score
KITTI_data, KITTI_labels = ds_fns.filename_kitti_creator(metric)
EUROC_data, EUROC_labels = ds_fns.filenames_euroc_creator(metric)
TUMVI_data, TUMVI_labels = ds_fns.filename_tumvi_creator(metric)

ds_data = [KITTI_data, EUROC_data, TUMVI_data]

# min_vals_list = []
# max_vals_list = []
# for ds_data_item in ds_data:
#     min_val = 0
#     max_val = 0
#     data_vec = []
#     min_vals_ds = []
#     max_vals_ds = []
#     for seq in ds_data_item:
#         data_vec.extend(seq)
#         min_val = min(data_vec)
#         max_val = max(data_vec)
#         min_vals_ds.append(min_val)
#         max_vals_ds.append(max_val)
#         print(min_val, max_val)
#     print("\n\n")
#     min_vals_list.append(min_vals_ds)
#     max_vals_list.append(max_vals_ds)

# data_agg = sum(min_vals_list, [])
# print(data_agg)
# plt.plot(len(data_agg), data_agg)

# for min_vals_item, max_vals_item in zip(min_vals_list, max_vals_list):
#     plt.plot(range(len(max_vals_item)), max_vals_item)
#     plt.plot(range(len(min_vals_item)), min_vals_item)
    
# plt.show()


min_vals_list = []
max_vals_list = []
all_min_list = []
all_max_list = []
min_val = 0
max_val = 0
data_vec = []
for ds_data_item in ds_data:
    for seq in ds_data_item:
        data_vec.extend(seq)
        min_val = min(data_vec)
        max_val = max(data_vec)
        min_vals_list.append(min_val)
        max_vals_list.append(max_val)
        all_min_list.append(min(seq))
        all_max_list.append(max(seq))
        # print(min_val, max_val)
    # print("\n\n")
    # min_vals_list.append(min_vals_ds)
    # max_vals_list.append(max_vals_ds)

tum_vi_simple_data = ds_data[2][7] + ds_data[2][16]
print(min(tum_vi_simple_data))
print(max(tum_vi_simple_data))

ds_legend_items = [ 'KITTI DS Start', 'EuroC DS Start','TUM-VI DS Start', 
                    'Min. TUM-VI Seq 7+Seq 16', 'Max. TUM-VI Seq 7+Seq 16',
                    'Min. Score', 'Max. Score', 
                    'Min. Seq. Score', 'Max. Seq. Score']

fig1 = plt.figure()
fig1.set_size_inches([18,6])
matplotlib.rcParams.update({'font.size': 18})
plt.axvline(x=0, linewidth=3, color='lightcoral')
plt.axvline(x=22,  linewidth=3, color='lightblue')
plt.axvline(x=33,  linewidth=3, color='lightgreen')
plt.axhline(y=min(tum_vi_simple_data), color='k', linestyle='--', linewidth=2.5)
plt.axhline(y=max(tum_vi_simple_data), color='k', linestyle='--', linewidth=2.5)
plt.plot(range(len(min_vals_list)), min_vals_list, 'g-o')
plt.plot(range(len(max_vals_list)), max_vals_list, 'r-o')
plt.plot(range(len(all_min_list)), all_min_list, 'g--', linewidth=0.7)
plt.plot(range(len(all_max_list)), all_max_list, 'r--', linewidth=0.7)
plt.legend(ds_legend_items, loc='center left', bbox_to_anchor=(1, 0.5))
plt.xlabel('Sequences')
plt.ylabel('Blurring Score')
plt.grid()
# remove extra white spaces
# plt.tight_layout()
# get box dimensions in order to center the legend
# box = ax.get_position()
# ax.set_position([box.x0, box.y0 + box.height * 0.1, box.width, box.height * 0.9])
# # Put a legend below current axis
# ax.legend(['Min. TUM-VI Seq 7+Seq 16', 'Max. TUM-VI Seq 7+Seq 16','Min. Score', 'Max. Score', 'Min. Seq. Score', 'Max. Seq. Score', 'New DS', 'New DS']
# , loc='upper center', bbox_to_anchor=(0.5, 1.2),fancybox=True, ncol=4)
plt.tight_layout()
plt.savefig(dirname+"/../out_data/agg_figs/blurring_coverage.png")
plt.show()

