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
import matplotlib.pyplot as plt
import matplotlib

# import local libraries
sys.path.insert(0, os.path.dirname(__file__)+'/../tools/')
import DS_fns as ds_fns
import table_utils as tb_utils
import sys_utils
import visualization_fns as vis_fns
import dicts_generator as dg
# extract currenty directory name for path adjustification
dirname = os.path.dirname(__file__)+'/..'

# =============================================================================
# =============================================================================
def get_exposure_nums(ds_name, data_dict):
    BE = round(((data_dict[ds_name]["BLACK_EXPOSURE_COUNT"]["sum"] / data_dict[ds_name]["EXPOSURE_MEAN"]["size"])*100),2)
    UE = round(((data_dict[ds_name]["UNDER_EXPOSURE_COUNT"]["sum"] / data_dict[ds_name]["EXPOSURE_MEAN"]["size"])*100),2)
    PE = round(((data_dict[ds_name]["PROPER_EXPOSURE_COUNT"]["sum"] / data_dict[ds_name]["EXPOSURE_MEAN"]["size"])*100),2)
    OE = round(((data_dict[ds_name]["OVER_EXPOSURE_COUNT"]["sum"] / data_dict[ds_name]["EXPOSURE_MEAN"]["size"])*100),2)
    WE = round(((data_dict[ds_name]["WHITE_EXPOSURE_COUNT"]["sum"] / data_dict[ds_name]["EXPOSURE_MEAN"]["size"])*100),2)
    # print(BE, UE, PE, OE, WE)
    return [BE, UE, PE, OE, WE]

# =============================================================================
# =============================================================================
def get_brightness_vals(ds_name, data_dict):
    sigma_1 = round(((data_dict[ds_name]["BRIGHTNESS_DIFF_1SIGMA"]["sum"] / data_dict[ds_name]["BRIGHTNESS_DIFF"]["size"])*100),2)
    sigma_2 = round(((data_dict[ds_name]["BRIGHTNESS_DIFF_2SIGMA"]["sum"] / data_dict[ds_name]["BRIGHTNESS_DIFF"]["size"])*100),2)
    sigma_3 = round(((data_dict[ds_name]["BRIGHTNESS_DIFF_3SIGMA"]["sum"] / data_dict[ds_name]["BRIGHTNESS_DIFF"]["size"])*100),2)
    # print(BE, UE, PE, OE, WE)
    return [sigma_1, sigma_2, sigma_3]


# =============================================================================
# =============================================================================
def get_blur_vals(ds_name, data_dict):
    blur_50 = round(((data_dict[ds_name]["BLUR_TOTAL_COUNT"]["sum"] / data_dict[ds_name]["BLUR_SCORE"]["size"])*100),2)
    blur_90 = round(((data_dict[ds_name]["BLUR_GLOBAL_COUNT"]["sum"] / data_dict[ds_name]["BLUR_SCORE"]["size"])*100),2)
    # print(BE, UE, PE, OE, WE)
    return [blur_50, blur_90]


# =============================================================================
# =============================================================================
def draw_bar_char_grouped(tags, dict, ylabel_txt, fig_size, file_name):
    #plot the bar charts for the H and SDI table for the paper
    KITTI = []
    EUROC = []
    TUMVI = []
    labels_cat = []
    for tag in tags:
        labels_cat.append(titles_dict[tag])
        KITTI.append(dict[tag][ds_names[0]])
        EUROC.append(dict[tag][ds_names[1]])
        TUMVI.append(dict[tag][ds_names[2]])

    x = np.arange(len(labels_cat))
    width = 0.25
    fig, ax = plt.subplots(figsize=fig_size)
    rects1 = ax.bar(x-width, KITTI, width, label='KITTI', color='#d0535f', edgecolor='black', zorder=3)
    rects2 = ax.bar(x, EUROC, width, label='EuroC-MAV', color='#45a679', edgecolor='black', zorder=3)
    rects3 = ax.bar(x+width, TUMVI, width, label='TUM-VI', color='#30abd4', edgecolor='black', zorder=3)

    # Add some text for labels, title and custom x-axis tick labels, etc.
    ax.set_ylabel(ylabel_txt)
    ax.set_xticks(x)
    ax.set_xticklabels(labels_cat, rotation=90)
    ax.legend(loc='upper center', bbox_to_anchor=(0.5, 1.2),fancybox=True, ncol=3)
    ax.grid(zorder=0)
    # plt.bar_label(rects1, rotation='vertical', padding=5)
    # plt.bar_label(rects2, rotation='vertical', padding=5)
    # plt.bar_label(rects3, rotation='vertical', padding=5)
    plt.tight_layout()
    plt.savefig(dirname+"/../out_data/agg_figs/"+file_name+".png")
    plt.show()

# =============================================================================
# =============================================================================
def H_SDI_boxplot(dictionary_item, keys_list, fig_name, x_title):
    ## Deal with Entropy
    values_list = []
    for key in dictionary_item.keys():
        if key in keys_list:
            values_list.append(dictionary_item[key])

    KITTI_entropy= []
    EUROC_entropy = []
    TUMVI_entropy = []
    for item in range(len(values_list)):
        item_list = list(values_list[item].values())
        KITTI_entropy.append(item_list[0])
        EUROC_entropy.append(item_list[1])
        TUMVI_entropy.append(item_list[2])

    K_str = str(np.round(np.mean(KITTI_entropy), 2))+'$\pm$('+str(np.round(np.std(KITTI_entropy),2))+') &'
    E_str = str(np.round(np.mean(EUROC_entropy), 2))+'$\pm$('+str(np.round(np.std(EUROC_entropy),2))+') &'
    T_str = str(np.round(np.mean(TUMVI_entropy), 2))+'$\pm$('+str(np.round(np.std(TUMVI_entropy),2))+') \\\\'

    print(  K_str, 
            E_str,
            T_str)

    plt.figure(figsize=(5,4))
    plt.boxplot([KITTI_entropy, EUROC_entropy, TUMVI_entropy], labels=['KITTI', 'EURO-C MAV', 'TUM-VI'], showmeans=True, vert=True)
    plt.grid('major', axis='y')
    matplotlib.rcParams.update({'font.size': 16})
    plt.xlabel('Dataset')
    plt.ylabel(x_title)
    plt.tight_layout()
    plt.savefig(dirname+"/../out_data/publication_figs/"+fig_name+".png")
    # plt.close('all')

# =============================================================================
# =============================================================================
# define dataset names
ds_names = ['KITTI', 'EURO_C', 'TUM_VI']

# import the titles and units dictionary
titles_dict, __, __ = sys_utils.import_dict(dirname+"/../out_data/agg_reports/dicts/", "titles_dict")
units_dict , __, __ = sys_utils.import_dict(dirname+"/../out_data/agg_reports/dicts/", "units_dict")

# import stats 
stats_dict, __, __  = sys_utils.import_dict(dirname+"/../out_data/agg_reports/dicts/", "stats_dict")
agg_stats_dict, __, __ = sys_utils.import_dict(dirname+"/../out_data/agg_reports/dicts/", "agg_stats_dict")

# load SDI and Entropy dicts
entropy_dict, __, __  = sys_utils.import_dict(dirname+"/../out_data/agg_reports/dicts/", "entropy_dict")
SDI_dict, __, __ = sys_utils.import_dict(dirname+"/../out_data/agg_reports/dicts/", "SDI_oneMinusD")

# ##############################################################################################################
mode = 2
mode_all = False
# ##############################################################################################################
# Exposure : get ds-wide percentages
if mode == 0 or mode_all:
    exposure_percentages = []
    for ds in ds_names:
        exposure_percentages.append(get_exposure_nums(ds, stats_dict)) 

    # Plotting
    y0 = np.array([item[0] for item in exposure_percentages])
    y1 = np.array([item[1] for item in exposure_percentages])
    y2 = np.array([item[2] for item in exposure_percentages])
    y3 = np.array([item[3] for item in exposure_percentages])
    y4 = np.array([item[4] for item in exposure_percentages])
    # plt.subplot(224)
    fig1 = plt.figure()
    fig1.set_size_inches([6,4])
    matplotlib.rcParams.update({'font.size': 16})
    plt.grid(zorder=0)
    plt.bar(ds_names,y0, color='k', width=0.35, zorder=3, edgecolor = "k")
    plt.bar(ds_names,y1, bottom=y0, color='b', width=0.35, zorder=3, edgecolor = "k")
    plt.bar(ds_names,y2, bottom=y0+y1, color='g', width=0.35, zorder=3, edgecolor = "k")
    plt.bar(ds_names,y3, bottom=y0+y1+y2, color='r', width=0.35, zorder=3, edgecolor = "k")
    plt.bar(ds_names,y4, bottom=y0+y1+y2+y3, color='y', width=0.35, zorder=3, edgecolor = "k")
    plt.xlabel('Dataset/Benchmark')
    plt.ylabel('Exposure Categories (%)')
    plt.legend(['Black', 'Under Exposed', 'Properly Exposed', 'Over Exposed', 'White' ], prop={'size': 10})
    # plt.xticks(rotation=-45)
    plt.tight_layout()
    plt.savefig(dirname+"/../out_data/agg_figs/exposure_percent_barchart.png")
    plt.show()
# ##############################################################################################################
# ##############################################################################################################
# Dynamic Range Coverage
# visualization of inertial dynamic range utilization/coverage
if mode == 1 or mode_all:
    categories = ['Gyro-x', 'Gyro-y', 'Gyro-z', 'Acc-x', 'Acc-y', 'Acc-z']
    EuroC_data = [
        stats_dict['EURO_C']['GX_DR_coverage_percent']['max'], 
        stats_dict['EURO_C']['GY_DR_coverage_percent']['max'], 
        stats_dict['EURO_C']['GZ_DR_coverage_percent']['max'], 
        stats_dict['EURO_C']['AX_DR_coverage_percent']['max'], 
        stats_dict['EURO_C']['AY_DR_coverage_percent']['max'], 
        stats_dict['EURO_C']['AZ_DR_coverage_percent']['max'], 
    ]

    TUMVI_data = [
        stats_dict['TUM_VI']['GX_DR_coverage_percent']['max'], 
        stats_dict['TUM_VI']['GY_DR_coverage_percent']['max'], 
        stats_dict['TUM_VI']['GZ_DR_coverage_percent']['max'], 
        stats_dict['TUM_VI']['AX_DR_coverage_percent']['max'], 
        stats_dict['TUM_VI']['AY_DR_coverage_percent']['max'], 
        stats_dict['TUM_VI']['AZ_DR_coverage_percent']['max'], 
    ]

    vis_fns.draw_radar_plot(categories, EuroC_data, TUMVI_data)
# ##############################################################################################################
# ##############################################################################################################
# Rotation Only stats
if mode == 2 or mode_all:
    KITTI_percent = 0
    EUROC_percent = round(((stats_dict[ds_names[1]]["ROT_ONLY_COUNT"]["sum"] / stats_dict[ds_names[1]]["AX"]["size"])*100),2)
    TUMVI_percent = round(((stats_dict[ds_names[2]]["ROT_ONLY_COUNT"]["sum"] / stats_dict[ds_names[2]]["AX"]["size"])*100),2)
    matplotlib.rcParams.update({'font.size': 14})
    fig1 = plt.figure()
    fig1.set_size_inches([6,4])
    plt.grid(zorder=0)
    barplot = plt.bar(ds_names,[KITTI_percent, EUROC_percent, TUMVI_percent], 
                        width=0.35, zorder=3, edgecolor = "k", 
                        color=['#d0535f', '#45a679', '#30abd4'])
    plt.bar_label(barplot)
    plt.xlabel('Dataset/Benchmark')
    plt.ylabel('Rotation Only Motion (%)')
    plt.tight_layout()
    plt.savefig(dirname+"/../out_data/agg_figs/rot_only_percent.png")
    plt.show()

    KITTI_count = 0
    EUROC_count = round((stats_dict[ds_names[1]]["ROT_ONLY_COUNT"]["sum"]),2)
    TUMVI_count = round((stats_dict[ds_names[2]]["ROT_ONLY_COUNT"]["sum"]),2)

    fig1 = plt.figure()
    fig1.set_size_inches([6,4])
    plt.grid(zorder=0)

    barplot = plt.bar(ds_names,[KITTI_count, EUROC_count, TUMVI_count], 
                        width=0.35, zorder=3, edgecolor = "k", 
                        color=['#d0535f', '#45a679', '#30abd4'])
    plt.bar_label(barplot)
    plt.xlabel('Dataset/Benchmark')
    plt.ylabel('Rotation Only Motion (Samples)')
    plt.tight_layout()
    plt.savefig(dirname+"/../out_data/agg_figs/rot_only_count.png")
    plt.show()
# ##############################################################################################################
# ##############################################################################################################
if mode == 3 or mode_all:
    #print the data for the H and SDI table for the paper
    print('\n\n\n\n\n')
    for tag in dg.general_tags:
        metric_title = titles_dict[tag]+" [$"+units_dict[tag]+"$]"
        KITTI_H = str(entropy_dict[tag][ds_names[0]])
        EUROC_H = str(entropy_dict[tag][ds_names[1]])
        TUMVI_H = str(entropy_dict[tag][ds_names[2]])

        KITTI_SDI = str(SDI_dict[tag][ds_names[0]])
        EUROC_SDI = str(SDI_dict[tag][ds_names[1]])
        TUMVI_SDI = str(SDI_dict[tag][ds_names[2]])
        print('\multicolumn{1}{l||}{'+metric_title+'} & '+KITTI_H+' & '+KITTI_SDI+' & '+EUROC_H+' & '+EUROC_SDI+' & '+TUMVI_H+' & '+TUMVI_SDI+' \\\\')

    print('\n\n\n\n\n')
    for tag in dg.inertial_tags:
        metric_title = titles_dict[tag]+" [$"+units_dict[tag]+"$]"
        KITTI_H = str(entropy_dict[tag][ds_names[0]])
        EUROC_H = str(entropy_dict[tag][ds_names[1]])
        TUMVI_H = str(entropy_dict[tag][ds_names[2]])

        KITTI_SDI = str(SDI_dict[tag][ds_names[0]])
        EUROC_SDI = str(SDI_dict[tag][ds_names[1]])
        TUMVI_SDI = str(SDI_dict[tag][ds_names[2]])
        print('\multicolumn{1}{l||}{'+metric_title+'} & '+KITTI_H+' & '+KITTI_SDI+' & '+EUROC_H+' & '+EUROC_SDI+' & '+TUMVI_H+' & '+TUMVI_SDI+' \\\\')

    print('\n\n\n\n\n')
    for tag in dg.visual_tags:
        metric_title = titles_dict[tag]+" [$"+units_dict[tag]+"$]"
        KITTI_H = str(entropy_dict[tag][ds_names[0]])
        EUROC_H = str(entropy_dict[tag][ds_names[1]])
        TUMVI_H = str(entropy_dict[tag][ds_names[2]])

        KITTI_SDI = str(SDI_dict[tag][ds_names[0]])
        EUROC_SDI = str(SDI_dict[tag][ds_names[1]])
        TUMVI_SDI = str(SDI_dict[tag][ds_names[2]])
        print('\multicolumn{1}{l||}{'+metric_title+'} & '+KITTI_H+' & '+KITTI_SDI+' & '+EUROC_H+' & '+EUROC_SDI+' & '+TUMVI_H+' & '+TUMVI_SDI+' \\\\')

# ##############################################################################################################
# ##############################################################################################################
if mode == 4 or mode_all:
    #plot the bar charts for the H and SDI table for the paper
    draw_bar_char_grouped(dg.general_tags, entropy_dict, 'Shannon Entropy (H)', (5,5), 'H_general')
    draw_bar_char_grouped(dg.inertial_tags, entropy_dict, 'Shannon Entropy (H)', (10,5), 'H_inertial')
    draw_bar_char_grouped(dg.visual_tags, entropy_dict, 'Shannon Entropy (H)', (15,5), 'H_visual')

    draw_bar_char_grouped(dg.general_tags, SDI_dict, 'Simpson Diversity Index (SDI)', (5,5), 'SDI_general')
    draw_bar_char_grouped(dg.inertial_tags, SDI_dict, 'Simpson Diversity Index (SDI)', (10,5), 'SDI_inertial')
    draw_bar_char_grouped(dg.visual_tags, SDI_dict, 'Simpson Diversity Index (SDI)', (15,5), 'SDI_visual')

    
# ##############################################################################################################
# ##############################################################################################################
if mode == 5 or mode_all:
    #print the data for the stats of metrics
    print('\n\n\n\n\n')
    for tag in dg.general_tags:
        metric_title = titles_dict[tag]+" [$"+units_dict[tag]+"$]"
        KITTI_mu    = str((stats_dict[ds_names[0]][tag]['mean']))
        KITTI_sigma = str(stats_dict[ds_names[0]][tag]['std_dev'])
        KITTI_str = KITTI_mu + " $\pm$ ("+KITTI_sigma+")"  

        EUROC_mu    = str(stats_dict[ds_names[1]][tag]['mean'])
        EUROC_sigma = str(stats_dict[ds_names[1]][tag]['std_dev'])
        EUROC_str = EUROC_mu + " $\pm$ ("+EUROC_sigma+")" 

        TUMVI_mu    = str(stats_dict[ds_names[2]][tag]['mean'])
        TUMVI_sigma = str(stats_dict[ds_names[2]][tag]['std_dev'])
        TUMVI_str = TUMVI_mu + " $\pm$ ("+TUMVI_sigma+")" 

        agg_mu    = str(agg_stats_dict[tag]['mean'])
        agg_sigma = str(agg_stats_dict[tag]['std_dev'])
        agg_str = agg_mu + " $\pm$ ("+agg_sigma+")"
        
        print('\multicolumn{1}{l||}{'+metric_title+'} & '+KITTI_str+'&'+EUROC_str+'&'+TUMVI_str+'&'+agg_str+'\\\\')

    print('\n\n\n\n\n')
    for tag in dg.inertial_tags:
        metric_title = titles_dict[tag]+" [$"+units_dict[tag]+"$]"
        KITTI_mu    = str((stats_dict[ds_names[0]][tag]['mean']))
        KITTI_sigma = str(stats_dict[ds_names[0]][tag]['std_dev'])
        KITTI_str = KITTI_mu + " $\pm$ ("+KITTI_sigma+")"  

        EUROC_mu    = str(stats_dict[ds_names[1]][tag]['mean'])
        EUROC_sigma = str(stats_dict[ds_names[1]][tag]['std_dev'])
        EUROC_str = EUROC_mu + " $\pm$ ("+EUROC_sigma+")" 

        TUMVI_mu    = str(stats_dict[ds_names[2]][tag]['mean'])
        TUMVI_sigma = str(stats_dict[ds_names[2]][tag]['std_dev'])
        TUMVI_str = TUMVI_mu + " $\pm$ ("+TUMVI_sigma+")" 

        agg_mu    = str(agg_stats_dict[tag]['mean'])
        agg_sigma = str(agg_stats_dict[tag]['std_dev'])
        agg_str = agg_mu + " $\pm$ ("+agg_sigma+")"
        
        print('\multicolumn{1}{l||}{'+metric_title+'} & '+KITTI_str+'&'+EUROC_str+'&'+TUMVI_str+'&'+agg_str+'\\\\')

    print('\n\n\n\n\n')
    for tag in dg.visual_tags:
        metric_title = titles_dict[tag]+" [$"+units_dict[tag]+"$]"
        KITTI_mu    = str((stats_dict[ds_names[0]][tag]['mean']))
        KITTI_sigma = str(stats_dict[ds_names[0]][tag]['std_dev'])
        KITTI_str = KITTI_mu + " $\pm$ ("+KITTI_sigma+")"  

        EUROC_mu    = str(stats_dict[ds_names[1]][tag]['mean'])
        EUROC_sigma = str(stats_dict[ds_names[1]][tag]['std_dev'])
        EUROC_str = EUROC_mu + " $\pm$ ("+EUROC_sigma+")" 

        TUMVI_mu    = str(stats_dict[ds_names[2]][tag]['mean'])
        TUMVI_sigma = str(stats_dict[ds_names[2]][tag]['std_dev'])
        TUMVI_str = TUMVI_mu + " $\pm$ ("+TUMVI_sigma+")" 

        agg_mu    = str(agg_stats_dict[tag]['mean'])
        agg_sigma = str(agg_stats_dict[tag]['std_dev'])
        agg_str = agg_mu + " $\pm$ ("+agg_sigma+")"
        
        print('\multicolumn{1}{l||}{'+metric_title+'} & '+KITTI_str+'&'+EUROC_str+'&'+TUMVI_str+'&'+agg_str+'\\\\')

# ##############################################################################################################
# ##############################################################################################################
if mode == 6 or mode_all:
    brightness_vals = []
    for ds in ds_names:
        brightness_vals.append(get_brightness_vals(ds, stats_dict))

    print(brightness_vals)

    x = np.arange(len(ds_names))
    width = 0.25
    fig, ax = plt.subplots(figsize=([6,4]))
    rects1 = ax.bar(x-width, [item[0] for item in brightness_vals], width, label='KITTI', color='#d0535f', edgecolor='black', zorder=3)
    rects2 = ax.bar(x, [item[1] for item in brightness_vals], width, label='EuroC-MAV', color='#45a679', edgecolor='black', zorder=3)
    rects3 = ax.bar(x+width, [item[2] for item in brightness_vals], width, label='TUM-VI', color='#30abd4', edgecolor='black', zorder=3)

    # Add some text for labels, title and custom x-axis tick labels, etc.
    ax.set_ylabel('Brightness Diff. [% dBr/dt > \u03B1\u03C3]')
    ax.set_xticks(x)
    ax.set_xticklabels(ds_names)
    ax.legend(['dBr/dt > 1\u03C3', 'dBr/dt > 2\u03C3', 'dBr/dt > 3\u03C3'], loc='upper center', bbox_to_anchor=(0.5, 1.2),fancybox=True, ncol=3)
    ax.grid(zorder=0)
    # plt.bar_label(rects1, rotation='vertical', padding=5)
    # plt.bar_label(rects2, rotation='vertical', padding=5)
    # plt.bar_label(rects3, rotation='vertical', padding=5)
    plt.tight_layout()
    plt.savefig(dirname+"/../out_data/agg_figs/brightness_diff.png")
    plt.show()

# ##############################################################################################################
# ##############################################################################################################
if mode == 7 or mode_all:
    H_SDI_boxplot(entropy_dict,  dg.general_tags, 'H_general', 'Entropy (H)')
    H_SDI_boxplot(entropy_dict,  dg.general_tags, 'H_general', 'Entropy (H)')
    H_SDI_boxplot(entropy_dict,  dg.inertial_tags, 'H_inertial', 'Entropy (H)')
    H_SDI_boxplot(entropy_dict,  dg.visual_tags, 'H_visual', 'Entropy (H)')
    
    print('\n\n')

    H_SDI_boxplot(SDI_dict,  dg.general_tags, 'SDI_general', 'Simpson Diversity Index (SDI)')
    H_SDI_boxplot(SDI_dict,  dg.inertial_tags, 'SDI_inertial', 'Simpson Diversity Index (SDI)')
    H_SDI_boxplot(SDI_dict,  dg.visual_tags, 'SDI_visual', 'Simpson Diversity Index (SDI)')
        
    