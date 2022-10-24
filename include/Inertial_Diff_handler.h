#ifndef INERTIAL_DIFF_HANDLER_H
#define INERTIAL_DIFF_HANDLER_H


#include "common.h"


class Inertial_Diff_handler : public Processing_Element
{
private:
    
public:
    Inertial_Diff_handler();
    ~Inertial_Diff_handler();

    void calculate_higher_order_derivatives(vector<double>& m_in_data, 
                                            vector<double>& m_in_timestamps, 
                                            vector<double>& out_1st_diff, 
                                            vector<double>& out_1st_timestamps,
                                            vector<double>& out_2nd_diff,
                                            vector<double>& out_2nd_timestamps);
    };


#endif