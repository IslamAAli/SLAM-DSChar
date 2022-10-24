#include "common.h"

Blur_Scoreboard::Blur_Scoreboard(Sequence* m_seq): Sequence_Scoreboard(m_seq)
{
    blurred_images_count                = 0 ;
    global_blurred_images               = 0 ;
    local_blurred_images                = 0 ;
    blurred_images_percentage           = 0 ;
    global_blurred_images_percentage    = 0 ;
    local_blurred_images_percentage     = 0 ;
}

Blur_Scoreboard::~Blur_Scoreboard()
{
}

double Blur_Scoreboard::get_blurred_img_percent()
{
    return blurred_images_percentage;
}
double Blur_Scoreboard::get_global_blur_percent()
{
    return global_blurred_images_percentage;
}
double Blur_Scoreboard::get_local_blur_percent()
{
    return local_blurred_images_percentage;
}
vector_stats Blur_Scoreboard::get_blur_score_stats()
{
    return blur_score_vec_stats;
}
vector_stats Blur_Scoreboard::get_blur_percent_stats()
{
    return blur_percentage_vec_stats;
}

void Blur_Scoreboard::add_blur_metric_scores(double image_blur_score, double blur_percentage, bool blur_result, bool global_blur, bool local_blur)
{
    // add values to the vectors
    blur_score_vec.push_back(image_blur_score);
    blur_percentage_vec.push_back(blur_percentage);

    // check statues and increment counters accoringly
    if(blur_result)
        blurred_images_count ++;

    if(global_blur)
        global_blurred_images ++;

    if(local_blur)
        local_blurred_images ++;
}

void Blur_Scoreboard::add_blur_metric_percentage()
{
    blurred_images_percentage           = ((double)blurred_images_count/(double)seq->get_seq_img_count())*100 ;
    global_blurred_images_percentage    = ((double)global_blurred_images/(double)seq->get_seq_img_count())*100 ;
    local_blurred_images_percentage     = ((double)local_blurred_images/(double)seq->get_seq_img_count())*100 ;
}

void Blur_Scoreboard::export_results()
{
    cout << "[BLURRING] *** Exporting Results ... " << endl;
    // calculate stats of vectors
    Stats_Utils::calculate_vector_stats(blur_score_vec, blur_score_vec_stats);
    Stats_Utils::calculate_vector_stats(blur_percentage_vec, blur_percentage_vec_stats);
    // calculate percentages 
    add_blur_metric_percentage();

    // Export the per-image results
    f_p.tag = "BLUR_SCORE";
    Export_Utils::file_export_selector(blur_score_vec, f_p);

    f_p.tag = "BLUR_PERCENT";
    Export_Utils::file_export_selector(blur_percentage_vec, f_p);

    // Export general blurring stats
    vector<double> temp_vec;
    f_p.tag = "BLUR_TOTAL_COUNT";
    temp_vec.clear();
    temp_vec.push_back((double)blurred_images_count);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "BLUR_TOTAL_PERCENT";
    temp_vec.clear();
    temp_vec.push_back((double)blurred_images_percentage);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "BLUR_LOCAL_COUNT";
    temp_vec.clear();
    temp_vec.push_back((double)local_blurred_images);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "BLUR_LOCAL_PERCENT";
    temp_vec.clear();
    temp_vec.push_back((double)local_blurred_images_percentage);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "BLUR_GLOBAL_COUNT";
    temp_vec.clear();
    temp_vec.push_back((double)global_blurred_images);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "BLUR_GLOBAL_PERCENT";
    temp_vec.clear();
    temp_vec.push_back((double)global_blurred_images_percentage);
    Export_Utils::file_export_selector(temp_vec, f_p);

    // export the tikz files
    string fig_title = f_p.ds_name+" Seq. "+f_p.seq_name;
    f_p.extension = ".tex";

    f_p.tag = "BLUR_SCORE_FIG";
    Export_Utils::create_vector_tikz_figure(blur_score_vec_stats, SYS_CMD::CMD_RUN_BLUR, f_p, 
        "[BLUR_SCORE] "+f_p.ds_name+" Seq. "+f_p.seq_name, "Frames", "Blurring Score");

    f_p.tag = "BLUR_PERCENT_FIG";
    Export_Utils::create_vector_tikz_figure(blur_score_vec_stats, SYS_CMD::CMD_RUN_BLUR, f_p, 
        "[BLUR_PERCENT] "+f_p.ds_name+" Seq. "+f_p.seq_name, "Frames", "Blurring Percentage");
}