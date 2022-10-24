#ifndef DISPARITY_SCOREBOARD_H
#define DISPARITY_SCOREBOARD_H

#include "common.h"

class Disparity_Scoreboard: public Sequence_Scoreboard
{
private:
    Disparity_Method_Scoreboard* DM_StereoBM;
    Disparity_Method_Scoreboard* DM_stereoSGBM;

public:
    Disparity_Scoreboard(Sequence* m_seq);
    ~Disparity_Scoreboard();

    void export_results();

    void add_results(double min_val, double max_val, double avg_val, double std_div_val, DISPARITY_ALGO m_mode);

    vector_stats get_min_disp_vec_stats(DISPARITY_ALGO m_mode);
    vector_stats get_max_disp_vec_stats(DISPARITY_ALGO m_mode);
    vector_stats get_avg_disp_vec_stats(DISPARITY_ALGO m_mode);
    vector_stats get_std_div_disp_vec_stats(DISPARITY_ALGO m_mode);
};


#endif