#ifndef BRIGHTNESS_SCOREBOARD_H
#define BRIGHTNESS_SCOREBOARD_H

#include "common.h"

class Brightness_Scoreboard: public Sequence_Scoreboard
{
private:
    vector<double> brightness_scores;
    vector<double> brightness_scores_diff;
    double brightness_change_1sigma;
    double brightness_change_2sigma;
    double brightness_change_3sigma;
    double brightness_change_1sigma_percentage;
    double brightness_change_2sigma_percentage;
    double brightness_change_3sigma_percentage;
    vector_stats brightness_stats;
    vector_stats brightness_diff_stats;

public:
    Brightness_Scoreboard(Sequence* m_seq);
    ~Brightness_Scoreboard();

    void export_results();

    void add_brightness_score(double m_b_val);
    void add_brightness_change_score(double diff_1sigma, double diff_2sigma, double diff_3sigma);
    void set_brightness_stats(vector_stats& m_vector_stats);
    void set_brightness_scores_diff(vector<double>& m_vec);
    void set_brightness_diff_stats(vector_stats& m_vector_stats);
    vector<double> get_brightness_scores();
    vector<double> get_brighness_sigma_scores();
    vector_stats get_brightness_stats();
};


#endif