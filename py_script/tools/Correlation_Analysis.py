from curses import meta
import numpy as np
from numpy import c_
import pandas as pd
import glob
import os
import re
import shutil
import statistics as st
import scipy.stats as sci_st
from texttable import Texttable
import sys
from scipy.stats import pearsonr
import matplotlib.pyplot as plt
import seaborn as sns

# import local libraries
sys.path.insert(0, os.path.dirname(__file__)+'/../tools/')
import DS_fns as ds_fns
import table_utils as tb_utils
import sys_utils
import math

# extract currenty directory name for path adjustification
dirname = os.path.dirname(__file__)+'/..'

# get data from a dataset to send to the 
def get_data_for_ds(ds, tag):
    if (ds == "KITTI"):
        d,l = ds_fns.filename_kitti_creator(tag)
    elif (ds == "EUROC"):
        d,l =  ds_fns.filenames_euroc_creator(tag)
    elif (ds == "TUMVI"):
        d,l =  ds_fns.filename_tumvi_creator(tag)
    else:
        d,l =  None, None

    d_all = np.array(sum(d, []))
    d_all[np.isnan(d_all)] = 0
    d_all[np.isinf(d_all)] = 0
    return d_all


def calculate_corr_for_ds(ds):
    # get meta_categories from file
    meta_categories = sys_utils.import_list(dirname+"/../out_data/agg_reports/lists/meta_cat")
    
    count = 1
    corr_mat = np.zeros((len(meta_categories), len(meta_categories)))
    for i in range(0,len(meta_categories)):
        d1_all = get_data_for_ds(ds, meta_categories[i])

        if (len(d1_all >= 2)):
            for j in range(i,len(meta_categories)):
                # read KITTI dataset data based on selected tag
                d2_all = get_data_for_ds(ds, meta_categories[j])
                
                if len(d2_all) >=2 :
                    if len(d1_all) == len(d2_all):
                        corr,_ = pearsonr(d1_all, d2_all)

                        if not(math.isnan(corr)):
                            print(str(count)+"\t"+meta_categories[i]+'\t' +meta_categories[j]+"\t"+str(corr))
                            count+=1
                            corr_mat[j][i] = corr


    # loop over the corr_mat to detect 0 at the diagonal 
    rem = []
    for i in range(0,len(meta_categories)):
        if (corr_mat[i][i] == 0):
            rem.append(i)

    idx = list(set(range(corr_mat.shape[0])).difference(rem))

    out_corr_map    = corr_mat[np.ix_(idx,idx)]
    out_labels      = meta_categories

    for index in sorted(rem, reverse=True):
        del out_labels[index]

    # change the out labels with natural language words with units
    titles_dict, __, __ = sys_utils.import_dict(dirname+"/../out_data/agg_reports/dicts/", "titles_dict")
    units_dict , __, __ = sys_utils.import_dict(dirname+"/../out_data/agg_reports/dicts/", "units_dict")

    NL_labels = []
    for c_label in out_labels:
        NL_labels.append(titles_dict[c_label]+"["+units_dict[c_label]+"]")

    #plt.show()
    fig1 = plt.figure(ds+' PMCC')
    fig1.set_size_inches([15,15])
    sns.heatmap(out_corr_map, cmap= 'binary', square=True, linewidths=0.5, xticklabels=NL_labels,yticklabels=NL_labels, vmin=0, vmax=1)
    plt.tight_layout()
    plt.savefig(dirname+"/../out_data/agg_figs/PMCC/"+ds+".png")
    plt.close('all')



# main function, do the corr for the 3 datasets
# KITTI
calculate_corr_for_ds("KITTI")
calculate_corr_for_ds("EUROC")
calculate_corr_for_ds("TUMVI")