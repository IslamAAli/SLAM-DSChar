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
def revisit_plot(data1, data2, dlabels, ds_name):
    empty_labels = [''] * len(dlabels)

    fig1 = plt.figure(ds_name+' Revisit')
    fig1.set_size_inches([16,12])
    plt.subplot(211)
    plt.boxplot(data1, labels=dlabels, showmeans=True)
    plt.grid('major', axis='x')
    plt.xlabel('Sequence')
    plt.ylabel('Closeset Match Similarity Score')
    plt.xticks(rotation=-45)

    plt.subplot(212)
    plt.boxplot(data2, labels=dlabels, showmeans=True)
    plt.grid('major', axis='x')
    plt.xlabel('Sequence')
    plt.ylabel('Distance to Closest Match (Frames)')
    plt.xticks(rotation=-45)

    plt.tight_layout()
    plt.savefig(dirname+"/../out_data/agg_figs/"+ds_name+"_revisit.png",bbox_inches='tight')
    plt.show()
# =============================================================

kitti_data1, kitti_labels = ds_fns.filename_kitti_creator("REVISIT_SCORE")
kitti_data2, kitti_labels = ds_fns.filename_kitti_creator("REVISIT_DIST")
revisit_plot(kitti_data1, kitti_data2, kitti_labels, 'KITTI')

euro_c_data1, euro_c_labels = ds_fns.filenames_euroc_creator("REVISIT_SCORE")
euro_c_data2, euro_c_labels = ds_fns.filenames_euroc_creator("REVISIT_DIST")
revisit_plot(euro_c_data1, euro_c_data2, euro_c_labels, 'EuroC')

tum_vi_data1, tum_vi_labels = ds_fns.filename_tumvi_creator("REVISIT_SCORE")
tum_vi_data2, tum_vi_labels = ds_fns.filename_tumvi_creator("REVISIT_DIST")
revisit_plot(tum_vi_data1, tum_vi_data2, tum_vi_labels, 'TUMVI')
