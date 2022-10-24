#ifndef INERTIAL_AXIS_DIFF_SCOREBOARD_H
#define INERTIAL_AXIS_DIFF_SCOREBOARD_H

#include "common.h"

class Inertial_Axis_Diff_Scorebaord: public Sequence_Scoreboard
{
private:

    string m_axis_str;
    INERTIAL_MODE in_mode;

    // gyroscope scorboarding attributes
    vector<double> g_1st_diff;
    vector<double> g_2nd_diff;
    vector_stats g_1st_diff_stats;
    vector_stats g_2nd_diff_stats;
    vector_stats g_stats;

    // acceleromter scoreboarding attributes
    vector<double> a_1st_diff;
    vector<double> a_2nd_diff;
    vector_stats a_1st_diff_stats;
    vector_stats a_2nd_diff_stats;
    vector_stats a_stats;

public:
    Inertial_Axis_Diff_Scorebaord(Sequence* m_seq, string in_axis_str, INERTIAL_MODE m_mode);
    ~Inertial_Axis_Diff_Scorebaord();

    void export_results();

    void add_gyro_inertial_results(vector<double> m_1st_diff, vector<double> m_2nd_diff);
    void add_acc_inertial_results(vector<double> m_1st_diff, vector<double> m_2nd_diff);

    vector_stats get_g_stats();
    vector_stats get_a_stats();
    vector_stats get_g_1st_diff_stats();
    vector_stats get_a_1st_diff_stats();
    vector_stats get_g_2nd_diff_stats();
    vector_stats get_a_2nd_diff_stats();
};

#endif