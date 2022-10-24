#include "common.h"

DBoW2_Scoreboard::DBoW2_Scoreboard(Sequence* m_seq): Sequence_Scoreboard(m_seq)
{
    revisit_counter_1p0         = 0; 
    revisit_counter_0p9         = 0; 
    revisit_counter_0p5         = 0; 
}

DBoW2_Scoreboard::~DBoW2_Scoreboard()
{
}

void DBoW2_Scoreboard::add_revisit_score(double m_score, int m_distance)
{
    closest_match_score.push_back(m_score);
    closest_match_distance.push_back((double)m_distance);

    // cout << "Score:\t" << m_score << "\tDistance:\t" << m_distance << "\t";

    if (m_score >= 1.0)
    {
        revisit_counter_1p0 ++ ;
        // cout << "1.0" << endl;
    }
    else
    {
        if (m_score >= 0.9)
        {
            revisit_counter_0p9 ++ ;
            // cout << "0.9" << endl;
        }
        else
        {
            if (m_score >= 0.5)
            {
                revisit_counter_0p5 ++ ;
                // cout << "0.5" << endl;
            }
            // else
            // {
            //     cout << endl;
            // }
        }
    }
}

void DBoW2_Scoreboard::export_results()
{
    cout << "[REVISIT_FREQ] *** Exporting Results ... " << endl;
    // calculate vector stats
    Stats_Utils::calculate_vector_stats(closest_match_distance, closest_match_distance_stats);
    Stats_Utils::calculate_vector_stats(closest_match_score, closest_match_score_stats);
    
    // Export the per-image results
    f_p.tag = "REVISIT_SCORE";
    Export_Utils::file_export_selector(closest_match_score, f_p);

    f_p.tag = "REVISIT_DIST";
    Export_Utils::file_export_selector(closest_match_distance, f_p);

    
    vector<double> temp_vec;
    f_p.tag = "REVISIT_SCORE_1P0";
    temp_vec.clear();
    temp_vec.push_back((double)revisit_counter_1p0);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "REVISIT_SCORE_0P9";
    temp_vec.clear();
    temp_vec.push_back((double)revisit_counter_0p9);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "REVISIT_SCORE_0P5";
    temp_vec.clear();
    temp_vec.push_back((double)revisit_counter_0p5);
    Export_Utils::file_export_selector(temp_vec, f_p);

    // Export the Tikz files for the 3 contrast items
    f_p.extension = ".tex";
    string fig_title = seq->get_ds_name()+" Seq. "+seq->get_seq_name();

    f_p.tag = "REVISIT_SCORE_FIG";
    Export_Utils::create_vector_tikz_figure(closest_match_score_stats, SYS_CMD::CMD_RUN_REVISIT_FREQ, f_p, 
        "[REVISIT_SCORE] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Frames", "DBow2 Score");

    f_p.tag = "REVISIT_DIST_FIG";
    Export_Utils::create_vector_tikz_figure(closest_match_distance_stats, SYS_CMD::CMD_RUN_REVISIT_FREQ, f_p, 
        "[REVISIT_DIST] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Frames", "Distance to closest Match (Frames)");
}

vector_stats DBoW2_Scoreboard::get_score_stats()
{
    return closest_match_score_stats;
}
vector_stats DBoW2_Scoreboard::get_distance_stats()
{
    return closest_match_distance_stats;
}
int DBoW2_Scoreboard::get_revisit_score_1p0()
{
    return revisit_counter_1p0;
}
int DBoW2_Scoreboard::get_revisit_score_0p9()
{
    return revisit_counter_0p9;
}
int DBoW2_Scoreboard::get_revisit_score_0p5()
{
    return revisit_counter_0p5;
}