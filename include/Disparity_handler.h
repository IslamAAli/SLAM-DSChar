#ifndef DISPARITY_HANDLER_H
#define DISPARITY_HANDLER_H

#include "common.h"

class Disparity_handler
{
private:
    /* data */
public:
    Disparity_handler(/* args */);
    ~Disparity_handler();

    void rectify_input_unCalib(cv::Mat& m_r_img, cv::Mat& m_l_img, cv::Mat& out_r_img, cv::Mat& out_l_img);

    void calculate_disparity(cv::Mat& m_r_img, cv::Mat& m_l_img, 
                            double& min_disparity, double& max_disparity, double& avg_disparity, double& std_div, 
                            DISPARITY_ALGO m_mode);
    void calculate_disparity_StereoBM(cv::Mat& m_r_img, cv::Mat& m_l_img, cv::Mat& disp_img);
    void calculate_disparity_StereoSGBM(cv::Mat& m_r_img, cv::Mat& m_l_img, cv::Mat& disp_img);

    vector<double> filter_disparity_map(cv::Mat& m_img);
};

#endif