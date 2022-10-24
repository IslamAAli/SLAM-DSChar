#ifndef INERTIAL_DR_SCOREBOARD_H
#define INERTIAL_DR_SCOREBOARD_H

#include "common.h"

class Inertial_DR_Scoreboard : public Sequence_Scoreboard
{
private:
    Inertial_Axis_DR_Scorebaord* axis_x;
    Inertial_Axis_DR_Scorebaord* axis_y;
    Inertial_Axis_DR_Scorebaord* axis_z;
public:
    Inertial_DR_Scoreboard(Sequence* m_seq);
    ~Inertial_DR_Scoreboard();

    void export_results();

    void add_inertial_DR_results(INERTIAL_MODE m_mode, int m_DR_limit_hit_count, double m_DR_limit_hit_percentage, double m_DR_coverage_percentage);

    Inertial_Axis_DR_Scorebaord* get_x_axis();
    Inertial_Axis_DR_Scorebaord* get_y_axis();
    Inertial_Axis_DR_Scorebaord* get_z_axis();
};

#endif