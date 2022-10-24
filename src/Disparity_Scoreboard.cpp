#include "common.h"


Disparity_Scoreboard::Disparity_Scoreboard(Sequence* m_seq): Sequence_Scoreboard(m_seq)
{
    DM_StereoBM = new Disparity_Method_Scoreboard(m_seq, "BM");
    DM_stereoSGBM = new Disparity_Method_Scoreboard(m_seq, "SGBM");
}

Disparity_Scoreboard::~Disparity_Scoreboard()
{
}

void Disparity_Scoreboard::export_results()
{
    DM_StereoBM->export_results();
    DM_stereoSGBM->export_results();
}

void Disparity_Scoreboard::add_results(double min_val, double max_val, double avg_val, double std_div_val, DISPARITY_ALGO m_mode)
{
    switch (m_mode)
    {
        case STEREO_BM:
            DM_StereoBM->add_disparity_scores(min_val, max_val, avg_val, std_div_val);
            break;
        
        case STEREO_SGBM:
            DM_stereoSGBM->add_disparity_scores(min_val, max_val, avg_val, std_div_val);
            break;
        
        default:
            break;
    }
}

vector_stats Disparity_Scoreboard::get_min_disp_vec_stats(DISPARITY_ALGO m_mode)
{
    switch (m_mode)
    {
        case STEREO_BM:
            return DM_StereoBM->get_min_disp_vec_stats();
            break;
        
        case STEREO_SGBM:
        default:
            return DM_stereoSGBM->get_min_disp_vec_stats();
            break;
    }
}
vector_stats Disparity_Scoreboard::get_max_disp_vec_stats(DISPARITY_ALGO m_mode)
{
    switch (m_mode)
    {
        case STEREO_BM:
            return DM_StereoBM->get_max_disp_vec_stats();
            break;
        
        case STEREO_SGBM:
        default:
            return DM_stereoSGBM->get_max_disp_vec_stats();
            break;
    }
}
vector_stats Disparity_Scoreboard::get_avg_disp_vec_stats(DISPARITY_ALGO m_mode)
{
    switch (m_mode)
    {
        case STEREO_BM:
            return DM_StereoBM->get_avg_disp_vec_stats();
            break;
        
        case STEREO_SGBM:
        default:
            return DM_stereoSGBM->get_avg_disp_vec_stats();
            break;
    }
}
vector_stats Disparity_Scoreboard::get_std_div_disp_vec_stats(DISPARITY_ALGO m_mode)
{
    switch (m_mode)
    {
        case STEREO_BM:
            return DM_StereoBM->get_std_div_disp_vec_stats();
            break;
        
        case STEREO_SGBM:
        default:
            return DM_stereoSGBM->get_std_div_disp_vec_stats();
            break;
    }
}