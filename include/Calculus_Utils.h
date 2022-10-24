#ifndef CALCULUS_UTILS
#define CALCULUS_UTILS

#include "common.h"

namespace Calculus_Utils
{
    void numerical_diff(vector<double> m_x_vector, vector<double> m_y_vector, vector<double>& out_x_vector, vector<double>& out_y_vector);
    void numerical_intg(vector<double> m_x_vector, vector<double> m_y_vector, vector<double>& out_vector);
} // namespace Calculus_Utils


#endif