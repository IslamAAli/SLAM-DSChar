#ifndef BRIGHTNESS_HANDLER_H
#define BRIGHTNESS_HANDLER_H

#include "common.h"

class Brightness_handler : public Processing_Element
{
private:
    /* data */
public:
    Brightness_handler(/* args */);
    ~Brightness_handler();

    double calc_avg_brightness(cv::Mat& m_img);
    void calc_brightness_changes(vector<double> m_vec, vector<double> timestamps, 
                                int& diff_1_sigma, int& diff_2_sigma, int& diff_3_sigma,
                                vector<double>& diff_vec, vector_stats& m_diff_stats);
};




#endif