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


# ===========================================================================================
# Report Generator for single Dataset
# ===========================================================================================
def calculate_entropy(data,tag,  base=None):
    print(">>> Calculating Shannon's entropy "+ tag)
    entropy_val = 0

    if(len(data) != 0):
        value,counts = np.unique(data, return_counts=True)
        entropy_val = entropy(counts, base=base)

    return entropy_val

def calculate_SDI(data, tag):
    print(">>> Calculating Simpson's Diversity Indeces "+ tag)
    d           = 0
    oneMinusD   = 0
    oneOverD    = 0

    if(len(data) > 1):
        value,counts = np.unique(data, return_counts=True)
        # calculate D
        d = sum(counts * np.subtract(counts,1)) / (len(data) * (len(data) -1))
        # calculate other values
        oneMinusD = 1-d
        if (d != 0):
            oneOverD = 1/d

    return d, oneMinusD, oneOverD