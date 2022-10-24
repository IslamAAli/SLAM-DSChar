import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import sys

sys.path.insert(0, os.path.dirname(__file__)+'/../tools/')
import DS_fns as ds_fns

dirname = os.path.dirname(__file__)+'/..'

# =============================================================
def disparity_plot(data1, data2, data3, data4, dlabels, ds_name):
    empty_labels = [''] * len(dlabels)

    fig1 = plt.figure(ds_name+' Disparity')
    fig1.set_size_inches([20,14])

    plt.subplot(221)
    plt.boxplot(data1, labels=dlabels, showmeans=True, vert=False)
    plt.grid('major', axis='x')
    plt.ylabel('Sequence')
    plt.xlabel('StereoBM Mean')
    plt.xticks(rotation=-45)

    plt.subplot(222)
    plt.boxplot(data2, labels=empty_labels, showmeans=True, vert=False)
    plt.grid('major', axis='x')
    plt.xlabel('StereoBM Std. Div.')

    plt.subplot(223)
    plt.boxplot(data3, labels=dlabels, showmeans=True, vert=False)
    plt.grid('major', axis='x')
    plt.ylabel('Sequence')
    plt.xlabel('StereoSGBM Mean')

    plt.subplot(224)
    plt.boxplot(data4, labels=empty_labels, showmeans=True, vert=False)
    plt.grid('major', axis='x')
    plt.xlabel('StereoSGBM Std. Div.')


    plt.tight_layout()
    plt.savefig(dirname+"/../out_data/agg_figs/"+ds_name+"_disparity.png",bbox_inches='tight')
    plt.show()
# =============================================================

# ==================
# KITTI
# ==================
kitti_data1, kitti_labels = ds_fns.filename_kitti_creator("DISPARITY_AVG_BM")
kitti_data2, kitti_labels = ds_fns.filename_kitti_creator("DISPARITY_STD_DIV_BM")
kitti_data3, kitti_labels = ds_fns.filename_kitti_creator("DISPARITY_AVG_SGBM")
kitti_data4, kitti_labels = ds_fns.filename_kitti_creator("DISPARITY_STD_DIV_SGBM")

disparity_plot(kitti_data1, kitti_data2, kitti_data3, kitti_data4, kitti_labels, 'KITTI')

# ==================
# EURO-C
# ==================
euro_c_data1, euro_c_labels = ds_fns.filenames_euroc_creator("DISPARITY_AVG_BM")
euro_c_data2, euro_c_labels = ds_fns.filenames_euroc_creator("DISPARITY_STD_DIV_BM")
euro_c_data3, euro_c_labels = ds_fns.filenames_euroc_creator("DISPARITY_AVG_SGBM")
euro_c_data4, euro_c_labels = ds_fns.filenames_euroc_creator("DISPARITY_STD_DIV_SGBM")

disparity_plot(euro_c_data1, euro_c_data2, euro_c_data3, euro_c_data4, euro_c_labels, 'EuroC')

# ==================
# TUM-VI
# ==================
tum_vi_data1, tum_vi_labels = ds_fns.filename_tumvi_creator("DISPARITY_AVG_BM")
tum_vi_data2, tum_vi_labels = ds_fns.filename_tumvi_creator("DISPARITY_STD_DIV_BM")
tum_vi_data3, tum_vi_labels = ds_fns.filename_tumvi_creator("DISPARITY_AVG_SGBM")
tum_vi_data4, tum_vi_labels = ds_fns.filename_tumvi_creator("DISPARITY_STD_DIV_SGBM")

disparity_plot(tum_vi_data1, tum_vi_data2, tum_vi_data3, tum_vi_data4, tum_vi_labels, 'TUMVI')
