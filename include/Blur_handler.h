#ifndef BLUR_HANDLER_H
#define BLUR_HANDLER_H

#include "common.h"

class Blur_handler
{
private:
    /* data */
public:
    Blur_handler(/* args */);
    ~Blur_handler();

    double calculate_var_laplacian(cv::Mat& m_img);
    void calculate_segmented_blur_detection(cv::Mat& m_img, int m_bin_size, double m_blur_threshold_score,
                                              double& image_blur_score, double& blur_percentage, bool& blur_result,
                                              bool& local_blur, bool& global_blur,
                                              vector<double>& sub_score, vector<bool>& sub_status);
};

#endif