#include "common.h"

Dataset_Scoreboard::Dataset_Scoreboard(/* args */)
{
}

Dataset_Scoreboard::~Dataset_Scoreboard()
{
}

void Dataset_Scoreboard::export_and_save(Blur_Scoreboard* m_b_sb)
{
    m_b_sb->export_results();
    blur_sb_vec.push_back(m_b_sb);
}

void Dataset_Scoreboard::export_and_save(Brightness_Scoreboard* m_b_sb)
{
    m_b_sb->export_results();
    brightness_sb_vec.push_back(m_b_sb);
}

void Dataset_Scoreboard::export_and_save(Contrast_Scoreboard* m_c_sb)
{
    m_c_sb->export_results();
    contrast_sb_vec.push_back(m_c_sb);
}

void Dataset_Scoreboard::export_and_save(DBoW2_Scoreboard* m_rv_sb)
{
    m_rv_sb->export_results();
    revisit_sb_vec.push_back(m_rv_sb);
}

void Dataset_Scoreboard::export_and_save(Features_Scoreboard* m_f_sb)
{
    m_f_sb->export_results();
    features_sb_vec.push_back(m_f_sb);
}


void Dataset_Scoreboard::export_and_save(Inertial_Diff_Scoreboard* i_diff_sb)
{
    i_diff_sb->export_results();
    inertial_diff_sb_vec.push_back(i_diff_sb);
}
void Dataset_Scoreboard::export_and_save(Inertial_DR_Scoreboard* i_dr_sb)
{
    i_dr_sb->export_results();
    inertial_dr_sb_vec.push_back(i_dr_sb);
}

void Dataset_Scoreboard::export_and_save(General_Char_Scoreboard* m_gc_sb)
{
    m_gc_sb->export_results();
    general_char_sb_vec.push_back(m_gc_sb);
}

void Dataset_Scoreboard::export_and_save(Rotation_only_Scoreboard* m_rot_only_sb)
{
    m_rot_only_sb->export_results();
    rot_only_sb_vec.push_back(m_rot_only_sb);
}

void Dataset_Scoreboard::export_and_save(Exposure_Scoreboard* m_exposure_sb)
{
    m_exposure_sb->export_results();
    exposure_sb_vec.push_back(m_exposure_sb);
}

void Dataset_Scoreboard::export_and_save(Disparity_Scoreboard* m_disp_sb)
{
    m_disp_sb->export_results();
    disparity_sb_vec.push_back(m_disp_sb);
}