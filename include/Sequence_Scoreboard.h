#ifndef SEQUENCE_SCOREBOARD_H
#define SEQUENCE_SCOREBOARD_H

#include "common.h"

class Sequence_Scoreboard: public Scoreboard
{
friend class Sequence;
friend class Results_Exporter;
friend class Dataset;

protected:
    // [0] General Parameters
    file_name_package f_p;
    Sequence* seq;
private:

public:
    // constructor and destructor functions
    Sequence_Scoreboard(Sequence* m_seq);
    ~Sequence_Scoreboard();

    // basic scoreboard functions
    void export_results();
};

#endif