#include "common.h"

// ===================================================================
// Constructors
// ===================================================================
Inertial_DR_handler::Inertial_DR_handler(/* args */)
{    
    DR_limit_hit_count = 0 ;
}

// ===================================================================
// Destructors
// ===================================================================
Inertial_DR_handler::~Inertial_DR_handler()
{
}


// ===================================================================
// Check for dynamic range limits
// ===================================================================
int Inertial_DR_handler::dynamic_range_limits_checker(vector<double>& m_in_data, double m_lower_limit, double m_upper_limit)
{
    double DR_deduction = (m_upper_limit-m_lower_limit)*(CONFIG::CONFIG_INERTIAL_DR_PERCENTAGE/100.0);
    double adjusted_lower_limit = m_lower_limit + DR_deduction/2;
    double adjusted_upper_limit = m_upper_limit - DR_deduction/2;

    int DR_limit_hit_count = 0 ;

    // cout << DR_deduction << " " << adjusted_lower_limit << " " << adjusted_upper_limit << endl;

    for(unsigned int i=0; i<m_in_data.size(); i++)
    {
        // the sample is considered a hit if: greater than the adjusted upper limit or less than the adjusted lower limit 
        if (m_in_data[i]>= adjusted_upper_limit || m_in_data[i] <= adjusted_lower_limit)
        {
            DR_limit_hit_count ++ ;
        }
    }

    return DR_limit_hit_count;
}

double Inertial_DR_handler::dynamic_range_coverage_percentage(vector<double> & m_in_data, double m_lower_limit, double m_upper_limit)
{
    // get the maximum and minimum inertial value
    vector_stats inertial_data_stats;
    Stats_Utils::calculate_vector_stats(m_in_data, inertial_data_stats);

    // calculate the dynamic range of the sensor and the measurements to calculate the percentage
    double sensor_DR_range      = m_upper_limit - m_lower_limit;
    double measurement_DR_range = inertial_data_stats.max - inertial_data_stats.min;
    
    // return the coverage percentage of the measurements compared to the dynamic range of the sensor
    return (measurement_DR_range/sensor_DR_range)*100;
}

double Inertial_DR_handler::dynamic_range_limits_hitting_percentage(int m_inertial_data_size)
{
    // return the ratio of hits compared to the complete data size of the vector of inertial data
    return (DR_limit_hit_count/m_inertial_data_size)*100;
}