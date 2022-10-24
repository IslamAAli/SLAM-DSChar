import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import sys

sys.path.insert(0, os.path.dirname(__file__)+'/../tools/')
import DS_fns as ds_fns

dirname = os.path.dirname(__file__)+'/..'

# =============================================================
def rot_only_plot(data, labels, ds_name):
    empty_labels = [''] * len(labels)

    vert_val = True
    fig1 = plt.figure(ds_name+' Rotation Only')
    fig1.set_size_inches([16,12])
    # Creating plot
    plt.boxplot(data, labels=labels, vert=vert_val)
    plt.grid('major', axis='y')
    plt.xlabel('Sequence')
    plt.ylabel('Acceleration Magnitude (m/sec^2)')
    plt.xticks(rotation=-45)

    plt.tight_layout()
    plt.savefig(dirname+"/../out_data/agg_figs/"+ds_name+"_AccMag.png",bbox_inches='tight')
    plt.show()
# =============================================================


# get the filenames 
eur_c_data, euro_c_labels = ds_fns.filenames_euroc_creator("ACC_MAG")
rot_only_plot(eur_c_data, euro_c_labels, 'EuroC')

tumvi_data, tumvi_labels = ds_fns.filename_tumvi_creator("ACC_MAG")
rot_only_plot(tumvi_data, tumvi_labels, 'TUMVI')