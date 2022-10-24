from curses import meta
import numpy as np
import pandas as pd
import glob
import os
import re
import shutil
import statistics as st
import scipy.stats as sci_st
from texttable import Texttable
import sys
import pickle
import json


sys.path.insert(0, os.path.dirname(__file__)+'/../tools/')
import DS_fns as ds_fns
import sys_utils
import stats_fns 

# ===========================================================================================
# Report Generation
# ===========================================================================================
print("\n\n")
print("------------------------------------------")
print("---( DS_EVAL Reports Generator - v0p1 )---")
print("------------------------------------------")
print("")

# define datasets to be included
ds_names = ['KITTI', 'EURO_C', 'TUM_VI']
non_data_item = ["BRIGHTNESS_STATS", "BRIGHTNESS_CHANGE"]

# extract currenty directory name for path adjustification
dirname = os.path.dirname(__file__)+'/..'

# get meta_categories from file
meta_categories = sys_utils.import_list(dirname+"/../out_data/agg_reports/lists/meta_cat")

# read the data from files
ds_cat_data, meta_categories = ds_fns.read_ds_data_aggregate(ds_names, meta_categories)

# create list of dictionaries for each dataset
ds_eval_data = {}
ds_agg_cat_data = {}
for ds in ds_names:
    ds_eval_data[ds] = {}
    
for ds in ds_names:
    print("## Processing: "+ds)
    for cat in meta_categories:
        # calculate the stats of this aggregated data and add information to final dict
        ds_eval_data[ds][cat] = stats_fns.calculate_list_stats(ds_cat_data[ds][cat], cat)

# calculate the stats on the aggregated data
for category in meta_categories:
    # aggregate data from different datasets
    agg_data = []
    for ds in ds_names:
        agg_data += ds_cat_data[ds][category]

    ds_agg_cat_data[category] = stats_fns.calculate_list_stats(agg_data ,category)

# save the dictionary to the output folder
sys_utils.export_dict(dirname+"/../out_data/agg_reports/dicts/", "stats_dict", ds_eval_data)
sys_utils.export_dict(dirname+"/../out_data/agg_reports/dicts/", "agg_stats_dict", ds_agg_cat_data)

# visualization of data
for ds in ds_names:
    print("\n\n")
    print('-------------------------------')
    print(">> "+ds + " Final Report:")
    print('-------------------------------')
    t = Texttable(max_width=0)
    t.add_row(['ID','Metric', 'Samples', 'Sum', 'Min', 'Max','Mean', 'Std Dev', 'Median', 'Variance', 'Skewness'])
    key_id = 1
    for key in ds_eval_data[ds]:
        t.add_row   ([  
                    key_id,
                    key, 
                    ds_eval_data[ds][key]["size"],
                    ds_eval_data[ds][key]["sum"],
                    ds_eval_data[ds][key]["min"],
                    ds_eval_data[ds][key]["max"],
                    ds_eval_data[ds][key]["mean"],
                    ds_eval_data[ds][key]["std_dev"],
                    ds_eval_data[ds][key]["median"],
                    ds_eval_data[ds][key]["var"],
                    ds_eval_data[ds][key]["skewness"],
                    ])
        key_id += 1
    print(t.draw())
    report_file_path = dirname+"/../out_data/agg_reports/"+ds+".txt"
    stats_fns.export_data_table(report_file_path, t.draw())
    

print("\n\n")
print('-------------------------------')
print(">> Aggregated Final Report:")
print('-------------------------------')
t2 = Texttable(max_width=0)
t2.add_row(['ID','Metric', 'Samples', 'Sum', 'Min', 'Max','Mean', 'Std Dev', 'Median', 'Variance', 'Skewness'])
key_id = 1
for key in meta_categories:
    t2.add_row   ([  
                key_id,
                key, 
                ds_agg_cat_data[key]["size"],
                ds_agg_cat_data[key]["sum"],
                ds_agg_cat_data[key]["min"],
                ds_agg_cat_data[key]["max"],
                ds_agg_cat_data[key]["mean"],
                ds_agg_cat_data[key]["std_dev"],
                ds_agg_cat_data[key]["median"],
                ds_agg_cat_data[key]["var"],
                ds_agg_cat_data[key]["skewness"],
                ])
    key_id += 1
print(t2.draw())
report_file_path = dirname+"/../out_data/agg_reports/aggregated_stats.txt"
stats_fns.export_data_table(report_file_path, t2.draw())