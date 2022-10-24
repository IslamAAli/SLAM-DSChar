import numpy as np
import pandas as pd
import glob
import os
import re
import shutil
import statistics as st
import sys

#import local libraries
sys.path.insert(0, os.path.dirname(__file__)+'/../tools/')
import DS_fns as ds_fns
import sys_utils

# extract currenty directory name for path adjustification
dirname = os.path.dirname(__file__)+'/..'

# define datasets to be included
ds_names = ['KITTI', 'EURO_C', 'TUM_VI']
non_data_item = ["BRIGHTNESS_STATS", "BRIGHTNESS_CHANGE"]

meta_categories = ds_fns.get_meta_categories(ds_names, non_data_item)
sys_utils.export_list(dirname+"/../out_data/agg_reports/lists/meta_cat", meta_categories)