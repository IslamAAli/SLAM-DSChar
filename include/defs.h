#ifndef DEFS_H
#define DEFS_H

#include "common.h"

enum IMG_STEREO_SEQ{
    RIGHT_SEQ,
    LEFT_SEQ
};

enum SENSOR_DATA{
    VISUAL_DATA,
    INERTIAL_DATA
};
enum SYS_CMD{
    CMD_RUN_ALL,
    CMD_RUN_REVISIT_FREQ,
    CMD_RUN_CONTRAST,
    CMD_RUN_BRIGHTNESS,
    CMD_RUN_INERTIAL_DR,
    CMD_RUN_INERTIAL_DIFF, 
    CMD_RUN_FEATURES, 
    CMD_RUN_BLUR, 
    CMD_RUN_GENERAL_CHAR,
    CMD_RUN_DISPARITY, 
    CMD_RUN_EXPOSURE,
    CMD_RUN_INERTIAL_ROT_ONLY,
    CMD_RUN_KEYFRAMES
};

enum DISPARITY_ALGO{
    STEREO_BM,
    STEREO_SGBM
};

enum CMD_ERROR{
    INERTIAL_DATA_ERROR,
    STEREO_DATA_ERROR
};

enum VISUAL_FEATURES{
    VF_SIFT,
    VF_ORB,
    VF_FAST
};

enum EXPORT_MODE
{
    EXPORT_TXT,
    EXPORT_DAT,
    EXPORT_ALL
};

enum INERTIAL_MODE
{
    GYRO_X,
    GYRO_Y,
    GYRO_Z,
    ACC_X,
    ACC_Y,
    ACC_Z
};

enum EXPOSURE_STATUS{
    PROPER_EXPOSURE,
    UNDER_EXPOSURE,
    OVER_EXPOSURE,
    BLACK_EXPOSURE,
    WHITE_EXPOSURE
};

struct tuple_score_entry{
    int x_id; 
    int y_id;
    double score_val;
};

struct features_score_entry{
    int features_count;
    double spatial_dist_ratio_abs;
    double spatial_dist_ratio_avg;
};

struct file_name_package{
    string tag;
    string ds_name;
    string seq_name;
    string extension = ".txt";
};

struct vector_stats
{
    double arith_mean;
    double geo_mean;
    double std_dev;
    double var;
    double skewness;
    double min;
    double max;
    double count;
};

namespace DS_CONFIG_PARAM
{
    extern const string DS_PARAM_BASE_PATH;
    extern const string DS_PARAM_SEQ_COUNT;
    extern const string DS_PARAM_STEREO;
    extern const string DS_PARAM_IMU;
    extern const string DS_PARAM_GYRO_DR_POS;
    extern const string DS_PARAM_GYRO_DR_NEG;
    extern const string DS_PARAM_ACC_DR_POS;
    extern const string DS_PARAM_ACC_DR_NEG;
}

namespace CONFIG
{   
    extern const double CONFIG_DBOW2_MIN_SCORE;
    extern const string CONFIG_IN_PATH;
    extern const string CONFIG_IN_PATH_TEMPLATES;
    extern const string CONFIG_OUT_PATH;
    extern const string CONFIG_OUT_PATH_REPORTS;
    extern const string CONFIG_OUT_PATH_TIKZ_FIGS;
    extern const string CONFIG_OUT_PATH_TEX_REPORTS;
    extern const string CONFIG_OUT_PATH_DATASET_REPORTS;
    extern const bool CONFIG_DEBUG;
    extern const int CONFIG_VERBOSE;
    extern const int CONFIG_VERBOSE_RATE;
    extern const double CONFIG_INERTIAL_DR_PERCENTAGE;
    extern const double CONFIG_FEATURES_RATIO_BIN_SIZE;
    extern const EXPORT_MODE CONFIG_EXPORT_MODE;
    extern string DATASET_NAME;
    extern const int CONFIG_CONTRAST_KERNEL_SIZE;
    extern const double CONFIG_BLUR_BIN_SIZE;
    extern const double CONFIG_BLUR_THRESH;
    extern const double CONFIG_GRAVITY_VAL;
    extern const double CONFIG_GRAVITY_ERR_PERCENT;
    extern const bool   CONFIG_DISPARITY_RECTIFY;
}

namespace FILE_NAMES
{
    extern const string FILE_TIKZ_PLOT_TEMPLATE;
}


#endif
