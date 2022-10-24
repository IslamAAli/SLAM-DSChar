#include "common.h"


Visual_Feature_Scoreboard::Visual_Feature_Scoreboard(Sequence* m_seq, string f_name): Sequence_Scoreboard(m_seq)
{
    feature_name = f_name;
}

Visual_Feature_Scoreboard::~Visual_Feature_Scoreboard()
{
}

void Visual_Feature_Scoreboard::add_features_metric_scrore(int f_count, double f_dist_abs, double f_dist_avg)
{
    score_count.push_back(f_count);
    score_Fdist_abs.push_back(f_dist_abs);
    score_Fdist_avg.push_back(f_dist_avg);
}

void Visual_Feature_Scoreboard::export_results()
{
    cout << "[FEATURES ANALYSIS] *** Exporting Results for "<< feature_name << " ... " << endl;

    // calculte vectors stats
    Stats_Utils::calculate_vector_stats(score_count, score_count_stats);
    Stats_Utils::calculate_vector_stats(score_Fdist_abs, score_Fdist_abs_stats);
    Stats_Utils::calculate_vector_stats(score_Fdist_avg, score_Fdist_avg_stats);

    // Export the per-image results
    f_p.tag = feature_name+"_COUNT";
    Export_Utils::file_export_selector(score_count, f_p);
    f_p.tag = feature_name+"_DIST_ABS";
    Export_Utils::file_export_selector(score_Fdist_abs, f_p);
    f_p.tag = feature_name+"_DIST_AVG";
    Export_Utils::file_export_selector(score_Fdist_avg, f_p);

    // export the tikz files
    string fig_title = seq->get_ds_name()+" Seq. "+seq->get_seq_name();
    f_p.extension = ".tex";

    f_p.tag = feature_name+"_COUNT_FIG";
    Export_Utils::create_vector_tikz_figure(score_count_stats, SYS_CMD::CMD_RUN_FEATURES, f_p, 
        "["+feature_name+"_COUNT] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Frames", "# of Features");
    f_p.tag = feature_name+"_DIST_ABS_FIG";
    Export_Utils::create_vector_tikz_figure(score_Fdist_abs_stats, SYS_CMD::CMD_RUN_FEATURES, f_p, 
        "["+feature_name+"_DIST_ABS] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Frames", "Feature Spatial Distribution Ratio");
    f_p.tag = feature_name+"_DIST_AVG_FIG";
    Export_Utils::create_vector_tikz_figure(score_Fdist_avg_stats, SYS_CMD::CMD_RUN_FEATURES, f_p, 
        "["+feature_name+"_DIST_AVG] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Frames", "Feature Spatial Distribution Ratio");
}

vector_stats Visual_Feature_Scoreboard::get_score_count_stats()
{
    return score_count_stats;
}
vector_stats Visual_Feature_Scoreboard::get_Fdist_abs_stats()
{
    return score_Fdist_abs_stats;
}
vector_stats Visual_Feature_Scoreboard::get_Fdist_avg_stats()
{
    return score_Fdist_avg_stats;
}