import csv
import pandas as pd
import math

# ====================
# functions
# ====================
def extract_timestamp_data_visual(file_name, dir_path):
    print ('=> Processing Visual CSV file ...')

    # read the csv file  (timestamps are read in ns)
    file_path   = dir_path + file_name
    data        = pd.read_csv(file_path)
    data_list   = data['#timestamp [ns]'].tolist()
    print ('\tINPUT:  ', file_path)

    # output the timestamps text file in seconds
    out_file_path = dir_path+"timestamps.txt"
    print ('\tOUTPUT: ', out_file_path)
    with open(out_file_path, 'w') as f:
        for item in data_list:
            time_sec = float(item) / (10**9)
            f.write("%s\n" % time_sec)

# --------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------

def extract_timestamp_data_inertial(file_name, dir_path):
    print ('=> Processing Inertial CSV file ...')

    # read the csv file  (timestamps are read in ns)
    file_path   = dir_path + file_name
    data        = pd.read_csv(file_path)
    data_list   = data['#timestamp [ns]'].tolist()

    gyro_x      = data['w_RS_S_x [rad s^-1]'].tolist()
    gyro_y      = data['w_RS_S_y [rad s^-1]'].tolist()
    gyro_z      = data['w_RS_S_z [rad s^-1]'].tolist()

    acc_x       = data['a_RS_S_x [m s^-2]'].tolist()
    acc_y       = data['a_RS_S_y [m s^-2]'].tolist()
    acc_z       = data['a_RS_S_z [m s^-2]'].tolist()
    
    print ('\tINPUT:  ', file_path)

    # output the timestamps text file in seconds
    out_file_path = dir_path+"timestamps.txt"
    print ('\tOUTPUT: ', out_file_path)
    with open(out_file_path, 'w') as f:
        for item in data_list:
            time_sec = float(item) / (10**9)
            f.write("%s\n" % time_sec)
    
    # output the inertial data text file in deg/sec and m/sec^2
    out_file_path = dir_path+"inertial_data.txt"
    print ('\tOUTPUT: ', out_file_path)
    with open(out_file_path, 'w') as f:
        for (gx, gy, gz, ax, ay, az) in zip(gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z):
            gx_fixed = gx * 180 / math.pi
            gy_fixed = gy * 180 / math.pi
            gz_fixed = gz * 180 / math.pi
            f.write("%s %s %s %s %s %s\n" % (gx_fixed, gy_fixed, gz_fixed, ax, ay, az))

# --------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------
def process_timestamp(seq_list, pre_path, post_path_1, post_path_2, post_path_3, filename):
    for seq in seq_list:
        # process the left camera
        dp = pre_path +seq +post_path_1
        extract_timestamp_data_visual(filename, dp)

        # process the right camera
        dp = pre_path +seq +post_path_2
        extract_timestamp_data_visual(filename, dp)

        dp = pre_path +seq +post_path_3
        extract_timestamp_data_inertial(filename, dp)

        print ('=> Processing Complete ...\n')

# ====================
# Main script
# ====================
def main():
    
    # EuroC MAV sequences
    EuroC_Seq = [   
        'MH_01_easy', 
        'MH_02_easy',
        'MH_03_medium',
        'MH_04_difficult',
        'MH_05_difficult', 
        'V1_01_easy',
        'V1_02_medium',
        'V1_03_difficult',
        'V2_01_easy',
        'V2_02_medium',
        'V2_03_difficult'
    ]

    TUM_VI_Seq = [
        'calib-cam1',
        'calib-cam2',
        'calib-cam3',
        'calib-cam4',
        'calib-cam5',
        'calib-cam6',
        'calib-cam7',
        'calib-cam8',
        'calib-imu1',
        'calib-imu2',
        'calib-imu3',
        'calib-imu4',
        'calib-vignette2',
        'calib-vignette3',
        'corridor1',
        'corridor2',
        'corridor3',
        'corridor4',
        'corridor5',
        'magistrale1',
        'magistrale2',
        'magistrale3',
        'magistrale4',
        'magistrale5',
        'magistrale6',
        'outdoors1',
        'outdoors2',
        'outdoors3',
        'outdoors4',
        'outdoors5',
        'outdoors6',
        'outdoors7',
        'outdoors8',
        'room1',
        'room2',
        'room3',
        'room4',
        'room5',
        'room6',
        'slides1',
        'slides2',
        'slides3'
    ]
    
    process_timestamp(EuroC_Seq,
                        '/home/islamali/work_area/datasets/EuroC/', 
                        '/mav0/cam0/', '/mav0/cam1/',  '/mav0/imu0/', 
                        'data.csv')

    process_timestamp(TUM_VI_Seq,
                        '/media/islamali/SeagateEHD/SLAM_Datasets/tumvi/exported/euroc/512_16/', 
                        '/mav0/cam0/', '/mav0/cam1/',  '/mav0/imu0/', 
                        'data.csv')
    
if __name__ == "__main__":
    main()