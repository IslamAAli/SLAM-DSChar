#ifndef ROTATION_ONLY_HANDLER_H
#define ROTATION_ONLY_HANDLER_H

#include "common.h"

class Rotation_only_handler : public Processing_Element
{
private:
    /* data */
public:
    Rotation_only_handler(/* args */);
    ~Rotation_only_handler();

    vector<double> calculate_acc_magnitude(const vector<double>& acc_x, const vector<double>& acc_y, const vector<double>& acc_z);
    int count_rotation_only_motion(vector<double>& m_acc_mag, double m_g_val, double m_g_error_percent);

};

#endif