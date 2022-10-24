from curses import meta
import os
import statistics as st
import scipy.stats as sci_st
import sys
import numpy as np


sys.path.insert(0, os.path.dirname(__file__)+'/../tools/')
import DS_fns as ds_fns
# ===========================================================================================
# Report Generator for single Dataset
# ===========================================================================================
def calculate_list_stats(data, tag):
    print(">>> Calculating statistics "+ tag)
    list_stats = {}

    cleanedList = [x for x in data if x == x]

    if (len(cleanedList) == 0):
        list_stats['mean']      = np.nan
        list_stats['std_dev']   = np.nan
        list_stats['median']    = np.nan
        list_stats['var']       = np.nan
        list_stats['skewness']  = np.nan
        list_stats['min']       = np.nan
        list_stats['max']       = np.nan
        list_stats['size']      = np.nan
        list_stats['sum']       = np.nan

    elif (len(cleanedList) == 1):
        list_stats['mean']      = cleanedList[0]
        list_stats['std_dev']   = 0
        list_stats['median']    = cleanedList[0]
        list_stats['var']       = 0
        list_stats['skewness']  = 0
        list_stats['min']       = min(cleanedList)
        list_stats['max']       = max(cleanedList)
        list_stats['size']      = len(cleanedList)
        list_stats['sum']       = sum(cleanedList)

    else:
        list_stats['mean']      = round(st.mean(cleanedList),3)
        list_stats['std_dev']   = round(st.stdev(cleanedList),3)
        list_stats['median']    = round(st.median(cleanedList),3)
        list_stats['var']       = round(st.variance(cleanedList),3)
        list_stats['skewness']  = round(sci_st.skew(cleanedList),3)
        list_stats['min']       = min(cleanedList)
        list_stats['max']       = max(cleanedList)
        list_stats['size']      = len(cleanedList)
        list_stats['sum']       = sum(cleanedList)

    return list_stats

def export_data_table(file_path, data):
    text_file = open(file_path, "w")
    text_file.write(data)
    text_file.close()