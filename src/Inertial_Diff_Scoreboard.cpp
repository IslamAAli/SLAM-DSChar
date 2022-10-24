#include "common.h"

Inertial_Diff_Scoreboard::Inertial_Diff_Scoreboard(Sequence* m_seq): Sequence_Scoreboard(m_seq)
{
    axis_x = new Inertial_Axis_Diff_Scorebaord(m_seq, "X", GYRO_X);
    axis_y = new Inertial_Axis_Diff_Scorebaord(m_seq, "Y", GYRO_Y);
    axis_z = new Inertial_Axis_Diff_Scorebaord(m_seq, "Z", GYRO_Z);
}

Inertial_Diff_Scoreboard::~Inertial_Diff_Scoreboard()
{
}

void Inertial_Diff_Scoreboard::export_results()
{
    axis_x->export_results();
    axis_y->export_results();
    axis_z->export_results();
}

void Inertial_Diff_Scoreboard::add_inertial_diff_results(INERTIAL_MODE m_mode, vector<double> m_1st_diff, vector<double> m_2nd_diff, 
                                                vector<double> m_1st_timestamps, vector<double> m_2nd_timestamps)
{
    // set timestamp vectors
    inertial_timestamp_1st_diff = m_1st_timestamps;
    inertial_timestamp_2nd_diff = m_2nd_timestamps;

    switch (m_mode)
    {
        case GYRO_X:
            axis_x->add_gyro_inertial_results(m_1st_diff, m_2nd_diff);
            break;

        case GYRO_Y:
            axis_y->add_gyro_inertial_results(m_1st_diff, m_2nd_diff);
            break;
        
        case GYRO_Z:
            axis_z->add_gyro_inertial_results(m_1st_diff, m_2nd_diff);
            break;

        case ACC_X:
            axis_x->add_acc_inertial_results(m_1st_diff, m_2nd_diff);
            break;

        case ACC_Y:
            axis_y->add_acc_inertial_results(m_1st_diff, m_2nd_diff);
            break;
        
        case ACC_Z:
            axis_z->add_acc_inertial_results(m_1st_diff, m_2nd_diff);
            break;

        default:
            break;
    }
}

Inertial_Axis_Diff_Scorebaord* Inertial_Diff_Scoreboard::get_x_axis()
{
    return axis_x;
}
Inertial_Axis_Diff_Scorebaord* Inertial_Diff_Scoreboard::get_y_axis()
{
    return axis_y;
}
Inertial_Axis_Diff_Scorebaord* Inertial_Diff_Scoreboard::get_z_axis()
{
    return axis_z;
}