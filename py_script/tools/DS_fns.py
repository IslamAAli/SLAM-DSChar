import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import ptitprince as pt
import re
import shutil
import glob

# --------------------------------------------------------------
dlabels_EURO_C = [
        'MH_01_easy'
        ,'MH_02_easy'
        ,'MH_03_medium'
        ,'MH_04_difficult'
        ,'MH_05_difficult'
        ,'V1_01_easy'
        ,'V1_02_medium'
        ,'V1_03_difficult'
        ,'V2_01_easy'
        ,'V2_02_medium'
        ,'V2_03_difficult'
    ]

dlabels_KITTI = [  
            '00',
            '01',
            '02',
            '03',
            '04',
            '05',
            '06',
            '07',
            '08',
            '09',
            '10',
            '11',
            '12',
            '13',
            '14',
            '15',
            '16',
            '17',
            '18',
            '19',
            '20',
            '21']

dlabels_TUM_VI = [
        'corridor1'
        ,'corridor2'
        ,'corridor3'
        ,'corridor4'
        ,'corridor5'
        ,'magistrale1'
        ,'magistrale2'
        ,'magistrale3'
        ,'magistrale4'
        ,'magistrale5'
        ,'magistrale6'
        ,'outdoors1'
        ,'outdoors2'
        ,'outdoors3'
        ,'outdoors4'
        ,'outdoors5'
        ,'outdoors6'
        ,'outdoors7'
        ,'outdoors8'
        ,'room1'
        ,'room2'
        ,'room3'
        ,'room4'
        ,'room5'
        ,'room6'
        ,'slides1'
        ,'slides2'
        ,'slides3'
        ]
# --------------------------------------------------------------
dirname = os.path.dirname(__file__)+'/..'
# --------------------------------------------------------------
def read_files(files_list, filter=False, filterVal = 0):
    data= []
    for filename in files_list:
        fn = os.path.join(dirname, filename)
        if os.path.isfile(fn):
            with open(fn) as f:
                lines = f.read().splitlines()

            if filter:
                lines =  [i if float(i) > filterVal else 0 for i in lines]

            data.append(list(map(float, lines)))

    return data

# --------------------------------------------------------------
def filenames_euroc_creator(tag, filter=False, filterVal = 0):
    # read data from files
    filenames = [
         '../out_data/reports/EURO_C/['+tag+']EURO_C_MH_01_easy.txt'
        ,'../out_data/reports/EURO_C/['+tag+']EURO_C_MH_02_easy.txt'
        ,'../out_data/reports/EURO_C/['+tag+']EURO_C_MH_03_medium.txt'
        ,'../out_data/reports/EURO_C/['+tag+']EURO_C_MH_04_difficult.txt'
        ,'../out_data/reports/EURO_C/['+tag+']EURO_C_MH_05_difficult.txt'
        ,'../out_data/reports/EURO_C/['+tag+']EURO_C_V1_01_easy.txt'
        ,'../out_data/reports/EURO_C/['+tag+']EURO_C_V1_02_medium.txt'
        ,'../out_data/reports/EURO_C/['+tag+']EURO_C_V1_03_difficult.txt'
        ,'../out_data/reports/EURO_C/['+tag+']EURO_C_V2_01_easy.txt'
        ,'../out_data/reports/EURO_C/['+tag+']EURO_C_V2_02_medium.txt'
        ,'../out_data/reports/EURO_C/['+tag+']EURO_C_V2_03_difficult.txt'
    ]

    return read_files(filenames, filter, filterVal), dlabels_EURO_C

# --------------------------------------------------------------
def filename_kitti_creator(tag, filter=False, filterVal = 0):
    # read data from files
    filenames = [
         '../out_data/reports/KITTI/['+tag+']KITTI_00.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_01.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_02.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_03.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_04.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_05.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_06.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_07.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_08.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_09.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_10.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_11.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_12.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_13.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_14.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_15.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_16.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_17.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_18.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_19.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_20.txt'
        ,'../out_data/reports/KITTI/['+tag+']KITTI_21.txt'
    ]

    return read_files(filenames, filter, filterVal), dlabels_KITTI

# --------------------------------------------------------------
def filename_tumvi_creator(tag, filter=False, filterVal = 0):
    # read data from files
    filenames = [
        '../out_data/reports/TUM_VI/['+tag+']TUM_VI_corridor1.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_corridor2.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_corridor3.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_corridor4.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_corridor5.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_magistrale1.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_magistrale2.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_magistrale3.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_magistrale4.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_magistrale5.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_magistrale6.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_outdoors1.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_outdoors2.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_outdoors3.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_outdoors4.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_outdoors5.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_outdoors6.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_outdoors7.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_outdoors8.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_room1.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_room2.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_room3.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_room4.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_room5.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_room6.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_slides1.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_slides2.txt'
        ,'../out_data/reports/TUM_VI/['+tag+']TUM_VI_slides3.txt'
        ]

    return read_files(filenames, filter, filterVal), dlabels_TUM_VI

# --------------------------------------------------------------
def filename_creator(ds_name, tag, filter=False, filterVal = 0):
    if ds_name == 'KITTI':
        files, labels = filename_kitti_creator(tag, filter, filterVal)
    elif ds_name == 'EURO_C':
        files, labels = filenames_euroc_creator(tag, filter, filterVal)
    elif ds_name == 'TUM_VI':
        files, labels = filename_tumvi_creator(tag, filter, filterVal)
    else:
        files, labels = None, None
        print('ERROR: Unidentified Dataset !!')

    return files, labels

def seq_names_retriever(ds_name):
    if ds_name == 'KITTI':
        return dlabels_KITTI
    elif ds_name == 'EURO_C':
        return dlabels_EURO_C
    elif ds_name == 'TUM_VI':
        return dlabels_TUM_VI
    else:
        print('ERROR: Unidentified Dataset !!')
        return None

# --------------------------------------------------------------
def get_category_names(ds_name, dirname, in_folder):
    print(">>> Extracting Categories")
    category_list = []
    for file in glob.glob(dirname+"/../out_data/"+in_folder+"/"+ds_name+"/*.*"):
        
        file_name = os.path.basename(file)
        category = re.search(r"\[([A-Za-z0-9_]+)\]", file_name).group(1)
        category_list.append(category)

    category_list = list(dict.fromkeys(category_list))
    category_list.sort()
    return category_list

# --------------------------------------------------------------
def get_file_list(ds_name, dirname, in_folder, tag):
    print("# ["+ds_name+"] "+tag)
    print(">>> Reading file list")

    file_list = []
    for file in glob.glob(dirname+"/../out_data/"+in_folder+"/"+ds_name+"/*.txt"):
        
        file_name = os.path.basename(file)

        if(("["+tag+"]") not in file_name):
            continue
        else:
            file_list.append(file)
    
    return file_list

# --------------------------------------------------------------
def read_file_data(file_path):
    data = []
    file_in = open(file_path, 'r')
    for y in file_in.read().split('\n'):
        if y != '':
            data.append(float(y))

    return data

# --------------------------------------------------------------
def read_ds_data_aggregate(ds_names, meta_categories):
    # create list of dictionaries for each dataset
    ds_eval_data = {}
    for ds in ds_names:
        ds_eval_data[ds] = {}

    # for each dataset, find the stats of each 
    for ds in ds_names:
        file_list = []
        print("## Processing: "+ds)
        for cat in meta_categories:
            # get file list for each category for the selected data set
            file_list = get_file_list(ds, dirname, 'reports', cat)

            # get aggregated data for each category
            cat_data = []
            for cat_file in file_list:
                cat_data += read_file_data(cat_file)

            # calculate the stats of this aggregated data and add information to final dict
            ds_eval_data[ds][cat] = cat_data
    
    return ds_eval_data, meta_categories

# --------------------------------------------------------------
def get_meta_categories(ds_names, non_data_item):
    # global list to include all comparison items
    meta_categories = []

    # extract available categories in each dataset
    for ds in ds_names:
        print("## Reading: "+ds)
        cat_list = get_category_names(ds, dirname, 'reports')
        meta_categories += cat_list
        print("")

    # remove duplicates and sort the meta categories list
    meta_categories = list(dict.fromkeys(meta_categories))
    meta_categories.sort()

    # remove non-data files
    for item in non_data_item:
        meta_categories.remove(item)
    
    return meta_categories