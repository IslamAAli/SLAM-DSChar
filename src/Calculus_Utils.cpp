#include "common.h"

namespace Calculus_Utils
{
    // central method for differentiation
    void numerical_diff(vector<double> m_x_vector, vector<double> m_y_vector, vector<double>& out_x_vector, vector<double>& out_y_vector)
    {
        for(unsigned int i=0; i<m_x_vector.size()-1; i++)
        {
            double dx = m_x_vector[i+1] - m_x_vector[i];
            double dy = m_y_vector[i+1] - m_y_vector[i];
            out_y_vector.push_back(dy/dx); 
            out_x_vector.push_back(m_x_vector[i]+(dx/2));       //[TODO] validation
        }
    }

    // Tapzodial Method for numerical integration
    void numerical_intg(vector<double> m_x_vector, vector<double> m_y_vector, vector<double>& out_vector)
    {
        double dx_node = m_x_vector[1] - m_x_vector[0];
        double integral_accum = 0.5*dx_node*m_y_vector[0];
        out_vector.push_back(integral_accum);

        for(unsigned int i=1; i<m_x_vector.size()-1; i++)
        {
            double dx = m_x_vector[i+1] - m_x_vector[i];
            integral_accum += dx * m_y_vector[i];
            out_vector.push_back(integral_accum);
        }
    }

} // namespace Calculus_Utils
