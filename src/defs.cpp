#include "common.h"

namespace DS_CONFIG_PARAM
{
    const string DS_PARAM_BASE_PATH     = "base_path";
    const string DS_PARAM_SEQ_COUNT     = "seq_count";
    const string DS_PARAM_STEREO        = "stereo";
    const string DS_PARAM_IMU           = "imu";
    const string DS_PARAM_GYRO_DR_POS   = "g_DR_pos";
    const string DS_PARAM_GYRO_DR_NEG   = "g_DR_neg";
    const string DS_PARAM_ACC_DR_POS    = "a_DR_pos";
    const string DS_PARAM_ACC_DR_NEG    = "a_DR_neg";
}

namespace CONFIG
{
    const double        CONFIG_DBOW2_MIN_SCORE          = 0.9;
    const string        CONFIG_IN_PATH                  = "../in_data/";
    const string        CONFIG_IN_PATH_TEMPLATES        = "../in_data/templates/";
    const string        CONFIG_OUT_PATH                 = "../out_data/";
    const string        CONFIG_OUT_PATH_REPORTS         = "../out_data/reports/";
    const string        CONFIG_OUT_PATH_TIKZ_FIGS       = "../out_data/tikz_figures/";
    const string        CONFIG_OUT_PATH_DATASET_REPORTS = "../out_data/dataset_reports/";
    const string        CONFIG_OUT_PATH_TEX_REPORTS     = "../reports/";
    const bool          CONFIG_DEBUG                    = true;
    const int           CONFIG_VERBOSE                  = 0;
    const int           CONFIG_VERBOSE_RATE             = 20;
    const double        CONFIG_INERTIAL_DR_PERCENTAGE   = 10.0;
    const double        CONFIG_FEATURES_RATIO_BIN_SIZE  = 10;
    const EXPORT_MODE   CONFIG_EXPORT_MODE              = EXPORT_ALL;
    string              DATASET_NAME                    = "";
    const int           CONFIG_CONTRAST_KERNEL_SIZE     = 5;
    const double        CONFIG_BLUR_BIN_SIZE            = 50;
    const double        CONFIG_BLUR_THRESH              = 50;
    const double        CONFIG_GRAVITY_VAL              = 9.81;
    const double        CONFIG_GRAVITY_ERR_PERCENT      = 10;
    const bool          CONFIG_DISPARITY_RECTIFY        = false;
}

namespace FILE_NAMES
{
    const string        FILE_TIKZ_PLOT_TEMPLATE         = "tikz_template_plot.tex";
}
