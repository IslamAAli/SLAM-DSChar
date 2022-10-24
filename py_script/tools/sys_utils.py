from cv2 import cv2
import numpy as np
import os
import glob
import math
import pickle
import json

def read_files_from_path(relative_path, file_wildcard):
    dirname = os.path.dirname(__file__)+relative_path

    # read the images from the input folder
    files = []
    file_names = []
    for file in glob.glob(dirname+file_wildcard):
        files.append(file)
        file_names.append(os.path.basename(file))

    return files, file_names

def export_dict(path, filname,  data):
    #numpy dict
    np.save(path+filname+".npy", data)  

    #json dict
    json.dump(data, open(path+filname+".json", 'w')) 

    #pickle
    with open(path+filname+".pkl", 'wb+') as f:
        pickle.dump(data, f)

def import_dict(path, filname):
    #numpy  
    npy_dict = np.load(path+filname+".npy",allow_pickle='TRUE').item()

    #json
    json_dict = json.load(open(path+filname+".json"))

    # pickle
    with open(path+filname+".pkl", 'rb') as f:
        pkl_dict = pickle.load(f)

    return npy_dict, json_dict, pkl_dict

def export_dict_npy(path, filname,  data):
    #numpy dict
    np.save(path+filname+".npy", data)  

def import_dict_npy(path, filname):
    #numpy  
    npy_dict = np.load(path+filname+".npy",allow_pickle='TRUE').item()

    return npy_dict


def export_list(file_path, m_list):
    with open(file_path, "wb") as fp:   #Pickling
        pickle.dump(m_list, fp)

    textfile = open(file_path+".txt", "w")
    for element in m_list:
        textfile.write(element + "\n")
    textfile.close()

def import_list(file_path):
    with open(file_path, "rb") as fp:   # Unpickling
        m_list = pickle.load(fp)

    return m_list