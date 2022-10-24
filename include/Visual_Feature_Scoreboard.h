#ifndef VISUAL_FEATURE_SCOREBOARD_H
#define VISUAL_FEATURE_SCOREBOARD_H

#include "common.h"

class Visual_Feature_Scoreboard : public Sequence_Scoreboard
{

friend class Features_Scoreboard;
private:
    string feature_name;
    vector<double> score_count;
    vector<double> score_Fdist_abs;
    vector<double> score_Fdist_avg;
    vector_stats score_count_stats;
    vector_stats score_Fdist_abs_stats;
    vector_stats score_Fdist_avg_stats;
public:
    Visual_Feature_Scoreboard(Sequence* m_seq, string f_name);
    ~Visual_Feature_Scoreboard();

    void export_results();

    void add_features_metric_scrore(int f_count, double f_dist_abs, double f_dist_avg);

    vector_stats get_score_count_stats();
    vector_stats get_Fdist_abs_stats();
    vector_stats get_Fdist_avg_stats();

};



#endif