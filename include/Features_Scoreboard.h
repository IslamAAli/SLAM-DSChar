#ifndef FEATURES_SCOREBOARD_H
#define FEATURES_SCOREBOARD_H

#include "common.h"

class Features_Scoreboard : public Sequence_Scoreboard
{
private:
    Visual_Feature_Scoreboard* SIFT_features;
    Visual_Feature_Scoreboard* FAST_features;
    Visual_Feature_Scoreboard* ORB_features;

public:
    Features_Scoreboard(Sequence* m_seq);
    ~Features_Scoreboard();

    void export_results();

    void add_features_metric_scrore(int f_count, double f_dist_abs, double f_dist_avg, VISUAL_FEATURES m_type);

    vector_stats get_score_count_stats(VISUAL_FEATURES m_type);
    vector_stats get_Fdist_abs_stats(VISUAL_FEATURES m_type);
    vector_stats get_Fdist_avg_stats(VISUAL_FEATURES m_type);
    
};




#endif