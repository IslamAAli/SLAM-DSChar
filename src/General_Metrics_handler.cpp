#include "common.h"
// ============================================================================================
General_Metrics_handler::General_Metrics_handler(/* args */)
{
}
// ============================================================================================
General_Metrics_handler::~General_Metrics_handler()
{
}
// ============================================================================================
void General_Metrics_handler::add_seq_data_size(int size, vector<int>& m_out_vec)
{
    m_out_vec.push_back(size);
}
// ============================================================================================
vector<double> General_Metrics_handler::calculate_sampling_rate(vector<double> m_input_vec)
{
    vector<double> m_output_vec;
    for(unsigned int i=1; i<m_input_vec.size(); i++)
    {
        m_output_vec.push_back(m_input_vec[i]-m_input_vec[i-1]);
    }
    return m_output_vec;
}
// ============================================================================================
void General_Metrics_handler::calculate_timestamp_mismatch(vector<double> m_in_vec_1, vector<double> m_in_vec_2, vector<double>& m_out_vec)
{
    // initialize local vectors
    vector<double> short_vec = m_in_vec_2;
    vector<double> long_vec  = m_in_vec_1;

    // select the smaller vector to use as iterator
    if (m_in_vec_1.size() < m_in_vec_2.size())
    {
        short_vec = m_in_vec_1;
        long_vec = m_in_vec_2;
    }

    // loop over the short vector and find it closest match in the longer vector
    for(unsigned int i=0; i< short_vec.size(); i++)
    {
        // get the closest value 
        double closest_match_index = Utils::search_closest(long_vec, short_vec[i]);
        double closest_match_val = long_vec[closest_match_index];

        // calculate the difference and push it to the output array 
        m_out_vec.push_back((short_vec[i] - closest_match_val));
    }
}
// ============================================================================================
double General_Metrics_handler::calculate_seq_total_duration(vector<double> m_in_vec)
{
    // total duration = last timestamp - first timestamp // represented in seconds 
    return (m_in_vec[m_in_vec.size()-1] - m_in_vec[0]);
}
