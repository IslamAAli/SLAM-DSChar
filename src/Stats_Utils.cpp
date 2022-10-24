#include "common.h"

namespace Stats_Utils
{
    void calculate_stats_on_mat(cv::Mat m_img, double& mean, double& std_dev, double& var, double& skewness)
    {
        // define the scalar values to hold the mean and standard deviation of the grayscale image
        cv::Scalar mu, sigma;

        // calculate the mean and standard deviation 
        cv::meanStdDev(m_img, mu, sigma);

        // record the mean and standard deviation values to the output
        mean    = mu[0];
        std_dev = sigma[0];

        // calculate the variance
        var     = std_dev * std_dev;

        // calculate the skewness
        double skewness_sum = 0 ;
        for (int x = 0; x<m_img.rows; x++) 
        {
            for (int y = 0; y<m_img.cols; y++) 
            {
                int pixel_val = (int)(m_img.at<uchar>(x, y));
                skewness_sum += pow((pixel_val - mean), 3);
            }
        } 
        skewness = skewness_sum / (pow(std_dev, 3) * (m_img.cols * m_img.rows));        
    }

    void vector_trimming(vector<double> in_vector, int trim_percent, int hist_bins, vector<double>& out_vector)
    {
        //calcaulate the range of values to be trimmed
        int trimming_magnitude = round(hist_bins * trim_percent / 100);
        int start_begin = 0 ;
        int stard_stop  = trimming_magnitude-1;
        int end_begin   = hist_bins - trimming_magnitude;
        int end_stop    = hist_bins - 1;

        for(unsigned int i=0; i<in_vector.size(); i++)
        {
            if  (!( (in_vector[i] >= start_begin  && in_vector[i] <= stard_stop) || (in_vector[i] >= end_begin  && in_vector[i] < end_stop)))
            {
                out_vector.push_back(in_vector[i]);
            }
            // else
            // {
            //     cout << "Trimmed " << in_vector[i] << endl;
            // }
        }
    }

    void calculate_stats_on_vector(vector<uchar> m_input_vec, double& mean, double& std_dev, double& var, double& skewness)
    {
        // convert the vector to a double 1 d opencv matrix
        cv::Mat converted_Mat = cv::Mat(1, m_input_vec.size(), CV_8UC1, m_input_vec.data()).clone();
        
        // use the already developed method that can apply on matrices.
        calculate_stats_on_mat(converted_Mat, mean, std_dev, var, skewness);
    }


    void calculate_vector_stats(vector<double> m_input_vec, 
                    double& arithmetic_mean, 
                    double& geometric_mean, 
                    double& std_dev, 
                    double& var, 
                    double& skewness, 
                    double& min,
                    double& max,
                    double& count)
    {
        // calculate the arithmetic mean 
        double sum = std::accumulate(m_input_vec.begin(), m_input_vec.end(), 0.0);
        arithmetic_mean = sum / m_input_vec.size();

        // calcualte the geometric mean
        double geo_mean_product = 1;
        for(unsigned int i=0; i<m_input_vec.size(); i++)
        {
            geo_mean_product *= m_input_vec[i];
        }
        geometric_mean = pow(geo_mean_product, (float) 1/m_input_vec.size());

        // calculate the variance 
        double sq_sum = std::inner_product(m_input_vec.begin(), m_input_vec.end(), m_input_vec.begin(), 0.0);
        std_dev = std::sqrt(sq_sum / m_input_vec.size() - arithmetic_mean * arithmetic_mean);

        // calculate the variance
        var = std_dev * std_dev;

        // calculate skewness
        double skewness_sum = 0 ;
        for(unsigned int i=0; i<m_input_vec.size(); i++)
        {
            skewness_sum += pow(m_input_vec[i]-arithmetic_mean, 3);
        }
        skewness = skewness_sum / (pow(std_dev, 3) * m_input_vec.size());

        // calculate the minimum and maximum values
        if (m_input_vec.size() > 0)
        {
            max = *max_element(m_input_vec.begin(), m_input_vec.end());
            min = *min_element(m_input_vec.begin(), m_input_vec.end());
        }
        else
        {
            max = 0;
            min = 0;
        }
        count = (double)m_input_vec.size();
    }

    void calculate_vector_stats(vector<double> m_vec, vector_stats& m_vector_stats)
    {
        double arith_mean, geo_mean, std_dev, var, skewness, min, max, count;
        calculate_vector_stats(m_vec, arith_mean, geo_mean, std_dev, var, skewness, min, max, count);

        m_vector_stats.arith_mean       = arith_mean;
        m_vector_stats.geo_mean         = geo_mean;
        m_vector_stats.std_dev          = std_dev;
        m_vector_stats.var              = var;
        m_vector_stats.max              = max;
        m_vector_stats.min              = min; 
        m_vector_stats.skewness         = skewness;
        m_vector_stats.count            = count;
    }

    vector<double> convert_stats_to_vector(vector_stats m_vec_stats)
    {
        vector<double> out_vec={m_vec_stats.arith_mean, 
                                m_vec_stats.geo_mean, 
                                m_vec_stats.std_dev,
                                m_vec_stats.var,
                                m_vec_stats.skewness,
                                m_vec_stats.min,
                                m_vec_stats.max,
                                m_vec_stats.count};
        
        return out_vec;
    }

    vector<double> convert_mat_to_doubleVector_uchar8(cv::Mat& m_mat)
    {
        vector<double> result_vec;
        if (m_mat.rows > 0 && m_mat.cols > 0)
        {
            // convert the matrix into a vector
            std::vector<uchar>vec(m_mat.begin<uchar>(), m_mat.end<uchar>());

            // convert the vector of uchar to doubles
            for_each(vec.begin(), vec.end(), [&result_vec](const uchar &in) { result_vec.push_back(static_cast<double>(in)); });
        }
        return result_vec;
    }
}