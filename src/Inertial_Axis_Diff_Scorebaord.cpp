#include "common.h"

Inertial_Axis_Diff_Scorebaord::Inertial_Axis_Diff_Scorebaord(Sequence* m_seq, string in_axis_str,INERTIAL_MODE m_mode): Sequence_Scoreboard(m_seq)
{
    m_axis_str = in_axis_str;
    in_mode = m_mode;
}

Inertial_Axis_Diff_Scorebaord::~Inertial_Axis_Diff_Scorebaord()
{
}

void Inertial_Axis_Diff_Scorebaord::export_results()
{
    cout << "[INERTIAL_DIFF] *** Exporting Results " << m_axis_str << " ... " << endl;

    // get inertial data for current axis
    vector<double> axis_gyro_data, axis_acc_data;
    seq->get_seq_inertial_data()->get_inertial_data_by_axis(in_mode, axis_gyro_data, axis_acc_data);

    // calculate stats of vectors
    Stats_Utils::calculate_vector_stats(axis_gyro_data, g_stats);
    Stats_Utils::calculate_vector_stats(axis_acc_data, a_stats);
    
    Stats_Utils::calculate_vector_stats(g_1st_diff, g_1st_diff_stats);
    Stats_Utils::calculate_vector_stats(a_1st_diff, a_1st_diff_stats);

    Stats_Utils::calculate_vector_stats(g_2nd_diff, g_2nd_diff_stats);
    Stats_Utils::calculate_vector_stats(a_2nd_diff, a_2nd_diff_stats);

    // export sequence inertial data
    f_p.tag = "G"+m_axis_str;
    Export_Utils::file_export_selector(axis_gyro_data, f_p);
    f_p.tag = "A"+m_axis_str;
    Export_Utils::file_export_selector(axis_acc_data, f_p);

    // export first-order time_derivative data
    f_p.tag = "G"+m_axis_str+"_1ST_DIFF";
    Export_Utils::file_export_selector(g_1st_diff, f_p);
    f_p.tag = "A"+m_axis_str+"_1ST_DIFF";
    Export_Utils::file_export_selector(a_1st_diff, f_p);

    // export second-order time_derivative data
    f_p.tag = "G"+m_axis_str+"_2ND_DIFF";
    Export_Utils::file_export_selector(g_2nd_diff, f_p);
    f_p.tag = "A"+m_axis_str+"_2ND_DIFF";
    Export_Utils::file_export_selector(a_2nd_diff, f_p);

    // Export the Tikz files for the 3 contrast items
    f_p.extension = ".tex";
    string fig_title = seq->get_ds_name()+" Seq. "+seq->get_seq_name();

    f_p.tag = "G"+m_axis_str+"_FIG";
    Export_Utils::create_vector_tikz_figure(g_stats, SYS_CMD::CMD_RUN_INERTIAL_DIFF, f_p, 
        "[G"+m_axis_str+"] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Sample", "deg/sec");
    f_p.tag = "A"+m_axis_str+"_FIG";
    Export_Utils::create_vector_tikz_figure(a_stats, SYS_CMD::CMD_RUN_INERTIAL_DIFF, f_p, 
        "[A"+m_axis_str+"] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Sample", "m/sec^2");

    f_p.tag = "G"+m_axis_str+"_1ST_DIFF_FIG";
    Export_Utils::create_vector_tikz_figure(g_1st_diff_stats, SYS_CMD::CMD_RUN_INERTIAL_DIFF, f_p, 
        "[G"+m_axis_str+"_1ST_DIFF] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Sample", "deg/sec^2");
    f_p.tag = "AX_1ST_DIFF_FIG";
    Export_Utils::create_vector_tikz_figure(a_1st_diff_stats, SYS_CMD::CMD_RUN_INERTIAL_DIFF, f_p, 
        "[A"+m_axis_str+"_1ST_DIFF] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Sample", "m/sec^3");

    f_p.tag = "G"+m_axis_str+"_2ND_DIFF_FIG";
    Export_Utils::create_vector_tikz_figure(g_2nd_diff_stats, SYS_CMD::CMD_RUN_INERTIAL_DIFF, f_p, 
        "[G"+m_axis_str+"_2ND_DIFF] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Sample", "deg/sec^3");
    f_p.tag = "A"+m_axis_str+"_2ND_DIFF_FIG";
    Export_Utils::create_vector_tikz_figure(a_2nd_diff_stats, SYS_CMD::CMD_RUN_INERTIAL_DIFF, f_p, 
        "[A"+m_axis_str+"_2ND_DIFF] "+seq->get_ds_name()+" Seq. "+seq->get_seq_name(), "Sample", "m/sec^4");
}

void Inertial_Axis_Diff_Scorebaord::add_gyro_inertial_results(vector<double> m_1st_diff, vector<double> m_2nd_diff)
{
    g_1st_diff = m_1st_diff;
    g_2nd_diff = m_2nd_diff;
}

void Inertial_Axis_Diff_Scorebaord::add_acc_inertial_results(vector<double> m_1st_diff, vector<double> m_2nd_diff)
{
    a_1st_diff = m_1st_diff;
    a_2nd_diff = m_2nd_diff;
}


vector_stats Inertial_Axis_Diff_Scorebaord::get_g_stats()
{
    return g_stats;
}
vector_stats Inertial_Axis_Diff_Scorebaord::get_a_stats()
{
    return a_stats;
}
vector_stats Inertial_Axis_Diff_Scorebaord::get_g_1st_diff_stats()
{
    return g_1st_diff_stats;
}
vector_stats Inertial_Axis_Diff_Scorebaord::get_a_1st_diff_stats()
{
    return a_1st_diff_stats;
}
vector_stats Inertial_Axis_Diff_Scorebaord::get_g_2nd_diff_stats()
{
    return g_2nd_diff_stats;
}
vector_stats Inertial_Axis_Diff_Scorebaord::get_a_2nd_diff_stats()
{
    return a_2nd_diff_stats;
}