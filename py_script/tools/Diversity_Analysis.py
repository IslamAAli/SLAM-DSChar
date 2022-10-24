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
from scipy.stats import entropy

# import local libraries
sys.path.insert(0, os.path.dirname(__file__)+'/../tools/')
import DS_fns as ds_fns
import table_utils as tb_utils
import sys_utils
import Diversity_tools

# ===========================================================================================
# Report Generation
# ===========================================================================================
print("\n\n")
print("---------------------------------------------")
print("---( DS_EVAL Diversity Calculator - v0p1 )---")
print("---------------------------------------------")
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
entropy_dict    = {}
D_dict          = {}
oneMinusD_dict  = {}
oneOverD_dict   = {}
for cat in meta_categories:
    entropy_dict[cat]   = {}
    D_dict[cat]         = {}
    oneMinusD_dict[cat] = {}
    oneOverD_dict[cat]  = {}

# calculate diversity parameters
for ds in ds_names:
    print("## Processing: "+ds)
    for cat in meta_categories:
        # calculate the entropy
        entropy_dict[cat][ds] = round(Diversity_tools.calculate_entropy(ds_cat_data[ds][cat], cat), 3)

        # calculate the simpson coeff for diversity analysis
        m_d, m_oneMinusD, m_oneOverD = Diversity_tools.calculate_SDI(ds_cat_data[ds][cat], cat)
        D_dict[cat][ds]             = round(m_d, 3)
        oneMinusD_dict[cat][ds]     = round(m_oneMinusD, 3)
        oneOverD_dict[cat][ds]      = round(m_oneOverD, 3)

# export calculated diversity metrics
sys_utils.export_dict(dirname+"/../out_data/agg_reports/dicts/", "entropy_dict", entropy_dict)
sys_utils.export_dict(dirname+"/../out_data/agg_reports/dicts/", "SDI_D", D_dict)
sys_utils.export_dict(dirname+"/../out_data/agg_reports/dicts/", "SDI_oneMinusD", oneMinusD_dict)
sys_utils.export_dict(dirname+"/../out_data/agg_reports/dicts/", "SDI_oneOverD", oneOverD_dict)

# visualization and exporting information in tablular format
tb_utils.single_param_table(ds_names, meta_categories, entropy_dict, dirname, "ShannonEntropy", True, True)
tb_utils.single_param_table(ds_names, meta_categories, D_dict, dirname, "SimpsonDiversity_D", True, True)
tb_utils.single_param_table(ds_names, meta_categories, oneMinusD_dict, dirname, "SimpsonDiversity_oneMinusD", True, True)
tb_utils.single_param_table(ds_names, meta_categories, oneOverD_dict, dirname, "SimpsonDiversity_oneOVerD", True, True)