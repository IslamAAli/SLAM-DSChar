import glob
import os
import re
import shutil

# ===========================================================================================
# Categorization Function
# ===========================================================================================
def categorizer(ds_name, dirname, in_folder, out_folder, mode='*'):

    dir_string = dirname+"/../out_data/"+in_folder+"/"+ds_name+"/*."+mode

    for file in glob.glob(dir_string):
        
        file_name = os.path.basename(file)
        category = re.search(r"\[([A-Za-z0-9_]+)\]", file_name).group(1)

        print(ds_name+"\t\t"+category+'\t\t'+file_name)
        
        folder_name = dirname+"/../out_data/"+out_folder+"/"+ds_name+'/'+category
        
        if not os.path.exists(folder_name):
            os.mkdir(folder_name)
            shutil.copy(file, folder_name)
        else:
            shutil.copy(file, folder_name)


# ===========================================================================================
# Extract Current Directory details
# ===========================================================================================
dirname = os.path.dirname(__file__)+'/..'

# ===========================================================================================
# Categorization Execution
# ===========================================================================================
ds_names = ['KITTI', 'EURO_C', 'TUM_VI']


for ds in ds_names:
    categorizer(ds, dirname, 'reports', 'reports_categorized', 'txt')
    categorizer(ds, dirname, 'tikz_figures', 'tikz_figures_categorized', '*')
