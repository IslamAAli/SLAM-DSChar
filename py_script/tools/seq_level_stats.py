from curses import meta
from nis import cat
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
import DS_fns
import sys_utils
import stats_fns 
import Diversity_tools

print("\n\n")
print("------------------------------------------------------------------")
print("---( DS_EVAL Reports Generator - v0p1 - Sequence Level Results)---")
print("------------------------------------------------------------------")
print("")

# define datasets to be included
ds_names = ['KITTI', 'EURO_C', 'TUM_VI']
non_data_item = ["BRIGHTNESS_STATS", "BRIGHTNESS_CHANGE"]

# extract currenty directory name for path adjustification
dirname = os.path.dirname(__file__)+'/..'

# get meta_categories from file
meta_categories = sys_utils.import_list(dirname+"/../out_data/agg_reports/lists/meta_cat")

for dataset in ds_names:
    # dictionary to hold the data of different parameters
    dataset_dict = {}
    metrics_dict = {}
    diversity_dict = {}
    
    # retrieve the names of sequences for the current dataset
    seq_names = DS_fns.seq_names_retriever(dataset)

    # read the data for each category and save it to the dictionary
    for category in meta_categories:
        # read file data for this category

        data, labels = DS_fns.filename_creator(dataset, category)
        # save to dictionary with category name as key
        dataset_dict[category] = data

    # loop over sequences, and for each sequence, calculate the stats of different parameters
    for seq_id in range(len(seq_names)):
        for category in meta_categories:
            # check if data for this parameter exists
            if dataset_dict[category]:
                # data is saved in dataset_dict[category][seq_id]
                metrics_dict[category] = stats_fns.calculate_list_stats(dataset_dict[category][seq_id], category)

                # get diversity metrics 
                entropy = Diversity_tools.calculate_entropy(dataset_dict[category][seq_id], category)
                d, oneMinusD, oneOverD = Diversity_tools.calculate_SDI(dataset_dict[category][seq_id], category)
                diversity_dict[category] = {
                    "entropy": entropy,
                    "D": d, 
                    "1minusD" : oneMinusD,
                    "1overD"  : oneOverD
                }
            else:
                metrics_dict[category] = stats_fns.calculate_list_stats([], "Dummy")
                diversity_dict[category] = {
                    "entropy": 0,
                    "D": 0, 
                    "1minusD" : 0,
                    "1overD"  : 0
                }
                
        # create State table for each sequence
        print("\n\n")
        print('-------------------------------')
        print(">> "+seq_names[seq_id] + " Stats Report:")
        print('-------------------------------')
        t = Texttable(max_width=0)
        t.add_row(['ID','Metric', 'Samples', 'Sum', 'Min', 'Max','Mean', 'Std Dev', 'Median', 'Variance', 'Skewness'])
        key_id = 1
        for key in meta_categories:
            t.add_row   ([  
                        key_id,
                        key, 
                        metrics_dict[key]["size"],
                        metrics_dict[key]["sum"],
                        metrics_dict[key]["min"],
                        metrics_dict[key]["max"],
                        metrics_dict[key]["mean"],
                        metrics_dict[key]["std_dev"],
                        metrics_dict[key]["median"],
                        metrics_dict[key]["var"],
                        metrics_dict[key]["skewness"],
                        ])
            key_id += 1
        print(t.draw())
        report_file_path = dirname+"/../out_data/seq_level_agg_reports/"+dataset+"/reports/STATS_"+str(seq_names[seq_id])+".txt"
        stats_fns.export_data_table(report_file_path, t.draw())

        # create Diversity table for each sequence
        print("\n\n")
        print('-------------------------------')
        print(">> "+seq_names[seq_id] + " Diversity Report:")
        print('-------------------------------')
        t = Texttable(max_width=0)
        t.add_row(['ID','Metric', 'Entropy', 'SDI (D)', 'SDI (1-D)', 'SDI (1/D)'])
        key_id = 1
        for key in meta_categories:
            t.add_row   ([  
                        key_id,
                        key, 
                        diversity_dict[key]["entropy"],
                        diversity_dict[key]["D"],
                        diversity_dict[key]["1minusD"],
                        diversity_dict[key]["1overD"]
                        ])
            key_id += 1
        print(t.draw())
        report_file_path = dirname+"/../out_data/seq_level_agg_reports/"+dataset+"/reports/DIVERSITY_"+str(seq_names[seq_id])+".txt"
        stats_fns.export_data_table(report_file_path, t.draw())

        # save the dictionary to the output folder
        sys_utils.export_dict_npy(dirname+"/../out_data/seq_level_agg_reports/"+dataset+"/dicts/", "STATS_"+str(seq_names[seq_id]), metrics_dict)
        sys_utils.export_dict_npy(dirname+"/../out_data/seq_level_agg_reports/"+dataset+"/dicts/", "DIVERSITY_"+str(seq_names[seq_id]), diversity_dict)
    
