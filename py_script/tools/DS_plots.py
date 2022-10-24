import os
import sys
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import ptitprince as pt


# ==================================================================
# import the data reading and visualization package
sys.path.insert(0, os.path.dirname(__file__)+'/../')
import DS_fns as ds_fns
import visualization_fns as vis_fns
import sys_utils
dirname = os.path.dirname(__file__)+'/..'
# ==================================================================

# Read the stats info
npy_dict, __, __ = sys_utils.import_dict(dirname+"/../out_data/agg_reports/dicts/", 'stats_dict')

# visualization of inertial dynamic range utilization/coverage
categories = ['Gyro-x', 'Gyro-y', 'Gyro-z', 'Acc-x', 'Acc-y', 'Acc-z']
EuroC_data = [
    npy_dict['EURO_C']['GX_DR_coverage_percent']['max'], 
    npy_dict['EURO_C']['GY_DR_coverage_percent']['max'], 
    npy_dict['EURO_C']['GZ_DR_coverage_percent']['max'], 
    npy_dict['EURO_C']['AX_DR_coverage_percent']['max'], 
    npy_dict['EURO_C']['AY_DR_coverage_percent']['max'], 
    npy_dict['EURO_C']['AZ_DR_coverage_percent']['max'], 
]

TUMVI_data = [
    npy_dict['TUM_VI']['GX_DR_coverage_percent']['max'], 
    npy_dict['TUM_VI']['GY_DR_coverage_percent']['max'], 
    npy_dict['TUM_VI']['GZ_DR_coverage_percent']['max'], 
    npy_dict['TUM_VI']['AX_DR_coverage_percent']['max'], 
    npy_dict['TUM_VI']['AY_DR_coverage_percent']['max'], 
    npy_dict['TUM_VI']['AZ_DR_coverage_percent']['max'], 
]

vis_fns.draw_radar_plot(categories, EuroC_data, TUMVI_data)


