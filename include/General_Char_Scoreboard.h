#ifndef GENERAL_CHAR_SCROEBOARD_H
#define GENERAL_CHAR_SCOREBOARD_H

#include "common.h"

class General_Char_Scoreboard : public Sequence_Scoreboard
{
private:
    vector<double> visual_inertial_timestamps_mismatch;
public:
    General_Char_Scoreboard(Sequence* m_seq);
    ~General_Char_Scoreboard();

    void export_results();

    // General Characteristics methods
    void set_timestamp_mismatch_vec(vector<double> m_vec);
    vector<double> get_timestamp_mismatch_vec();
};


#endif