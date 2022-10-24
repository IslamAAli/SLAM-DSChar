#ifndef INERTIAL_AXIS_DR_SCOREBOARD_H
#define INERTIAL_AXIS_DR_SCOREBOARD_H

#include "common.h"

class Inertial_Axis_DR_Scorebaord: public Sequence_Scoreboard
{
private:
    double g_inertial_DR_limit_hit_count;
    double g_inertial_DR_limit_hit_percentage;
    double g_inertial_DR_coverage_percentage;
    
    double a_inertial_DR_limit_hit_count;
    double a_inertial_DR_limit_hit_percentage;
    double a_inertial_DR_coverage_percentage;

    string m_axis_str;
    INERTIAL_MODE in_mode;
public:
    Inertial_Axis_DR_Scorebaord(Sequence* m_seq, string in_axis_str, INERTIAL_MODE m_mode);
    ~Inertial_Axis_DR_Scorebaord();

    void export_results();

    void add_inertial_gyro_DR_results(int m_DR_limit_hit_count,double m_DR_limit_hit_percentage, double m_DR_coverage_percentage);
    void add_inertial_acc_DR_results(int m_DR_limit_hit_count,double m_DR_limit_hit_percentage, double m_DR_coverage_percentage);

    double get_g_inertial_DR_limit_hit_count();
    double get_g_inertial_DR_limit_hit_percentage();
    double get_g_inertial_DR_coverage_percentage();
    
    double get_a_inertial_DR_limit_hit_count();
    double get_a_inertial_DR_limit_hit_percentage();
    double get_a_inertial_DR_coverage_percentage();
};


#endif