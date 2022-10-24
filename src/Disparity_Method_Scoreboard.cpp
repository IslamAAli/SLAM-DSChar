#include "common.h"

Disparity_Method_Scoreboard::Disparity_Method_Scoreboard(Sequence* m_seq, string m_method_name): Sequence_Scoreboard(m_seq)
{
    method_name = m_method_name;
}

Disparity_Method_Scoreboard::~Disparity_Method_Scoreboard()
{
}

void Disparity_Method_Scoreboard::export_results()
{
    // calculate vector stats
    Stats_Utils::calculate_vector_stats(min_disparity, min_disp_vec_stats);
    Stats_Utils::calculate_vector_stats(max_disparity, max_disp_vec_stats);
    Stats_Utils::calculate_vector_stats(avg_disparity, avg_disp_vec_stats);
    Stats_Utils::calculate_vector_stats(std_div_disparity, std_div_disp_vec_stats);

    // Export the per-image results
    f_p.tag = "DISPARITY_MIN_"+method_name;
    Export_Utils::file_export_selector(min_disparity, f_p);

    f_p.tag = "DISPARITY_MAX_"+method_name;
    Export_Utils::file_export_selector(max_disparity, f_p);

    f_p.tag = "DISPARITY_AVG_"+method_name;
    Export_Utils::file_export_selector(avg_disparity, f_p);

    f_p.tag = "DISPARITY_STD_DIV_"+method_name;
    Export_Utils::file_export_selector(std_div_disparity, f_p);

    // Export the per-image figures
    f_p.tag = "DISPARITY_MIN_"+method_name+"_FIG";
    Export_Utils::create_vector_tikz_figure(min_disp_vec_stats, SYS_CMD::CMD_RUN_DISPARITY, f_p, 
        "[DISPARITY_MIN_"+method_name+"] "+f_p.ds_name+" Seq. "+f_p.seq_name, "Frames", "Min. Disparity");

    f_p.tag = "DISPARITY_MAX_"+method_name+"_FIG";
    Export_Utils::create_vector_tikz_figure(max_disp_vec_stats, SYS_CMD::CMD_RUN_DISPARITY, f_p, 
        "[DISPARITY_MAX_"+method_name+"] "+f_p.ds_name+" Seq. "+f_p.seq_name, "Frames", "Max. Disparity");

    f_p.tag = "DISPARITY_AVG_"+method_name+"_FIG";
    Export_Utils::create_vector_tikz_figure(min_disp_vec_stats, SYS_CMD::CMD_RUN_DISPARITY, f_p, 
        "[DISPARITY_AVG_"+method_name+"] "+f_p.ds_name+" Seq. "+f_p.seq_name, "Frames", "Avg. Disparity");

    f_p.tag = "DISPARITY_STD_DIV_"+method_name+"_FIG";
    Export_Utils::create_vector_tikz_figure(std_div_disp_vec_stats, SYS_CMD::CMD_RUN_DISPARITY, f_p, 
        "[DISPARITY_STD_DIV_"+method_name+"] "+f_p.ds_name+" Seq. "+f_p.seq_name, "Frames", "Std. Div. Disparity");
}

void Disparity_Method_Scoreboard::add_disparity_scores(double m_min_disp, double m_max_disp, double m_avg_disp, double m_std_div_disp)
{
    min_disparity.push_back(m_min_disp);
    max_disparity.push_back(m_max_disp);
    avg_disparity.push_back(m_avg_disp);
    std_div_disparity.push_back(m_std_div_disp);
}


vector_stats Disparity_Method_Scoreboard::get_min_disp_vec_stats()
{
    return min_disp_vec_stats;
}
vector_stats Disparity_Method_Scoreboard::get_max_disp_vec_stats()
{
    return max_disp_vec_stats;
}
vector_stats Disparity_Method_Scoreboard::get_avg_disp_vec_stats()
{
    return avg_disp_vec_stats;
}
vector_stats Disparity_Method_Scoreboard::get_std_div_disp_vec_stats()
{
    return std_div_disp_vec_stats;
}