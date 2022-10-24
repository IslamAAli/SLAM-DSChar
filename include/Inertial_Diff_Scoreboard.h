#ifndef INERTIAL_DIFF_SCOREBOARD_H
#define INERTIAL_DIFF_SCOREBOARD_H

#include "common.h"

class Inertial_Diff_Scoreboard: public Sequence_Scoreboard
{
private:
    Inertial_Axis_Diff_Scorebaord* axis_x;
    Inertial_Axis_Diff_Scorebaord* axis_y;
    Inertial_Axis_Diff_Scorebaord* axis_z;

    vector<double> inertial_timestamp_1st_diff;
    vector<double> inertial_timestamp_2nd_diff;

public:
    Inertial_Diff_Scoreboard(Sequence* m_seq);
    ~Inertial_Diff_Scoreboard();

    void export_results();

    void add_inertial_diff_results(INERTIAL_MODE m_mode, vector<double> m_1st_diff, vector<double> m_2nd_diff, 
                                                vector<double> m_1st_timestamps, vector<double> m_2nd_timestamps);

    Inertial_Axis_Diff_Scorebaord* get_x_axis();
    Inertial_Axis_Diff_Scorebaord* get_y_axis();
    Inertial_Axis_Diff_Scorebaord* get_z_axis();
};




#endif
