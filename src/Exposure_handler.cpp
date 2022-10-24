#include "common.h"


Exposure_handler::Exposure_handler(/* args */)
{
}

Exposure_handler::~Exposure_handler()
{
}

void Exposure_handler::calculate_exposure_status(cv::Mat& m_img, EXPOSURE_STATUS& m_status, double& m_mean, double& m_skewness, double& m_zone)
{
    // trim the input matrix histogram
    vector<double> img_vec = Stats_Utils::convert_mat_to_doubleVector_uchar8(m_img);
    vector<double> trimmed_img_vec;
    Stats_Utils::vector_trimming(img_vec, 5, 256, trimmed_img_vec);

    // get the mean and skewness of the input image
    vector_stats trimmed_vec_stats;
    Stats_Utils::calculate_vector_stats(trimmed_img_vec, trimmed_vec_stats);
    m_mean = trimmed_vec_stats.arith_mean;
    m_skewness = trimmed_vec_stats.skewness;

    // detect the zone of the mean value
    m_zone = zone_detector(m_mean);

    // detect the status of the image
    m_status = exposure_status_detector(m_zone, m_skewness);
}

EXPOSURE_STATUS Exposure_handler::exposure_status_detector(double m_zone, double m_skewness)
{
    EXPOSURE_STATUS img_status = PROPER_EXPOSURE;
    if(m_zone == 0)
    {
        img_status =  BLACK_EXPOSURE;
    }
    else if (m_zone == 6)
    {
        img_status =  WHITE_EXPOSURE;
    }
    else
    {
        if (m_zone == 1 && m_skewness > 0)
        {
            img_status = UNDER_EXPOSURE;
        }
        else if (m_zone == 5 && m_skewness < 0)
        {
            img_status = OVER_EXPOSURE;
        }
        else
        {
            img_status = PROPER_EXPOSURE; 
        }
    }

    return img_status;
}

double Exposure_handler::zone_detector(double m_mean)
{
    double zone_val = 0 ;

    if (m_mean <= 12)
    {
        zone_val = 0;
    }
    else if (m_mean <= 58)
    {
        zone_val = 1;
    }
    else if (m_mean <= 104)
    {
        zone_val = 2;
    }
    else if (m_mean <= 150)
    {
        zone_val = 3;
    }
    else if (m_mean <= 196)
    {
        zone_val = 4;
    }
    else if (m_mean <= 242)
    {
        zone_val = 5;
    }
    else
    {
        zone_val = 6;
    }

    return zone_val;
}