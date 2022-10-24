#include "common.h"

Inertial_DR_Scoreboard::Inertial_DR_Scoreboard(Sequence* m_seq): Sequence_Scoreboard(m_seq)
{
    axis_x = new Inertial_Axis_DR_Scorebaord(m_seq, "X", GYRO_X);
    axis_y = new Inertial_Axis_DR_Scorebaord(m_seq, "Y", GYRO_Y);
    axis_z = new Inertial_Axis_DR_Scorebaord(m_seq, "Z", GYRO_Z);
}

Inertial_DR_Scoreboard::~Inertial_DR_Scoreboard()
{
}

void Inertial_DR_Scoreboard::export_results()
{
    axis_x->export_results();
    axis_y->export_results();
    axis_z->export_results();
}

void Inertial_DR_Scoreboard::add_inertial_DR_results(INERTIAL_MODE m_mode, int m_DR_limit_hit_count,double m_DR_limit_hit_percentage,double m_DR_coverage_percentage)
{
    switch (m_mode)
    {
        case GYRO_X:
            axis_x->add_inertial_gyro_DR_results(m_DR_limit_hit_count, m_DR_limit_hit_percentage, m_DR_coverage_percentage);
            break;

        case GYRO_Y:
            axis_y->add_inertial_gyro_DR_results(m_DR_limit_hit_count, m_DR_limit_hit_percentage, m_DR_coverage_percentage);
            break;
        
        case GYRO_Z:
            axis_z->add_inertial_gyro_DR_results(m_DR_limit_hit_count, m_DR_limit_hit_percentage, m_DR_coverage_percentage);
            break;

        case ACC_X:
            axis_x->add_inertial_acc_DR_results(m_DR_limit_hit_count, m_DR_limit_hit_percentage, m_DR_coverage_percentage);
            break;

        case ACC_Y:
            axis_y->add_inertial_acc_DR_results(m_DR_limit_hit_count, m_DR_limit_hit_percentage, m_DR_coverage_percentage);
            break;
        
        case ACC_Z:
            axis_z->add_inertial_acc_DR_results(m_DR_limit_hit_count, m_DR_limit_hit_percentage, m_DR_coverage_percentage);
            break;

        default:
            break;
    }
}

Inertial_Axis_DR_Scorebaord* Inertial_DR_Scoreboard::get_x_axis()
{
    return axis_x;
}
Inertial_Axis_DR_Scorebaord* Inertial_DR_Scoreboard::get_y_axis()
{
    return axis_y;
}
Inertial_Axis_DR_Scorebaord* Inertial_DR_Scoreboard::get_z_axis()
{
    return axis_z;
}