#ifndef VISUALIZATION_UTILS_H
#define VISUALIZATION_UTILS_H

namespace Visualization_Utils
{
    void visualize_matrix(cv::Mat m_mat, double resize_factor);
    void print_vector(vector<string> vec);
    void print_vector(vector<double> vec);
    indicators::ProgressBar* create_progress_bar();
    void close_progress_bar();
}



#endif