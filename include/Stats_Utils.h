#ifndef STATS_UTILS
#define STATS_UTILS

#include "common.h"

namespace Stats_Utils
{
    void calculate_stats_on_mat(cv::Mat m_img, double& mean, double& std_dev, double& var, double& skewness);
    void vector_trimming(vector<double> in_vector, int trim_percent, int hist_bins, vector<double>& out_vector);
    void calculate_stats_on_vector(vector<uchar> m_input_vec, double& mean, double& std_dev, double& var, double& skewness);
    void calculate_vector_stats(vector<double> m_input_vec, 
                    double& arithmetic_mean, 
                    double& geometric_mean, 
                    double& std_dev, 
                    double& var, 
                    double& skewness,
                    double& min,
                    double& max,
                    double& count);

    void calculate_vector_stats(vector<double> m_vec, vector_stats& m_vector_stats);
    vector<double> convert_stats_to_vector(vector_stats m_vec_stats);
    vector<double> convert_mat_to_doubleVector_uchar8(cv::Mat& m_mat);
} // namespace Stats_Utils


#endif
