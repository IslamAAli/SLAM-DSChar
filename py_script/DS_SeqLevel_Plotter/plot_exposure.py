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
def exposure_plot(data1, data2, data3, bar_data, dlabels, ds_name):
    empty_labels = [''] * len(dlabels)

    fig1 = plt.figure(ds_name+' Revisit')
    fig1.set_size_inches([20,8])

    plt.subplot(221)
    plt.boxplot(data1, labels=empty_labels, showmeans=True)
    plt.grid('major', axis='x')
    plt.ylabel('Intensity Mean')
    plt.xticks(rotation=-45)

    plt.subplot(222)
    plt.boxplot(data2, labels=empty_labels, showmeans=True)
    plt.grid('major', axis='x')
    plt.ylabel('Intensity Skewness')
    plt.xticks(rotation=-45)

    plt.subplot(223)
    plt.boxplot(data3, labels=dlabels, showmeans=True)
    plt.grid('major', axis='x')
    plt.xlabel('Sequence')
    plt.ylabel('Exposure Zone')
    plt.xticks(rotation=-45)

    y0 = np.array(bar_data[0])
    y1 = np.array(bar_data[1])
    y2 = np.array(bar_data[2])
    y3 = np.array(bar_data[3])
    y4 = np.array(bar_data[4])
    plt.subplot(224)
    plt.bar(dlabels,y0, color='r')
    plt.bar(dlabels,y1, bottom=y0, color='b')
    plt.bar(dlabels,y2, bottom=y0+y1, color='g')
    plt.bar(dlabels,y3, bottom=y0+y1+y2, color='y')
    plt.bar(dlabels,y4, bottom=y0+y1+y2+y3, color='b')
    plt.xlabel('Sequence')
    plt.ylabel('Exposure Categories (%)')
    plt.legend(['Black', 'Under Exposed', 'Properly Exposed', 'Over Exposed', 'White' ])
    plt.xticks(rotation=-45)

    plt.tight_layout()
    plt.savefig(dirname+"/../out_data/agg_figs/"+ds_name+"_exposure.png",bbox_inches='tight')
    plt.show()
# =============================================================

# ==================
# KITTI
# ==================
kitti_data1, kitti_labels = ds_fns.filename_kitti_creator("EXPOSURE_MEAN")
kitti_data2, kitti_labels = ds_fns.filename_kitti_creator("EXPOSURE_SKEW")
kitti_data3, kitti_labels = ds_fns.filename_kitti_creator("EXPOSURE_ZONE")

bar_plot_list = []
BL, lab = ds_fns.filename_kitti_creator("BLACK_EXPOSURE_PERCENT")
UE, lab = ds_fns.filename_kitti_creator("UNDER_EXPOSURE_PERCENT")
PE, lab = ds_fns.filename_kitti_creator("PROPER_EXPOSURE_PERCENT")
OE, lab = ds_fns.filename_kitti_creator("OVER_EXPOSURE_PERCENT")
WH, lab = ds_fns.filename_kitti_creator("WHITE_EXPOSURE_PERCENT")

bar_plot_list.append( [item for sublist in BL for item in sublist])
bar_plot_list.append( [item for sublist in UE for item in sublist])
bar_plot_list.append( [item for sublist in PE for item in sublist])
bar_plot_list.append( [item for sublist in OE for item in sublist])
bar_plot_list.append( [item for sublist in WH for item in sublist])
exposure_plot(kitti_data1, kitti_data2, kitti_data3, bar_plot_list, kitti_labels, 'KITTI')


# ==================
# EURO-C
# ==================
euro_c_data1, euro_c_labels = ds_fns.filenames_euroc_creator("EXPOSURE_MEAN")
euro_c_data2, euro_c_labels = ds_fns.filenames_euroc_creator("EXPOSURE_SKEW")
euro_c_data3, euro_c_labels = ds_fns.filenames_euroc_creator("EXPOSURE_ZONE")

bar_plot_list = []
BL, lab = ds_fns.filenames_euroc_creator("BLACK_EXPOSURE_PERCENT")
UE, lab = ds_fns.filenames_euroc_creator("UNDER_EXPOSURE_PERCENT")
PE, lab = ds_fns.filenames_euroc_creator("PROPER_EXPOSURE_PERCENT")
OE, lab = ds_fns.filenames_euroc_creator("OVER_EXPOSURE_PERCENT")
WH, lab = ds_fns.filenames_euroc_creator("WHITE_EXPOSURE_PERCENT")

bar_plot_list.append( [item for sublist in BL for item in sublist])
bar_plot_list.append( [item for sublist in UE for item in sublist])
bar_plot_list.append( [item for sublist in PE for item in sublist])
bar_plot_list.append( [item for sublist in OE for item in sublist])
bar_plot_list.append( [item for sublist in WH for item in sublist])

exposure_plot(euro_c_data1, euro_c_data2, euro_c_data3, bar_plot_list, euro_c_labels, 'EuroC')

# ==================
# TUM-VI
# ==================
tum_vi_data1, tum_vi_labels = ds_fns.filename_tumvi_creator("EXPOSURE_MEAN")
tum_vi_data2, tum_vi_labels = ds_fns.filename_tumvi_creator("EXPOSURE_SKEW", True, -250)
tum_vi_data3, tum_vi_labels = ds_fns.filename_tumvi_creator("EXPOSURE_ZONE")

bar_plot_list = []
BL, lab = ds_fns.filename_tumvi_creator("BLACK_EXPOSURE_PERCENT")
UE, lab = ds_fns.filename_tumvi_creator("UNDER_EXPOSURE_PERCENT")
PE, lab = ds_fns.filename_tumvi_creator("PROPER_EXPOSURE_PERCENT")
OE, lab = ds_fns.filename_tumvi_creator("OVER_EXPOSURE_PERCENT")
WH, lab = ds_fns.filename_tumvi_creator("WHITE_EXPOSURE_PERCENT")

bar_plot_list.append( [item for sublist in BL for item in sublist])
bar_plot_list.append( [item for sublist in UE for item in sublist])
bar_plot_list.append( [item for sublist in PE for item in sublist])
bar_plot_list.append( [item for sublist in OE for item in sublist])
bar_plot_list.append( [item for sublist in WH for item in sublist])

exposure_plot(tum_vi_data1, tum_vi_data2, tum_vi_data3, bar_plot_list, tum_vi_labels, 'TUMVI')
