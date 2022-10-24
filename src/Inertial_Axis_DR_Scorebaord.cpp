#include "common.h"

Inertial_Axis_DR_Scorebaord::Inertial_Axis_DR_Scorebaord(Sequence* m_seq, string in_axis_str, INERTIAL_MODE m_mode): Sequence_Scoreboard(m_seq)
{
    m_axis_str = in_axis_str;
    in_mode = m_mode;

    g_inertial_DR_coverage_percentage  = 0 ;
    g_inertial_DR_limit_hit_count      = 0 ;
    g_inertial_DR_limit_hit_percentage = 0 ;

    a_inertial_DR_coverage_percentage  = 0 ;
    a_inertial_DR_limit_hit_count      = 0 ;
    a_inertial_DR_limit_hit_percentage = 0 ;
}

Inertial_Axis_DR_Scorebaord::~Inertial_Axis_DR_Scorebaord()
{
}

void Inertial_Axis_DR_Scorebaord::export_results()
{
    cout << "[INERTIAL_DR] *** Exporting Results " << m_axis_str << " ... " << endl;

    vector<double> temp_vec;
    f_p.tag = "G"+m_axis_str+"_DR_limit_count";
    temp_vec.clear();
    temp_vec.push_back((double)g_inertial_DR_limit_hit_count);
    Export_Utils::file_export_selector(temp_vec, f_p);


    f_p.tag = "A"+m_axis_str+"_DR_limit_count";
    temp_vec.clear();
    temp_vec.push_back((double)a_inertial_DR_limit_hit_count);
    Export_Utils::file_export_selector(temp_vec, f_p);


    // ============

    f_p.tag = "G"+m_axis_str+"_DR_limit_percent";
    temp_vec.clear();
    temp_vec.push_back((double)g_inertial_DR_limit_hit_percentage);
    Export_Utils::file_export_selector(temp_vec, f_p);


    f_p.tag = "A"+m_axis_str+"_DR_limit_percent";
    temp_vec.clear();
    temp_vec.push_back((double)a_inertial_DR_limit_hit_percentage);
    Export_Utils::file_export_selector(temp_vec, f_p);


    // ============

    f_p.tag = "G"+m_axis_str+"_DR_coverage_percent";
    temp_vec.clear();
    temp_vec.push_back((double)g_inertial_DR_coverage_percentage);
    Export_Utils::file_export_selector(temp_vec, f_p);


    f_p.tag = "A"+m_axis_str+"_DR_coverage_percent";
    temp_vec.clear();
    temp_vec.push_back((double)a_inertial_DR_coverage_percentage);
    Export_Utils::file_export_selector(temp_vec, f_p);

}

void Inertial_Axis_DR_Scorebaord::add_inertial_gyro_DR_results(int m_DR_limit_hit_count,double m_DR_limit_hit_percentage, double m_DR_coverage_percentage)
{
    g_inertial_DR_limit_hit_count       = m_DR_limit_hit_count;
    g_inertial_DR_limit_hit_percentage  = m_DR_limit_hit_percentage;
    g_inertial_DR_coverage_percentage   = m_DR_coverage_percentage;
}
void Inertial_Axis_DR_Scorebaord::add_inertial_acc_DR_results(int m_DR_limit_hit_count,double m_DR_limit_hit_percentage, double m_DR_coverage_percentage)
{
    a_inertial_DR_limit_hit_count       = m_DR_limit_hit_count;
    a_inertial_DR_limit_hit_percentage  = m_DR_limit_hit_percentage;
    a_inertial_DR_coverage_percentage   = m_DR_coverage_percentage;  
}

double Inertial_Axis_DR_Scorebaord::get_g_inertial_DR_limit_hit_count()
{
    return g_inertial_DR_limit_hit_count;
}
double Inertial_Axis_DR_Scorebaord::get_g_inertial_DR_limit_hit_percentage()
{
    return g_inertial_DR_limit_hit_percentage;
}
double Inertial_Axis_DR_Scorebaord::get_g_inertial_DR_coverage_percentage()
{
    return g_inertial_DR_coverage_percentage;
}

double Inertial_Axis_DR_Scorebaord::get_a_inertial_DR_limit_hit_count()
{
    return a_inertial_DR_limit_hit_count;
}
double Inertial_Axis_DR_Scorebaord::get_a_inertial_DR_limit_hit_percentage()
{
    return a_inertial_DR_limit_hit_percentage;
}
double Inertial_Axis_DR_Scorebaord::get_a_inertial_DR_coverage_percentage()
{
    return a_inertial_DR_coverage_percentage;
}