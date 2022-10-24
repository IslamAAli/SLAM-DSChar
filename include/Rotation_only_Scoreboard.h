#ifndef ROTATION_ONLY_SCOREBOARD_H
#define ROTATION_ONLY_SCOREBOARD_H

#include "common.h"

class Rotation_only_Scoreboard : public Sequence_Scoreboard
{
private:
    int rotation_only_count;
    double rotation_only_percentage;
    vector<double> f_mag;
    vector_stats f_mag_stats;
public:
    Rotation_only_Scoreboard(Sequence* m_seq);
    ~Rotation_only_Scoreboard();

    void export_results();

    void set_rotation_only_count(int m_count);
    int get_rotation_only_count();
    void increment_rotation_only_count();

    double get_rotation_only_percentage();
    void set_rotation_only_percentage(double m_percentage);

    vector<double> get_f_mag();
    void set_f_mag(vector<double> m_vec);

    vector_stats get_f_mag_stats();
    void set_f_mat_stats(vector_stats v_stats);
};


#endif