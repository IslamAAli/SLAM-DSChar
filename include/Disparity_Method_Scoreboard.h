#ifndef DISPARITY_METHOD_SCOREBOARD_H
#define DISPARITY_METHOD_SCOREBOARD_H

#include "common.h"

class Disparity_Method_Scoreboard : public Sequence_Scoreboard
{
private:
    string method_name;
    vector<double> min_disparity;
    vector<double> max_disparity;
    vector<double> avg_disparity;
    vector<double> std_div_disparity;

    vector_stats min_disp_vec_stats;
    vector_stats max_disp_vec_stats;
    vector_stats avg_disp_vec_stats;
    vector_stats std_div_disp_vec_stats;
    
public:
    Disparity_Method_Scoreboard(Sequence* m_seq, string m_method_name);
    ~Disparity_Method_Scoreboard();

    void add_disparity_scores(double m_min_disp, double m_max_disp, double m_avg_disp, double m_std_div_disp);

    void export_results();

    vector_stats get_min_disp_vec_stats();
    vector_stats get_max_disp_vec_stats();
    vector_stats get_avg_disp_vec_stats();
    vector_stats get_std_div_disp_vec_stats();
};

#endif