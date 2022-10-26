#include "common.h"

// ===================================================================
// Constructors
// ===================================================================
Features_handler::Features_handler(/* args */)
{
}

// ===================================================================
// Destructors
// ===================================================================
Features_handler::~Features_handler()
{
}

// ===================================================================
// Calculate the features metrics
// ===================================================================
void Features_handler::calc_features_metrics(cv::Mat& m_img, VISUAL_FEATURES m_features_type, 
                                            int& f_count, double& f_dist_ratio_abs, double& f_dist_ratio_avg)
{
    vector<cv::KeyPoint> keypoints;

    switch (m_features_type)
    {
        // detect SIFT features
        case VF_SIFT:
        {
            cv::Ptr<cv::xfeatures2d::SIFT> sift_detector = cv::xfeatures2d::SIFT::create();
            sift_detector->detect(m_img, keypoints);
            break;
        }

        // detect FAST features
        case VF_FAST:
        {
            cv::Ptr<cv::FastFeatureDetector> fast_detector = cv::FastFeatureDetector::create();
            fast_detector->detect(m_img, keypoints);
            break;
        }

        // detect ORB features
        case VF_ORB:
        default:
        {
            cv::Ptr<cv::FeatureDetector> orb_detector = cv::ORB::create(15000);
            orb_detector->detect(m_img, keypoints);
            break;
        }
    }

    // report the number of detect features in the image
    f_count = keypoints.size();

    // calculate the spatial distribution of the features in the image
    cv::Mat img_f_histogram = features_histogram(keypoints, m_img.size());
    
    // calculate spatial feature distribution ratios
    double image_bins               = img_f_histogram.cols * img_f_histogram.rows;
    double uniform_features_dist    = f_count/image_bins;
    double f_dist_avg_count         = 0 ;
    double f_dist_abs_count         = 0 ;

    

    for(int i=0; i<img_f_histogram.cols ;i++)
    {
        for(int j=0; j<img_f_histogram.rows; j++)
        {
            if (img_f_histogram.at<float>(i, j) >0)
            {   
                f_dist_abs_count ++ ;
                if (img_f_histogram.at<float>(i, j)>= uniform_features_dist)
                {
                    f_dist_avg_count++;
                }
            }
        }
    }

    f_dist_ratio_abs = (f_dist_abs_count/image_bins)*100.0;
    f_dist_ratio_avg = (f_dist_avg_count/image_bins)*100.0;
}

// ===================================================================
// Create the 2d histogram of the image bins
// ===================================================================
cv::Mat Features_handler::features_histogram(vector<cv::KeyPoint> m_kp, cv::Size m_img_size)
{
    // calculate the results 2D histogram size
    int rows = (int)(ceil(m_img_size.height / CONFIG::CONFIG_FEATURES_RATIO_BIN_SIZE));
    int cols = (int)(ceil(m_img_size.width  / CONFIG::CONFIG_FEATURES_RATIO_BIN_SIZE));
    
    // create a 2D matrix with zeros as initial values
    cv::Mat bin_f_count = cv::Mat::zeros(rows, cols, CV_32FC1);
    // loop over points and assign increment the bin count in the matrix accordingly
    for(unsigned int i=0; i<m_kp.size(); i++)
    {
        int loc_x = (int)(ceil(m_kp[i].pt.x / CONFIG::CONFIG_FEATURES_RATIO_BIN_SIZE)-1);
        int loc_y = (int)(ceil(m_kp[i].pt.y / CONFIG::CONFIG_FEATURES_RATIO_BIN_SIZE)-1);
        bin_f_count.at<float>(loc_y, loc_x) = bin_f_count.at<float>(loc_y, loc_x) + 1;
    }

    // return the histogram to the calling function
    return bin_f_count;
}