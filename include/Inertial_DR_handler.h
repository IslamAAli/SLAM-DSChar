#ifndef INERTIAL_DR_HANDLER_H
#define INERTIAL_DR_HANDLER_H


#include "common.h"


class Inertial_DR_handler : public Processing_Element
{
private:
    // internal scoreboarding
    int DR_limit_hit_count; 
public:
    Inertial_DR_handler();
    ~Inertial_DR_handler();

    // check for dynamic range limits
    int dynamic_range_limits_checker(vector<double>& m_in_data, double m_lower_limit, double m_upper_limit);
    double dynamic_range_coverage_percentage(vector<double> & m_in_data, double m_lower_limit, double m_upper_limit);
    double dynamic_range_limits_hitting_percentage(int m_inertial_data_size);
    };


#endif