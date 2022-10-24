#ifndef BLUR_SCOREBOARD_H
#define BLUR_SCROEBOARD_H

#include "common.h"

class Blur_Scoreboard : public Sequence_Scoreboard
{
private:
    vector<double> blur_score_vec, blur_percentage_vec;
    vector_stats blur_score_vec_stats, blur_percentage_vec_stats;
    int blurred_images_count;
    int global_blurred_images;
    int local_blurred_images;

    double blurred_images_percentage;
    double global_blurred_images_percentage;
    double local_blurred_images_percentage;

public:
    Blur_Scoreboard(Sequence* m_seq);
    ~Blur_Scoreboard();

    void export_results();

    double get_blurred_img_percent();
    double get_global_blur_percent();
    double get_local_blur_percent();
    vector_stats get_blur_score_stats();
    vector_stats get_blur_percent_stats();

    void add_blur_metric_scores(double image_blur_score, double blur_percentage, bool blur_result, bool global_blur, bool local_blur);
    void add_blur_metric_percentage();
};


#endif