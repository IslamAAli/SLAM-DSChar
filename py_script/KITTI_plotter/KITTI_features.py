import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import sys

sys.path.insert(0, os.path.dirname(__file__)+'/../tools/')
import DS_fns as ds_fns
dirname = os.path.dirname(__file__)+'/..'

data1, dlabels = ds_fns.filename_kitti_creator('SIFT_COUNT')
data2, dlabels = ds_fns.filename_kitti_creator('FAST_COUNT')
data3, dlabels = ds_fns.filename_kitti_creator('ORB_COUNT')

data4, dlabels = ds_fns.filename_kitti_creator('SIFT_DIST_ABS')
data5, dlabels = ds_fns.filename_kitti_creator('FAST_DIST_ABS')
data6, dlabels = ds_fns.filename_kitti_creator('ORB_DIST_ABS')

data7, dlabels = ds_fns.filename_kitti_creator('SIFT_DIST_AVG')
data8, dlabels = ds_fns.filename_kitti_creator('FAST_DIST_AVG')
data9, dlabels = ds_fns.filename_kitti_creator('ORB_DIST_AVG')


empty_labels= [''] * len(dlabels)

# =========================================================================

# SIFT
fig1 = plt.figure('KITTI_SIFT')
fig1.set_size_inches([10,12])
plt.subplot(211)
plt.boxplot(data1, labels=dlabels, showmeans=True)
plt.grid('major', axis='x')
plt.xlabel('Sequence')
plt.ylabel('# Visual Features')

plt.subplot(223)
plt.boxplot(data4, labels=dlabels, vert=False)
plt.grid('major', axis='y')
plt.ylabel('Sequence')
plt.xlabel('% Spatial Features Distribution > 0')

plt.subplot(224)
plt.boxplot(data7, labels=empty_labels, vert=False)
plt.grid('major', axis='y')
plt.xlabel('% Spatial Features Distribution > $F_{dist-avg}$')

plt.tight_layout()
plt.savefig(dirname+"/../out_data/agg_figs/KITTI_features_SIFT.png",bbox_inches='tight')
plt.show()

# FAST
fig2 = plt.figure('KITTI_FAST')
fig2.set_size_inches([10,12])
plt.subplot(211)
plt.boxplot(data2, labels=dlabels, showmeans=True)
plt.grid('major', axis='x')
plt.xlabel('Sequence')
plt.ylabel('# Visual Features')

plt.subplot(223)
plt.boxplot(data5, labels=dlabels, vert=False)
plt.grid('major', axis='y')
plt.ylabel('Sequence')
plt.xlabel('% Spatial Features Distribution > 0')

plt.subplot(224)
plt.boxplot(data8, labels=empty_labels, vert=False)
plt.grid('major', axis='y')
plt.xlabel('% Spatial Features Distribution > $F_{dist-avg}$')

plt.tight_layout()
plt.savefig(dirname+"/../out_data/agg_figs/KITTI_features_FAST.png",bbox_inches='tight')
plt.show()

# ORB
fig3 = plt.figure('KITTI_ORB')
fig3.set_size_inches([10,12])
plt.subplot(211)
plt.boxplot(data3, labels=dlabels, showmeans=True)
plt.grid('major', axis='x')
plt.xlabel('Sequence')
plt.ylabel('# Visual Features')

plt.subplot(223)
plt.boxplot(data6, labels=dlabels, vert=False)
plt.grid('major', axis='y')
plt.ylabel('Sequence')
plt.xlabel('% Spatial Features Distribution > 0')

plt.subplot(224)
plt.boxplot(data9, labels=empty_labels, vert=False)
plt.grid('major', axis='y')
plt.xlabel('% Spatial Features Distribution > $F_{dist-avg}$')

plt.tight_layout()
plt.savefig(dirname+"/../out_data/agg_figs/KITTI_features_ORB.png",bbox_inches='tight')
plt.show()