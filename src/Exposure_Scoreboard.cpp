#include "common.h"

Exposure_Scoreboard::Exposure_Scoreboard(Sequence* m_seq): Sequence_Scoreboard(m_seq)
{
    proper_exposure_count = 0;
    under_exposure_count = 0;
    over_exposure_count = 0;
    black_exposure_count = 0;
    white_exposure_count = 0;

    proper_exposure_percent = 0;
    under_exposure_percent = 0;
    over_exposure_percent = 0;
    black_exposure_percent = 0;
    white_exposure_percent = 0;
}

Exposure_Scoreboard::~Exposure_Scoreboard()
{
}

void Exposure_Scoreboard::export_results()
{
    // calculate vector stats
    Stats_Utils::calculate_vector_stats(mean_vals, mean_vec_stats);
    Stats_Utils::calculate_vector_stats(skewness_vals, skewness_vec_stats);
    Stats_Utils::calculate_vector_stats(img_zone, img_zone_vec_stats);

    // calculate the percentage values
    calculate_metrics_percentages();

    // Export the per-image results
    f_p.tag = "EXPOSURE_MEAN";
    Export_Utils::file_export_selector(mean_vals, f_p);

    f_p.tag = "EXPOSURE_SKEW";
    Export_Utils::file_export_selector(skewness_vals, f_p);

    f_p.tag = "EXPOSURE_ZONE";
    Export_Utils::file_export_selector(img_zone, f_p);

    // Export general blurring stats
    vector<double> temp_vec;
    f_p.tag = "OVER_EXPOSURE_COUNT";
    temp_vec.clear();
    temp_vec.push_back((double)over_exposure_count);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "OVER_EXPOSURE_PERCENT";
    temp_vec.clear();
    temp_vec.push_back((double)over_exposure_percent);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "UNDER_EXPOSURE_COUNT";
    temp_vec.clear();
    temp_vec.push_back((double)under_exposure_count);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "UNDER_EXPOSURE_PERCENT";
    temp_vec.clear();
    temp_vec.push_back((double)under_exposure_percent);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "PROPER_EXPOSURE_COUNT";
    temp_vec.clear();
    temp_vec.push_back((double)proper_exposure_count);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "PROPER_EXPOSURE_PERCENT";
    temp_vec.clear();
    temp_vec.push_back((double)proper_exposure_percent);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "BLACK_EXPOSURE_COUNT";
    temp_vec.clear();
    temp_vec.push_back((double)black_exposure_count);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "BLACK_EXPOSURE_PERCENT";
    temp_vec.clear();
    temp_vec.push_back((double)black_exposure_percent);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "WHITE_EXPOSURE_COUNT";
    temp_vec.clear();
    temp_vec.push_back((double)white_exposure_count);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "WHITE_EXPOSURE_PERCENT";
    temp_vec.clear();
    temp_vec.push_back((double)white_exposure_percent);
    Export_Utils::file_export_selector(temp_vec, f_p);

    // export the tikz files
    string fig_title = f_p.ds_name+" Seq. "+f_p.seq_name;
    f_p.extension = ".tex";

    f_p.tag = "EXPOSURE_MEAN_FIG";
    Export_Utils::create_vector_tikz_figure(mean_vec_stats, SYS_CMD::CMD_RUN_EXPOSURE, f_p, 
        "[EXPOSURE_MEAN] "+f_p.ds_name+" Seq. "+f_p.seq_name, "Frames", "Exposure Mean");

    f_p.tag = "EXPOSURE_SKEW_FIG";
    Export_Utils::create_vector_tikz_figure(skewness_vec_stats, SYS_CMD::CMD_RUN_EXPOSURE, f_p, 
        "[EXPOSURE_SKEW] "+f_p.ds_name+" Seq. "+f_p.seq_name, "Frames", "Exposure Skewness");

    f_p.tag = "EXPOSURE_ZONE_FIG";
    Export_Utils::create_vector_tikz_figure(skewness_vec_stats, SYS_CMD::CMD_RUN_EXPOSURE, f_p, 
        "[EXPOSURE_ZONE] "+f_p.ds_name+" Seq. "+f_p.seq_name, "Frames", "Exposure Skewness");
}

void Exposure_Scoreboard::add_exposure_results_entry(EXPOSURE_STATUS m_status, double m_mean, double m_skewness, double m_zone)
{
    // add results of mean and skewness to the vectors 
    mean_vals.push_back(m_mean);
    skewness_vals.push_back(m_skewness);
    img_zone.push_back(m_zone);

    // increment status counters based on reported status
    switch (m_status)
    {
        case OVER_EXPOSURE:
            over_exposure_count ++;
            break;

        case UNDER_EXPOSURE:
            under_exposure_count ++;
            break;
        
        case PROPER_EXPOSURE:
            proper_exposure_count ++;
            break;

        case BLACK_EXPOSURE:
            black_exposure_count ++ ;
            break;

        case WHITE_EXPOSURE:
            white_exposure_count ++ ;
            break; 
        
        default:
            break;
    }
}

void Exposure_Scoreboard::calculate_metrics_percentages()
{
    proper_exposure_percent     = ((double)proper_exposure_count/(double)seq->get_seq_img_count())*100 ;
    under_exposure_percent      = ((double)under_exposure_count/(double)seq->get_seq_img_count())*100 ;
    over_exposure_percent       = ((double)over_exposure_count/(double)seq->get_seq_img_count())*100 ;
    black_exposure_percent      = ((double)black_exposure_count/(double)seq->get_seq_img_count())*100 ;
    white_exposure_percent      = ((double)white_exposure_count/(double)seq->get_seq_img_count())*100 ;
}

// setter functions
void Exposure_Scoreboard::set_proper_exposure_count(int m_count)
{
    proper_exposure_count = m_count;
}
void Exposure_Scoreboard::set_under_exposure_count(int m_count)
{
    under_exposure_count = m_count;
}
void Exposure_Scoreboard::set_over_exposure_count(int m_count)
{
    over_exposure_count = m_count;
}
void Exposure_Scoreboard::set_black_exposure_count(int m_count)
{
    black_exposure_count = m_count;
}
void Exposure_Scoreboard::set_white_exposure_count(int m_count)
{
    white_exposure_count = m_count;
}

void Exposure_Scoreboard::set_proper_exposure_percent(double m_percent)
{
    proper_exposure_percent = m_percent;
}
void Exposure_Scoreboard::set_under_exposure_percent(double m_percent)
{
    under_exposure_percent = m_percent;
}
void Exposure_Scoreboard::set_over_exposure_percent(double m_percent)
{
    over_exposure_percent = m_percent;
}
void Exposure_Scoreboard::set_black_exposure_percent(double m_percent)
{
    black_exposure_percent = m_percent;
}
void Exposure_Scoreboard::set_white_exposure_percent(double m_percent)
{
    white_exposure_percent = m_percent;
}

// getter functions
int Exposure_Scoreboard::get_proper_exposure_count()
{
    return proper_exposure_count;
}
int Exposure_Scoreboard::get_under_exposure_count()
{
    return under_exposure_count;
}
int Exposure_Scoreboard::get_over_exposure_count()
{
    return over_exposure_count;
}
int Exposure_Scoreboard::get_black_exposure_count()
{
    return black_exposure_count;
}
int Exposure_Scoreboard::get_white_exposure_count()
{
    return white_exposure_count;
}

int Exposure_Scoreboard::get_proper_exposure_percent()
{
    return proper_exposure_percent;
}
int Exposure_Scoreboard::get_under_exposure_percent()
{
    return under_exposure_percent;
}
int Exposure_Scoreboard::get_over_exposure_percent()
{
    return over_exposure_percent;
}
int Exposure_Scoreboard::get_black_exposure_percent()
{
    return black_exposure_percent;
}
int Exposure_Scoreboard::get_white_exposure_percent()
{
    return white_exposure_percent;
}

vector_stats Exposure_Scoreboard::get_mean_vec_stats()
{
    return mean_vec_stats;
}
vector_stats Exposure_Scoreboard::get_skewness_vec_stats()
{
    return skewness_vec_stats;
}
vector_stats Exposure_Scoreboard::get_zone_vec_stats()
{
    return img_zone_vec_stats;
}