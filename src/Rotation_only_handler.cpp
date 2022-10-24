#include "common.h"

Rotation_only_handler::Rotation_only_handler(/* args */)
{
}

Rotation_only_handler::~Rotation_only_handler()
{
}

vector<double> Rotation_only_handler::calculate_acc_magnitude(const vector<double>& acc_x, const vector<double>& acc_y, const vector<double>& acc_z)
{
    vector<double> acc_mag; 
    for(unsigned int i =0; i<acc_x.size(); i++)
    {
        double f_mag = sqrt(acc_x[i]*acc_x[i] + acc_y[i]*acc_y[i] + acc_z[i]*acc_z[i]);
        acc_mag.push_back(f_mag);
    }
    return acc_mag;
}

int Rotation_only_handler::count_rotation_only_motion(vector<double>& m_acc_mag, double m_g_val, double m_g_error_percent)
{
    int rot_only_count = 0; 
    double g_percent = (m_g_error_percent/100) * m_g_val;
    double upper_bound = m_g_val + g_percent;

    for(unsigned int i=0; i < m_acc_mag.size(); i++)
    {
        if (m_acc_mag[i] <= upper_bound)
            rot_only_count ++ ;
    }
    return rot_only_count;
}