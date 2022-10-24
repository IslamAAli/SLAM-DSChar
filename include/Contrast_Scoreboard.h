#ifndef CONTRAST_SCOREBOARD_H
#define CONTRAST_SCOREBOARD_H

#include "common.h"

class Contrast_Scoreboard: public Sequence_Scoreboard
{
private:
    vector<double> rms_contrast;
    vector<double> weber_contrast;
    vector<double> michelson_contrast;
    vector<double> CR_contrast;
    vector_stats rms_contrast_stats;
    vector_stats weber_contrast_stats;
    vector_stats michelson_contrast_stats;
    vector_stats CR_contrast_stats;

public:
    Contrast_Scoreboard(Sequence* m_seq);
    ~Contrast_Scoreboard();

    void export_results();

    void add_contrast_scores(double rms, double weber, double michelson, double CR);

    vector_stats get_rms_stats();
    vector_stats get_weber_stats();
    vector_stats get_michelson_stats();
    vector_stats get_CR_stats();
};


#endif