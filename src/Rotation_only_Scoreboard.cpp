#include "common.h"

Rotation_only_Scoreboard::Rotation_only_Scoreboard(Sequence* m_seq): Sequence_Scoreboard(m_seq)
{
    rotation_only_count = 0 ;
    rotation_only_percentage = 0 ;
}

Rotation_only_Scoreboard::~Rotation_only_Scoreboard()
{
}

void Rotation_only_Scoreboard::set_rotation_only_count(int m_count)
{
    rotation_only_count = m_count;
}
int Rotation_only_Scoreboard::get_rotation_only_count()
{
    return rotation_only_count;
}

void Rotation_only_Scoreboard::increment_rotation_only_count()
{
    rotation_only_count ++ ;
}

double Rotation_only_Scoreboard::get_rotation_only_percentage()
{
    return rotation_only_percentage;
}
void Rotation_only_Scoreboard::set_rotation_only_percentage(double m_percentage)
{
    rotation_only_percentage = m_percentage;
}

vector<double> Rotation_only_Scoreboard::get_f_mag()
{
    return f_mag;
}
void Rotation_only_Scoreboard::set_f_mag(vector<double> m_vec)
{
    f_mag = m_vec;
}

vector_stats Rotation_only_Scoreboard::get_f_mag_stats()
{
    return f_mag_stats;
}
void Rotation_only_Scoreboard::set_f_mat_stats(vector_stats v_stats)
{
    f_mag_stats = v_stats;
}


void Rotation_only_Scoreboard::export_results()
{
    cout << "[INERTIAL_ROT_ONLY] *** Exporting Results  ... " << endl;

    // calculating stats
    Stats_Utils::calculate_vector_stats(f_mag, f_mag_stats);

    // Export the per-image results
    f_p.tag = "ACC_MAG";
    Export_Utils::file_export_selector(f_mag, f_p);

    vector<double> temp_vec;
    f_p.tag = "ROT_ONLY_COUNT";
    temp_vec.clear();
    temp_vec.push_back((double)rotation_only_count);
    Export_Utils::file_export_selector(temp_vec, f_p);

    f_p.tag = "ROT_ONLY_PERCENT";
    temp_vec.clear();
    temp_vec.push_back(rotation_only_percentage);
    Export_Utils::file_export_selector(temp_vec, f_p);

    // export the tikz file for the brightness time derivative 
    f_p.tag = "ACC_MAG_FIG";
    f_p.extension = ".tex";
    Export_Utils::create_vector_tikz_figure(f_mag_stats, SYS_CMD::CMD_RUN_INERTIAL_ROT_ONLY, f_p, 
                "[ACC_MAG] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Frames", "Acceleration Magnitude m/sec^2");
}