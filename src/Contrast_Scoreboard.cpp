#include "common.h"

Contrast_Scoreboard::Contrast_Scoreboard(Sequence* m_seq): Sequence_Scoreboard(m_seq)
{
}

Contrast_Scoreboard::~Contrast_Scoreboard()
{
}

void Contrast_Scoreboard::export_results()
{
    cout << "[CONTRAST] *** Exporting Results ... " << endl;
    // calculate vector stats
    Stats_Utils::calculate_vector_stats(weber_contrast, weber_contrast_stats);
    Stats_Utils::calculate_vector_stats(michelson_contrast, michelson_contrast_stats);
    Stats_Utils::calculate_vector_stats(rms_contrast, rms_contrast_stats);
    Stats_Utils::calculate_vector_stats(CR_contrast, CR_contrast_stats);

    // Export the per-image results
    f_p.tag = "CONTRAST_WEBER";
    Export_Utils::file_export_selector(weber_contrast, f_p);

    f_p.tag = "CONTRAST_MICHELSON";
    Export_Utils::file_export_selector(michelson_contrast, f_p);

    f_p.tag = "CONTRAST_RMS";
    Export_Utils::file_export_selector(rms_contrast, f_p);

    f_p.tag = "CONTRAST_CR";
    Export_Utils::file_export_selector(CR_contrast, f_p);
    

    // Export the Tikz files for the 3 contrast items
    f_p.extension = ".tex";
    string fig_title = seq->get_ds_name()+" Seq. "+seq->get_seq_name();

    f_p.tag = "CONTRAST_WEBER_FIG";
    Export_Utils::create_vector_tikz_figure(weber_contrast_stats, SYS_CMD::CMD_RUN_CONTRAST, f_p, 
        "[CONTRAST_WEBER] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Frames", "Constrast Score");

    f_p.tag = "CONTRAST_MICHELSON_FIG";
    Export_Utils::create_vector_tikz_figure(michelson_contrast_stats, SYS_CMD::CMD_RUN_CONTRAST, f_p, 
        "[CONTRAST_MICHELSON] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Frames", "Constrast Score");

    f_p.tag = "CONTRAST_RMS_FIG";
    Export_Utils::create_vector_tikz_figure(rms_contrast_stats, SYS_CMD::CMD_RUN_CONTRAST, f_p, 
        "[CONTRAST_RMS] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Frames", "Constrast Score");

    f_p.tag = "CONTRAST_CR_FIG";
    Export_Utils::create_vector_tikz_figure(CR_contrast_stats, SYS_CMD::CMD_RUN_CONTRAST, f_p, 
        "[CONTRAST_CR] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Frames", "Constrast Score");
}

void Contrast_Scoreboard::add_contrast_scores(double rms, double weber, double michelson, double CR)
{
    rms_contrast.push_back(rms);
    weber_contrast.push_back(weber);
    michelson_contrast.push_back(michelson);
    CR_contrast.push_back(CR); 
}


vector_stats Contrast_Scoreboard::get_rms_stats()
{
    return rms_contrast_stats;
}
vector_stats Contrast_Scoreboard::get_weber_stats()
{
    return weber_contrast_stats;
}
vector_stats Contrast_Scoreboard::get_michelson_stats()
{
    return michelson_contrast_stats;
}
vector_stats Contrast_Scoreboard::get_CR_stats()
{
    return CR_contrast_stats;
}