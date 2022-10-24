import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import ptitprince as pt

# extract currenty directory name for path adjustification
dirname = os.path.dirname(__file__)+'/..'

def draw_raincloud(data, plot_props):
    pal = sns.color_palette(plot_props['colors'])
    ort = 'v'

    ax=pt.half_violinplot(data = data, palette = pal, bw = 0.2, cut = 0.,edgecolor = "none",
    scale = "area", width = 0.5, inner = None, orient = ort)

    ax=sns.stripplot(data = data, palette = pal, edgecolor = "none",
    size = 1, jitter = 1, zorder = 1, orient = ort)

    ax=sns.boxplot(data = data, color = "black", width = 0.1, zorder = 10,
    showcaps = True, boxprops = {'facecolor':'none', "zorder":10},
    showfliers=True, whiskerprops = {'linewidth':0.5, "zorder":10},
    showmeans=True, meanprops=dict(marker='o', markerfacecolor='black', markeredgecolor='black', markersize=3, zorder=3),
    saturation = 0.3, orient = ort)

    plt.xlabel(plot_props['ylabel'])
    plt.ylabel(plot_props['xlabel'])
    ax.set_xticklabels(plot_props['labels'], rotation='0')
    plt.grid(True)
    
# ==================================================================
def bar_plotting(data_dict, ylabel_str, folder_name, in_ylim = 0):

    for key in data_dict:
        print("Bar Chart Plotting: "+ folder_name + " "+ key)
        y_val = []
        x_val = []
        for ds in data_dict[key]:
            y_val.append(data_dict[key][ds])
            x_val.append(ds)
        x_pos = np.arange(len(x_val))

        # Create bars with different colors
        # fig1 = plt.figure("")
        # fig1.set_size_inches([6,10])
        barplot = plt.bar(x_pos, y_val, color=['#d0535f', '#45a679', '#30abd4'], width = 0.5, edgecolor='black')

        # Create names on the x-axis
        plt.xticks(x_pos, x_val)
        plt.xlabel(key)
        plt.ylabel(ylabel_str)
        # plt.title(ylabel_str+" for "+key)
        plt.grid()
        if (in_ylim > 0):
            plt.ylim([0,in_ylim])
        plt.bar_label(barplot)
        

        plt.savefig(dirname+"/../out_data/agg_figs/"+folder_name+"/barchart_"+key+".png")
        plt.close('all')

# ==================================================================
def draw_KDE_plot(data1, data2, data3, tag):
    sns.kdeplot(np.array(data1),color='#d0535f', linewidth=1, bw_method="silverman", shade=True, label='KITTI', )
    sns.kdeplot(np.array(data2),color='#45a679', linewidth=1, bw_method="silverman", shade=True, label='EURO-C MAV')
    sns.kdeplot(np.array(data3),color='#30abd4', linewidth=1, bw_method="silverman", shade=True, label='TUM-VI')

    plt.xlabel(tag)
    plt.ylabel('Probability Density')
    plt.grid(True, linestyle=":", color='gray')
    plt.legend()


def draw_radar_plot(categories, EuroC_data, TUMVI_data):
    categories = [*categories, categories[0]]
    EuroC_data = [*EuroC_data, EuroC_data[0]]
    TUMVI_data = [*TUMVI_data, TUMVI_data[0]]

    label_loc = np.linspace(start=0, stop=2 * np.pi, num=len(EuroC_data))

    ax = plt.subplot(polar=True)
    plt.yticks([10,20,30,40], ["10%", "20%", "30%", "40%"], color="grey", size=7)
    plt.ylim(0,40)
    plt.plot(label_loc, EuroC_data, label='EuroC')
    plt.fill(label_loc, EuroC_data, 'b', alpha=0.1)
    plt.plot(label_loc, TUMVI_data, label='TUM-VI')
    plt.fill(label_loc, TUMVI_data, 'r', alpha=0.1)
    lines, labels = plt.thetagrids(np.degrees(label_loc), labels=categories)

    # remove extra white spaces
    plt.tight_layout()
    # get box dimensions in order to center the legend
    box = ax.get_position()
    ax.set_position([box.x0, box.y0 + box.height * 0.1, box.width, box.height * 0.9])
    # Put a legend below current axis
    ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.05), fancybox=True, ncol=5)
    plt.savefig(dirname+"/../out_data/agg_figs/inertial_DR_radar.png")
    plt.show()