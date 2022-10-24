#ifndef FEATURES_HANDLER_H
#define FEATURES_HANDLER_H

#include "common.h"

class Features_handler : public Processing_Element
{
private:
    /* data */
public:
    Features_handler(/* args */);
    ~Features_handler();


    void calc_features_metrics(cv::Mat& m_img, VISUAL_FEATURES m_features_type, int& f_count, double& f_dist_ratio_abs, double& f_dist_ratio_avg);
    cv::Mat features_histogram(vector<cv::KeyPoint> m_kp, cv::Size m_img_size);
};


#endif