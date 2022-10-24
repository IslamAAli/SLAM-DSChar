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

def single_param_table(ds_names, meta_categories, data_dict, dirname, file_tag, print_bool=True, export_bool=True):
    # visualization of data
    print("\n\n")
    print('----------------------------------')
    print(">> Shannon's Entropy Final Report:")
    print('----------------------------------')
    t = Texttable(max_width=0)
    t.add_row(['ID','Metric']+ds_names)
    key_id = 1
    for key in meta_categories:
        entropy_ds_vals = []
        for ds in data_dict[key]:
            entropy_ds_vals.append(data_dict[key][ds])

        t.add_row([key_id,key]+entropy_ds_vals)

        key_id += 1

    if print_bool:
        print(t.draw())

    if export_bool:
        report_file_path = dirname+"/../out_data/agg_reports/"+file_tag+".txt"
        export_data_table(report_file_path, t.draw())

# ===========================================================================================
def export_data_table(file_path, data):
    text_file = open(file_path, "w")
    text_file.write(data)
    text_file.close()