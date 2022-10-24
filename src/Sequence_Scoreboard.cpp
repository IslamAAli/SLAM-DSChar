#include "common.h"

// ==========================================================
// Constructors and Destructors
// ==========================================================
Sequence_Scoreboard::Sequence_Scoreboard(Sequence* m_seq)
{
    seq = m_seq;

    f_p.ds_name     = m_seq->get_ds_name();
    f_p.seq_name    = m_seq->get_seq_name();
    f_p.extension   = ".txt";
}

Sequence_Scoreboard::~Sequence_Scoreboard()
{
}

// ==========================================================
// Scoreboarding Functions
// ==========================================================
