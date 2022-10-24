#include "common.h"

Blur_handler::Blur_handler(/* args */)
{
}

Blur_handler::~Blur_handler()
{
}

double Blur_handler::calculate_var_laplacian(cv::Mat& m_img)
{
    // calculate the laplacian operator on the input image using standard configuration
    cv::Mat img_laplacian;
    cv::Laplacian(m_img, img_laplacian, CV_16S);
    
    // calculate the variance of the laplacian image as a measure for the image blur level/blur score
    cv::Mat mean;
    cv::Mat std_dev;
    cv::meanStdDev(img_laplacian, mean, std_dev);

    double sigma = std_dev.at<double>(0,0);

    // return the variance as the measure of the blurring
    return sigma*sigma;
}


void Blur_handler::calculate_segmented_blur_detection(cv::Mat& m_img, int m_bin_size, double m_blur_threshold_score,
                                            double& image_blur_score, double& blur_percentage, bool& blur_result,
                                            bool& local_blur, bool& global_blur,
                                            vector<double>& sub_score, vector<bool>& sub_status)
{
    // initialization
    double total_subscore = 0;
    double sub_images_count = 0;
    double blurred_sub_images_count = 0;

    // loop over rows and columns with increments of bin size 
    for(int r=0; r<m_img.rows; r+= m_bin_size)
    {
        for(int c=0; c<m_img.cols; c+=m_bin_size)
        {
            // adjust rows boundaries
            double rows_start = r; 
            double rows_end = r+m_bin_size;
            if (rows_end >= m_img.rows)
            {
                rows_end = m_img.rows;
            }

            // adjust cols boundaries
            double cols_start = c;
            double cols_end = c+m_bin_size;
            if(cols_end >= m_img.cols)
            {
                cols_end = m_img.cols;
            }

            // extract sub_image from the original image
            cv::Mat sub_img = m_img(cv::Range(rows_start,rows_end), cv::Range(cols_start,cols_end));

            // calculate the sub score of the sub image
            double img_sub_score = calculate_var_laplacian(sub_img);
            sub_score.push_back(img_sub_score);

            // increment counters for statistics calculations
            total_subscore += img_sub_score;
            sub_images_count += 1;

            // detect if the sub_image is blurred 
            if (img_sub_score < m_blur_threshold_score)
            {
                // blurred
                blurred_sub_images_count +=1;
                sub_status.push_back(true);
            }
            else
            {
                // not blurred
                sub_status.push_back(false);
            }
        }
    }

    // calculate the blurring statistics
    image_blur_score = total_subscore / (double)sub_images_count;
    blur_percentage = ((double)blurred_sub_images_count/(double)sub_images_count)*100;
    blur_percentage > 50.0 ? blur_result = true : blur_result = false;

    global_blur = false;
    local_blur = false;

    if (blur_percentage >= 90)
        global_blur = true;

    if (blur_percentage >= 0)
        local_blur = true;
}