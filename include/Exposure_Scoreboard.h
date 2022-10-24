#ifndef EXPOSURE_SCOREBOARD_H
#define EXPOSURE_SCOREBOARD_H

#include "common.h"

class Exposure_Scoreboard : public Sequence_Scoreboard
{
private:
    int proper_exposure_count;
    int under_exposure_count;
    int over_exposure_count;
    int black_exposure_count;
    int white_exposure_count;

    double proper_exposure_percent;
    double under_exposure_percent;
    double over_exposure_percent;
    double black_exposure_percent;
    double white_exposure_percent;

    vector<double> mean_vals;
    vector<double> skewness_vals;
    vector<double> img_zone;
    vector_stats mean_vec_stats;
    vector_stats skewness_vec_stats;
    vector_stats img_zone_vec_stats;

public:
    Exposure_Scoreboard(Sequence* m_seq);
    ~Exposure_Scoreboard();

    void export_results();

    void calculate_metrics_percentages();

    void add_exposure_results_entry(EXPOSURE_STATUS m_status, double m_mean, double m_skewness, double m_zone);

    // setter functions
    void set_proper_exposure_count(int m_count);
    void set_under_exposure_count(int m_count);
    void set_over_exposure_count(int m_count);
    void set_black_exposure_count(int m_count);
    void set_white_exposure_count(int m_count);

    void set_proper_exposure_percent(double m_percent);
    void set_under_exposure_percent(double m_percent);
    void set_over_exposure_percent(double m_percent);
    void set_black_exposure_percent(double m_percent);
    void set_white_exposure_percent(double m_percent);

    // getter functions
    int get_proper_exposure_count();
    int get_under_exposure_count();
    int get_over_exposure_count();
    int get_black_exposure_count();
    int get_white_exposure_count();

    int get_proper_exposure_percent();
    int get_under_exposure_percent();
    int get_over_exposure_percent();
    int get_black_exposure_percent();
    int get_white_exposure_percent();

    vector_stats get_mean_vec_stats();
    vector_stats get_skewness_vec_stats();
    vector_stats get_zone_vec_stats();

};

#endif
