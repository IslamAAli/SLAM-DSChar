#include "common.h"


Brightness_handler::Brightness_handler(/* args */)
{
}

Brightness_handler::~Brightness_handler()
{
}

// ===================================================================
// Calculate the average image brightness
// ===================================================================
double Brightness_handler::calc_avg_brightness(cv::Mat& m_img)
{
    // get the mean value as a scalar
    cv::Scalar b_avg =  cv::mean(m_img);
    
    // return the double value deduced from the scalar object
    return  b_avg[0];
}

void Brightness_handler::calc_brightness_changes(vector<double> m_vec, vector<double> timestamps, 
                                                    int& diff_1_sigma, int& diff_2_sigma, int& diff_3_sigma,
                                                    vector<double>& diff_vec, vector_stats& m_diff_stats)
{
    // initialize the output counters
    diff_1_sigma = 0;
    diff_2_sigma = 0;
    diff_3_sigma = 0;

    // calculate the derivative of the signal
    vector<double> diff_out_x;
    vector<double> diff_out_y;
    Calculus_Utils::numerical_diff(timestamps, m_vec,diff_out_x, diff_out_y);

    // calculate mu and sigma for the diff vector
    double arith_mean, geo_mean, std_dev, var, skewness, min, max, count;
    Stats_Utils::calculate_vector_stats(diff_out_y, arith_mean, geo_mean, std_dev, var, skewness, min, max, count);

    // return the time derivative vector
    diff_vec = diff_out_y;

    m_diff_stats.arith_mean = arith_mean;
    m_diff_stats.geo_mean   = geo_mean;
    m_diff_stats.std_dev    = std_dev;
    m_diff_stats.var        = var;
    m_diff_stats.skewness   = skewness;
    m_diff_stats.min        = min;
    m_diff_stats.max        = max;
    m_diff_stats.count      = count; 

    // count the number of occurances of brightness changes of mean+/-sigma, mean+/-2*sigma, mean+/-3*sigma
    for(unsigned int i=0; i <diff_out_y.size(); i++)
    {
        if (diff_out_y[i]<= arith_mean-std_dev || diff_out_y[i] >= arith_mean+std_dev)
        {
            diff_1_sigma ++;
        }
        
        if (diff_out_y[i]<= arith_mean-2*std_dev || diff_out_y[i] >= arith_mean+2*std_dev)
        {
            diff_2_sigma ++;
        }
        
        if (diff_out_y[i]<= arith_mean-3*std_dev || diff_out_y[i] >= arith_mean+3*std_dev)
        {
            diff_3_sigma ++;
        }
    }
}