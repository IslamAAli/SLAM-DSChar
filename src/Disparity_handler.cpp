#include "common.h"

Disparity_handler::Disparity_handler(/* args */)
{
}

Disparity_handler::~Disparity_handler()
{
}

void Disparity_handler::rectify_input_unCalib(cv::Mat& m_r_img, cv::Mat& m_l_img, cv::Mat& out_r_img, cv::Mat& out_l_img)
{
    out_r_img = m_r_img;
    out_l_img = m_l_img;
}

void Disparity_handler::calculate_disparity(cv::Mat& m_r_img, cv::Mat& m_l_img, 
                                            double& min_disparity, double& max_disparity, double& avg_disparity, double& std_div_disparity,
                                            DISPARITY_ALGO m_mode)
{
    // rectify images if rectification flag is on
    cv::Mat rec_img_r, rec_img_l, disp_img;

    if (CONFIG::CONFIG_DISPARITY_RECTIFY)
    {
        rectify_input_unCalib(m_r_img, m_l_img, rec_img_r, rec_img_l);
    }
    else
    {
        rec_img_r = m_r_img;
        rec_img_l = m_l_img;
    }


    // run the selected algorithm
    switch (m_mode)
    {
        case STEREO_BM:
            calculate_disparity_StereoBM(m_r_img, m_l_img, disp_img);
            break;
        
        case STEREO_SGBM:
            calculate_disparity_StereoSGBM(m_r_img, m_l_img, disp_img);
            break;
            
        default:
            break;
    }
    
    // filter the disparity image and convert it into a vector
    vector<double> disp_vals = filter_disparity_map(disp_img);

    // calculate stats on the filtered vectors
    vector_stats disp_img_stats;
    Stats_Utils::calculate_vector_stats(disp_vals, disp_img_stats);

    min_disparity = disp_img_stats.min;
    max_disparity = disp_img_stats.max;
    avg_disparity = disp_img_stats.arith_mean;
    std_div_disparity = disp_img_stats.std_dev;

    // cout << min_disparity << " " << max_disparity << " " << avg_disparity << " " << std_div_disparity << endl;

}

void Disparity_handler::calculate_disparity_StereoBM(cv::Mat& m_r_img, cv::Mat& m_l_img, cv::Mat& disp_img)
{
    // create the object
    cv::Ptr<cv::StereoBM> stereo_BM_obj = cv::StereoBM::create(144,9);

    // set the disparity parameters
    // stereo_BM_obj->setPreFilterSize(5);
    stereo_BM_obj->setPreFilterCap(16);
    stereo_BM_obj->setMinDisparity(-32);
    stereo_BM_obj->setUniquenessRatio(1);
    stereo_BM_obj->setDisp12MaxDiff(90);
    stereo_BM_obj->setSpeckleRange(20);
    stereo_BM_obj->setSpeckleWindowSize(60);

    // compute the stereo disparity image
    stereo_BM_obj->compute(m_l_img, m_r_img, disp_img);

    normalize(disp_img, disp_img, 0, 255, cv::NORM_MINMAX, CV_8U);
}

void Disparity_handler::calculate_disparity_StereoSGBM(cv::Mat& m_r_img, cv::Mat& m_l_img, cv::Mat& disp_img)
{
    // create the object
    cv::Ptr<cv::StereoSGBM> stereo_SBGM_obj = cv::StereoSGBM::create(
            -32,    // MinDisparity
        	144,    // NumDisparities
            9,      // block size
            60,     // P1
            2400,   // P2
            90,     // Disp12MaxDiff
            16,     // PreFilterCap
            1,      // UniquenessRatio
            60,     // SpeckleWindowSize
            20,     // SpeckleRange
            true    // SGBM mode
    );

    stereo_SBGM_obj->setMode(cv::StereoSGBM::MODE_SGBM);

    // compute the stereo disparity image
    stereo_SBGM_obj->compute(m_l_img, m_r_img, disp_img);

    normalize(disp_img, disp_img, 0, 255, cv::NORM_MINMAX, CV_8U);
}

vector<double> Disparity_handler::filter_disparity_map(cv::Mat& m_img)
{
    // convert the disparity map into a vector
    vector<double> disp_vec = Stats_Utils::convert_mat_to_doubleVector_uchar8(m_img);
    // cout << m_img.cols << " " << m_img.rows << " " << disp_vec.size() << endl;

    // removing all occuracnces of zeros 
    disp_vec.erase(std::remove(disp_vec.begin(), disp_vec.end(), 0.0), disp_vec.end());
    // cout << disp_vec.size() << endl;

    // return the filtered vector
    return disp_vec;
}