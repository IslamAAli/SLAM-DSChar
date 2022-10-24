import matplotlib.pyplot as plt
import os

dirname = os.path.dirname(__file__)
plt_type = 1
# =============================================================================================
# Datasets Release date Bar chart
# =============================================================================================
if plt_type ==1:
    year = [2009, 2010, 2011, 2012,2013,2014,2015,2016,2017,2018,2019,2020,2021]
    old = [0,3,5,8,11,13,13,15,22,26,35,43,49]
    new = [3,2,3,3,2,0,2,7,4,9,8,6,6]
    # =====
    plt.subplot(211)
    # plt.figure(figsize=(10, 6))
    plt.grid(axis='y', zorder=0)
    splot1 = plt.bar(year, old, 0.6, label='Available Datasets', color='#1A77F5',zorder=3,edgecolor='black')
    splot2 = plt.bar(year, new, 0.6, bottom=old, label='New Datasets', color='#F85836', zorder=3, edgecolor='black')
    plt.xlabel('Year')
    plt.ylabel('# SLAM Datasets')
    plt.title('SLAM Datasets Release Dates')
    plt.legend()
    plt.xticks(year)
    plt.bar_label(splot2)
    # plt.tight_layout()
    # plt.show()

# =============================================================================================
# Sensors Popularity Bar chart
# =============================================================================================
    sensor = ['IMU (Gyro)','IMU (Acc)','Wheel Odom.','GPS/GNSS',
    'Mono Cam','Stereo Cam','Omni Cam','IR Cam','Depth Cam',
    'LiDAR','Event Cam','Ref. Data','Total']
    # total = [0,0,0,0,0,0,0,0,0,0,0,0,55]
    sensor_count = [37,39,5,24,27,32,6,3,13,19,5,30, 55]
    # =====
    plt.subplot(212)
    # plt.figure(figsize=(10, 6))
    plt.grid(axis='y', zorder=0)
    splot = plt.bar(sensor, sensor_count, 0.6, label='Sensor Popularity', color='#1A77F5',zorder=3, edgecolor='black')
    splot[12].set_color('#F85836')
    splot[12].set_edgecolor('black')
    # plt.bar(sensor, total, 0.6, bottom=sensor_count, label='Total # Datasets', color='#F85836', zorder=3,edgecolor='black')
    plt.xlabel('Sensor')
    plt.ylabel('# of Appearances in Datasets')
    plt.xticks(rotation=60)
    # plt.legend()
    plt.bar_label(splot)
    plt.title('Sensors\' Popularity Among SLAM Datasets')
    plt.tight_layout()
    plt.show()

# =============================================================================================
# Dataset characteristics donut charts
# =============================================================================================
if plt_type == 3:
    plt.subplot(331)
    wedgeprops = {'width':0.4, 'edgecolor':'black', 'linewidth':2}
    data = [48,5,2]
    labels = ['Real', 'Synthetic', 'Both']
    labels = [f'{l}, {s:0.1f}%' for l, s in zip(labels, data)]
    plt.pie(data, labels=labels, startangle=90, wedgeprops=wedgeprops)
    plt.title('Real vs. Synethic Data', loc='center', y=1.0, pad=20, fontweight='bold')

    plt.subplot(332)
    data = [49,6]
    labels = ['No', 'Yes']
    labels = [f'{l}, {s:0.1f}%' for l, s in zip(labels, data)]
    plt.pie(data, labels=labels, startangle=90, wedgeprops=wedgeprops)
    plt.title('Dataset Semantic Labels', loc='center', y=1.0, pad=20, fontweight='bold')

    plt.subplot(333)
    data = [51,4]
    labels = ['No', 'Yes']
    labels = [f'{l}, {s:0.1f}%' for l, s in zip(labels, data)]
    plt.pie(data, labels=labels, startangle=90, wedgeprops=wedgeprops)
    plt.title('Multi-Robot Support', loc='center', y=1.0, pad=20, fontweight='bold')

    plt.subplot(334)
    data = [49,6]
    labels = ['No', 'Yes']
    labels = [f'{l}, {s:0.1f}%' for l, s in zip(labels, data)]
    plt.pie(data, labels=labels, startangle=90, wedgeprops=wedgeprops)
    plt.title('HDR Imaging', loc='center', y=1.0, pad=20, fontweight='bold')

    plt.subplot(335)
    data = [8,47]
    labels = ['No', 'Yes']
    labels = [f'{l}, {s:0.1f}%' for l, s in zip(labels, data)]
    plt.pie(data, labels=labels, startangle=90, wedgeprops=wedgeprops)
    plt.title('Ground Truth', loc='center', y=1.0, pad=20, fontweight='bold')

    plt.subplot(336)
    data = [16,9,1,20,5,4]
    labels = ['Car','UGV','Canoe','Handheld','UAV','Hybrid']
    labels = [f'{l}, {s:0.1f}%' for l, s in zip(labels, data)]
    plt.pie(data, labels=labels, startangle=90, wedgeprops=wedgeprops)
    plt.title('Carrier Platform', loc='center', y=1.0, pad=20, fontweight='bold')
    
    plt.subplot(337)
    data = [47,1,7]
    labels = ['Land', 'Water', 'Hybrid']
    labels = [f'{l}, {s:0.1f}%' for l, s in zip(labels, data)]
    plt.pie(data, labels=labels, startangle=90, wedgeprops=wedgeprops)
    plt.title('Environment Scene', loc='center', y=1.0, pad=20, fontweight='bold')

    plt.subplot(338)
    data = [35,4,16]
    labels = ['Uncontrolled','Hybrid','Controlled']
    labels = [f'{l}, {s:0.1f}%' for l, s in zip(labels, data)]
    plt.pie(data, labels=labels, startangle=90, wedgeprops=wedgeprops)
    plt.title('Environment Engineering', loc='center', y=1.0, pad=20, fontweight='bold')

    plt.subplot(339)
    data = [25,14,16]
    labels = ['Outdoor','Indoor','Both']
    labels = [f'{l}, {s:0.1f}%' for l, s in zip(labels, data)]
    plt.pie(data, labels=labels, startangle=90, wedgeprops=wedgeprops)
    plt.title('Indoor vs. Outdoor', loc='center', y=1.0, pad=20, fontweight='bold')

    # plt.tight_layout()
    plt.show()

# =============================================================================================
# Box plots
# =============================================================================================
if plt_type ==4:
    print()