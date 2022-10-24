#include "common.h"

// ===================================================================
// Constructors
// ===================================================================
Inertial_Diff_handler::Inertial_Diff_handler(/* args */)
{    
}

// ===================================================================
// Destructors
// ===================================================================
Inertial_Diff_handler::~Inertial_Diff_handler()
{
}
// ===================================================================
// Calculate higher order derivatives of the inertial data
// ===================================================================
void Inertial_Diff_handler::calculate_higher_order_derivatives(  vector<double>& m_in_data, 
                                                            vector<double>& m_in_timestamps, 
                                                            vector<double>& out_1st_diff, 
                                                            vector<double>& out_1st_timestamps,
                                                            vector<double>& out_2nd_diff,
                                                            vector<double>& out_2nd_timestamps)
{
    // Calculate the first derivative of the input signal
    Calculus_Utils::numerical_diff(m_in_timestamps, m_in_data, out_1st_timestamps, out_1st_diff);

    // calculate the 2nd derivative of the 1st derivative signal
    Calculus_Utils::numerical_diff(out_1st_timestamps, out_1st_diff, out_2nd_timestamps, out_2nd_diff);
}