#ifndef CONTRAST_HANDLER
#define CONTRAST_HANDLER

#include "common.h"

class Contrast_handler : public Processing_Element
{
    private:
        /* data */
    public:
        Contrast_handler(/* args */);
        ~Contrast_handler();

        // Contrast calculation methods
        double contrast_rms(cv::Mat& m_img);
        double contrast_weber(cv::Mat& m_img);
        double contrast_michelson(cv::Mat& m_img);
        double contrast_ratio(cv::Mat& m_img);
        void get_max_min_lightness(cv::Mat& m_img, cv::Mat& min, cv::Mat& max);
        void get_mu_sigma_from_mat(cv::Mat& m_in_mat, double& mu, double& sigma);
        void get_luminance_channel(cv::Mat& m_in_mat, cv::Mat& L_channel);

};




#endif