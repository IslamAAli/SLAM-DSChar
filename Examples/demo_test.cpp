/**
 * @file demo_main.cpp
 * @author Islam Ali (iaali@ualberta.ca)
 * @brief Unit testing sample file
 * @version 1.0
 * @date 2021-09-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common.h"


int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    cv::Mat image = cv::imread("../in_data/sample_images/exposure_imgs/original.png", cv::IMREAD_GRAYSCALE);

    Exposure_handler* exp = new Exposure_handler();

    EXPOSURE_STATUS m_status;
    double m_mean, m_skewness, m_zone;

    exp->calculate_exposure_status(image,m_status, m_mean, m_skewness, m_zone);
    cout << m_status << endl;
    cout << m_mean << endl; 
    cout << m_skewness << endl;
    cout << m_zone << endl;

    // cout << image_blur_score << endl;
    // cout << blur_percentage << endl;
    // cout << blur_result << endl;

    return 0; 
}