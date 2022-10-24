#ifndef EXPOSURE_HANDLER_H
#define EXPOSURE_HANDLER_H

#include "common.h"

class Exposure_handler
{
private:
    /* data */
public:
    Exposure_handler(/* args */);
    ~Exposure_handler();

    void calculate_exposure_status(cv::Mat& m_img, EXPOSURE_STATUS& m_status, double& m_mean, double& m_skewness, double& m_zone);
    double zone_detector(double m_mean);
    EXPOSURE_STATUS exposure_status_detector(double m_zone, double m_skewness);
};


#endif