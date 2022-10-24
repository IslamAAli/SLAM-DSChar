import os
import sys
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import ptitprince as pt

# import the data reading and visualization package
sys.path.insert(0, os.path.dirname(__file__)+'/../')
import DS_fns as ds_fns
import visualization_fns as vis_fns
import sys_utils
import dicts_generator as dict_gen


# extract currenty directory name for path adjustification
dirname = os.path.dirname(__file__)+'/..'

# define datasets to be included
ds_names = ['KITTI', 'EURO_C', 'TUM_VI']
ds_names = ['TUM_VI']

metric_tags = dict_gen.general_tags + dict_gen.inertial_tags + dict_gen.visual_tags

for ds in ds_names:
    # loop over datasets ...
    for metric in metric_tags:
        df = pd.DataFrame(columns=['value', 'seq']);

        for seq in ds_fns.seq_names_retriever(ds):
            file_name = dirname+'/../out_data/reports/'+ds+'/['+metric+']'+ds+'_'+seq+'.txt'
            f = ds_fns.read_file_data(file_name)
            print(f)
            