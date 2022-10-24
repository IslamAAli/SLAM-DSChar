#include "common.h"

Brightness_Scoreboard::Brightness_Scoreboard(Sequence* m_seq): Sequence_Scoreboard(m_seq)
{
    brightness_change_1sigma    = 0;
    brightness_change_2sigma    = 0;
    brightness_change_3sigma    = 0;
}

Brightness_Scoreboard::~Brightness_Scoreboard()
{
}


void Brightness_Scoreboard::add_brightness_score(double m_b_val)
{
    brightness_scores.push_back(m_b_val);
}

vector<double> Brightness_Scoreboard::get_brightness_scores()
{
    return brightness_scores;
}

void Brightness_Scoreboard::add_brightness_change_score(double diff_1sigma, double diff_2sigma, double diff_3sigma)
{
    brightness_change_1sigma = diff_1sigma;
    brightness_change_2sigma = diff_2sigma;
    brightness_change_3sigma = diff_3sigma;

    brightness_change_1sigma_percentage = (brightness_change_1sigma/seq->get_seq_img_count())*100;
    brightness_change_2sigma_percentage = (brightness_change_2sigma/seq->get_seq_img_count())*100;
    brightness_change_3sigma_percentage = (brightness_change_3sigma/seq->get_seq_img_count())*100;
}

void Brightness_Scoreboard::set_brightness_stats(vector_stats& m_vector_stats)
{
    brightness_stats = m_vector_stats;
}

void Brightness_Scoreboard::set_brightness_scores_diff(vector<double>& m_vec)
{
    brightness_scores_diff = m_vec;
}

void Brightness_Scoreboard::set_brightness_diff_stats(vector_stats& m_vector_stats)
{
    brightness_diff_stats = m_vector_stats;
}

vector<double> Brightness_Scoreboard::get_brighness_sigma_scores()
{
    return {brightness_change_1sigma, brightness_change_1sigma_percentage,
            brightness_change_2sigma, brightness_change_2sigma_percentage,
            brightness_change_3sigma, brightness_change_3sigma_percentage};
}

vector_stats Brightness_Scoreboard::get_brightness_stats()
{
    return brightness_stats;
}

void Brightness_Scoreboard::export_results()
{
    cout << "[BRIGHTNESS] *** Exporting Results ... " << endl;
    // calculate the brightness stats
    Stats_Utils::calculate_vector_stats(brightness_scores, brightness_stats);

    // export the brightness scores
    f_p.tag = "BRIGHTNESS";
    Export_Utils::file_export_selector(brightness_scores, f_p);
    
    // export the brightness changes metrics
    f_p.tag = "BRIGHTNESS_CHANGE";
    vector<double> temp_vec = {(double)seq->get_seq_img_count(), 
                                brightness_change_1sigma, brightness_change_1sigma_percentage, 
                                brightness_change_2sigma, brightness_change_2sigma_percentage, 
                                brightness_change_3sigma, brightness_change_3sigma_percentage};
    Export_Utils::file_export_selector(temp_vec, f_p);

    // export sigma counts and percentages
    f_p.tag = "BRIGHTNESS_DIFF_1SIGMA";
    temp_vec.clear();
    temp_vec.push_back(brightness_change_1sigma);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "BRIGHTNESS_DIFF_2SIGMA";
    temp_vec.clear();
    temp_vec.push_back(brightness_change_2sigma);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "BRIGHTNESS_DIFF_3SIGMA";
    temp_vec.clear();
    temp_vec.push_back(brightness_change_3sigma);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "BRIGHTNESS_DIFF_1SIGMA_RATIO";
    temp_vec.clear();
    temp_vec.push_back(brightness_change_1sigma_percentage);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "BRIGHTNESS_DIFF_2SIGMA_RATIO";
    temp_vec.clear();
    temp_vec.push_back(brightness_change_2sigma_percentage);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "BRIGHTNESS_DIFF_3SIGMA_RATIO";
    temp_vec.clear();
    temp_vec.push_back(brightness_change_3sigma_percentage);
    Export_Utils::file_export_selector(temp_vec, f_p);

    // export the brighness time derivative scores
    f_p.tag = "BRIGHTNESS_DIFF";
    Export_Utils::file_export_selector(brightness_scores_diff, f_p);

    // export the stats values
    f_p.tag = "BRIGHTNESS_STATS";
    f_p.extension = ".txt";     
    Export_Utils::file_export_selector(Stats_Utils::convert_stats_to_vector(brightness_stats), f_p);

    // export the tikz file for the brightness time derivative 
    f_p.tag = "BRIGHTNESS_DIFF_FIG";
    f_p.extension = ".tex";
    Export_Utils::create_vector_tikz_figure(brightness_diff_stats, SYS_CMD::CMD_RUN_BRIGHTNESS, f_p, 
                "[BRIGHTNESS] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Frames", "Brightness Score");

    // export the tikz file for the brightness
    f_p.tag = "BRIGHTNESS_FIG";
    f_p.extension = ".tex";
    Export_Utils::create_vector_tikz_figure(brightness_stats, SYS_CMD::CMD_RUN_BRIGHTNESS, f_p,
                "[BRIGHTNESS_DIFF] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Frames", "$\\frac{d B}{dt}$");
}