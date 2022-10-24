#include "common.h"

Contrast_handler::Contrast_handler(/* args */)
{
}

Contrast_handler::~Contrast_handler()
{
}


// ===================================================================
// Calculate contrast using different methods
// ===================================================================
double Contrast_handler::contrast_rms(cv::Mat& m_img)
{
    // calculate the standard deviation
    cv::Mat mean;
    cv::Mat std_dev;
    cv::meanStdDev(m_img, mean, std_dev);

    return std_dev.at<double>(0,0);
}

double Contrast_handler::contrast_weber(cv::Mat& m_img)
{
    // variables definition
    cv::Mat L, L_b;
    cv::Mat newL, newL_b;

    // get luminance channel
    get_luminance_channel(m_img, L);
    L.convertTo(newL, CV_64FC1);

    // get the background channel
    GaussianBlur(newL, L_b, cv::Size(9,9), 0);
    L_b.convertTo(newL_b, CV_64FC1);

    // weber contrast 
    cv::Mat weber_contrast = (newL-newL_b)/newL_b;

    // get the mean of the resulting matrix
    double mu, sigma;
    get_mu_sigma_from_mat(weber_contrast,mu, sigma);

    return mu*100;
}

double Contrast_handler::contrast_michelson(cv::Mat& m_img)
{   
    // get luminance channel
    cv::Mat L;
    get_luminance_channel(m_img, L);

    // get max and minium values
    double min, max;
    cv::minMaxLoc(L, &min, &max);

    double michelson_contrast = (max-min)/(max+min);

    return michelson_contrast*100;
}


double Contrast_handler::contrast_ratio(cv::Mat& m_img)
{
    // variables definition
    cv::Mat L, L_b;
    cv::Mat newL, newL_b;

    // get luminance channel
    get_luminance_channel(m_img, L);
    L.convertTo(newL, CV_64FC1);

    // get the background channel
    GaussianBlur(newL, L_b, cv::Size(9,9), 0);
    L_b.convertTo(newL_b, CV_64FC1);

    // weber contrast 
    cv::Mat CR = newL/newL_b;

    // get the mean of the resulting matrix
    double mu, sigma;
    get_mu_sigma_from_mat(CR,mu, sigma);

    return mu*100;
}

void Contrast_handler::get_max_min_lightness(cv::Mat& m_img, cv::Mat& min, cv::Mat& max)
{
    // convert the image to RGB
    cv::Mat rgb_img, lab_img;
    cv::Mat lab_img_arr[3];
    cv::cvtColor(m_img, rgb_img, cv::COLOR_GRAY2RGB);

    // convert the image to the lab color space
    cv::cvtColor(rgb_img, lab_img, cv::COLOR_RGB2Lab);

    // extract the lab channel from the resulting matrix
    cv::split(lab_img, lab_img_arr);

    // calculate the max and minium matrices in kernela of size 
    cv::Mat element;
    
    cv::Mat minMat, maxMat;
    cv::erode(lab_img_arr[0], minMat, element);
    cv::dilate(lab_img_arr[0], maxMat, element);

    // convert the matrices into floats
    maxMat.convertTo(max, CV_64FC1);
    minMat.convertTo(min, CV_64FC1);
}

void Contrast_handler::get_mu_sigma_from_mat(cv::Mat& m_in_mat, double& mu, double& sigma)
{
    // calculate the mean and the standard deviation
    cv::Mat mean;
    cv::Mat std_dev;
    cv::meanStdDev(m_in_mat, mean, std_dev);

    sigma = std_dev.at<double>(0,0);
    mu = mean.at<double>(0,0);
}

void Contrast_handler::get_luminance_channel(cv::Mat& m_in_mat, cv::Mat& L_channel)
{
    // convert the image to RGB
    cv::Mat rgb_img, lab_img;
    cv::Mat lab_img_arr[3];
    cv::cvtColor(m_in_mat, rgb_img, cv::COLOR_GRAY2RGB);

    // convert the image to the lab color space
    cv::cvtColor(rgb_img, lab_img, cv::COLOR_RGB2Lab);

    // extract the lab channel from the resulting matrix
    cv::split(lab_img, lab_img_arr);

    L_channel =  lab_img_arr[0];
}