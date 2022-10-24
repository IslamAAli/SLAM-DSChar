#ifndef DBOW2_SCOREBOARD_H
#define DBOW2_SCOREBOARD_H

#include "common.h"

class DBoW2_Scoreboard: public Sequence_Scoreboard
{
private:
    vector<double> closest_match_distance;
    vector<double> closest_match_score;
    vector_stats closest_match_distance_stats;
    vector_stats closest_match_score_stats;
    int revisit_counter_1p0;
    int revisit_counter_0p9;
    int revisit_counter_0p5;
public:
    DBoW2_Scoreboard(Sequence* m_seq);
    ~DBoW2_Scoreboard();

    // basic scoreboard functions
    void export_results();

    void add_revisit_score(double m_score, int m_distance);

    vector_stats get_score_stats();
    vector_stats get_distance_stats();
    int get_revisit_score_1p0();
    int get_revisit_score_0p9();
    int get_revisit_score_0p5();
};




#endif 