import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import sys

sys.path.insert(0, os.path.dirname(__file__)+'/../tools/')
import DS_fns as ds_fns

dirname = os.path.dirname(__file__)+'/..'

# --------------------------------------------------------------
def read_files(files_list):
    data= []
    for filename in files_list:
        fn = os.path.join(dirname, filename)
        with open(fn) as f:
            lines = f.read().splitlines()

        data.append(list(map(float, lines)))

    return data

def draw_figure(tag, location, x_label, y_label, skip_labels, ds_name):
    # read data from files
    if (ds_name == 'EuroC'):
        data, labels = ds_fns.filenames_euroc_creator(tag)
    else:
        data, labels = ds_fns.filename_tumvi_creator(tag)


    empty_labels= [''] * len(labels)
    plt.subplot(location)
    if not skip_labels:
        plt.boxplot(data, labels=labels, vert=False)
        plt.ylabel(y_label)
    else:
        plt.boxplot(data, labels=empty_labels, vert=False)
    plt.grid('major', axis='y')
    plt.xlabel(x_label)


def plot_inertial_diff(ds_name):
    fig1 = plt.figure(ds_name+' Inertial Diff - Acc')
    fig1.set_size_inches([30,20])

    # Creating plot
    draw_figure('AX', 331, 'Acc-X (m/sec^2)', 'Sequence', False, ds_name)
    draw_figure('AX_1ST_DIFF', 332, 'Jerk-X (m/sec^3)', 'Sequence', True, ds_name)
    draw_figure('AX_2ND_DIFF', 333, 'Snap-X (m/sec^4)', 'Sequence', True, ds_name)

    draw_figure('AY', 334, 'Acc-Y (m/sec^2)', 'Sequence', False, ds_name)
    draw_figure('AY_1ST_DIFF', 335, 'Jerk-Y (m/sec^3)', 'Sequence', True, ds_name)
    draw_figure('AY_2ND_DIFF', 336, 'Snap-Y (m/sec^4)', 'Sequence', True, ds_name)

    draw_figure('AZ', 337, 'Acc-Z (m/sec^2)', 'Sequence', False, ds_name)
    draw_figure('AZ_1ST_DIFF', 338, 'Jerk-Z (m/sec^3)', 'Sequence', True, ds_name)
    draw_figure('AZ_2ND_DIFF', 339, 'Snap-Z (m/sec^4)', 'Sequence', True, ds_name)


    plt.tight_layout()
    plt.savefig(dirname+"/../out_data/agg_figs/"+ds_name+"_inertial_Acc.png",bbox_inches='tight')
    plt.show()

    fig1 = plt.figure(ds_name+' Inertial Diff - Gyro')
    fig1.set_size_inches([30,20])

    # Creating plot
    draw_figure('GX', 331, 'Angular Velocity-X (deg/sec)', 'Sequence', False, ds_name)
    draw_figure('GX_1ST_DIFF', 332, 'Angular Acceleration-X (deg/sec^2)', 'Sequence', True, ds_name)
    draw_figure('GX_2ND_DIFF', 333, 'Angular Jerk-X (m/sec^4)', 'Sequence', True, ds_name)

    draw_figure('GY', 334, 'Angular Velocity-Y (deg/sec)', 'Sequence', False, ds_name)
    draw_figure('GY_1ST_DIFF', 335, 'Angular Acceleration-Y (deg/sec^2)', 'Sequence', True, ds_name)
    draw_figure('GY_2ND_DIFF', 336, 'Angular Jerk-Y (deg/sec^3)', 'Sequence', True, ds_name)

    draw_figure('GZ', 337, 'Angular Velocity-Z (deg/sec)', 'Sequence', False, ds_name)
    draw_figure('GZ_1ST_DIFF', 338, 'Angular Acceleration-Z (deg/sec^2)', 'Sequence', True, ds_name)
    draw_figure('GZ_2ND_DIFF', 339, 'Angular Jerk-Z (deg/sec^3)', 'Sequence', True, ds_name)


    plt.tight_layout()
    plt.savefig(dirname+"/../out_data/agg_figs/"+ds_name+"_inertial_Gyro.png",bbox_inches='tight')
    plt.show()

# --------------------------------------------------------------

plot_inertial_diff ("EuroC")
plot_inertial_diff ("TUMVI")