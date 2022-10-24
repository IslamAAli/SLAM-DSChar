#include "common.h"

Features_Scoreboard::Features_Scoreboard(Sequence* m_seq) : Sequence_Scoreboard(m_seq)
{
    SIFT_features = new Visual_Feature_Scoreboard(m_seq, "SIFT");
    FAST_features = new Visual_Feature_Scoreboard(m_seq, "FAST");
    ORB_features = new Visual_Feature_Scoreboard(m_seq, "ORB");
}

Features_Scoreboard::~Features_Scoreboard()
{
}

void Features_Scoreboard::add_features_metric_scrore(int f_count, double f_dist_abs, double f_dist_avg, VISUAL_FEATURES m_type)
{
    switch (m_type)
    {
        case VF_SIFT:
            SIFT_features->add_features_metric_scrore(f_count, f_dist_abs, f_dist_avg);
            break;

        case VF_FAST:
            FAST_features->add_features_metric_scrore(f_count, f_dist_abs, f_dist_avg);
            break;
        
        case VF_ORB:
        default:
            ORB_features->add_features_metric_scrore(f_count, f_dist_abs, f_dist_avg);
            break;
    }
}

void Features_Scoreboard::export_results()
{
    SIFT_features->export_results();
    FAST_features->export_results();
    ORB_features->export_results();
}

vector_stats Features_Scoreboard::get_score_count_stats(VISUAL_FEATURES m_type)
{
    switch (m_type)
    {
        case VF_SIFT:
            return SIFT_features->get_score_count_stats();
            break;

        case VF_FAST:
            return SIFT_features->get_score_count_stats();
            break;

        case VF_ORB:
        default:
            return SIFT_features->get_score_count_stats();
            break;
    }
}
vector_stats Features_Scoreboard::get_Fdist_abs_stats(VISUAL_FEATURES m_type)
{
    switch (m_type)
    {
        case VF_SIFT:
            return SIFT_features->get_Fdist_abs_stats();
            break;

        case VF_FAST:
            return SIFT_features->get_Fdist_abs_stats();
            break;

        case VF_ORB:
        default:
            return SIFT_features->get_Fdist_abs_stats();
            break;
    }
}
vector_stats Features_Scoreboard::get_Fdist_avg_stats(VISUAL_FEATURES m_type)
{
    switch (m_type)
    {
        case VF_SIFT:
            return SIFT_features->get_Fdist_avg_stats();
            break;

        case VF_FAST:
            return SIFT_features->get_Fdist_avg_stats();
            break;

        case VF_ORB:
        default:
            return SIFT_features->get_Fdist_avg_stats();
            break;
    }
}