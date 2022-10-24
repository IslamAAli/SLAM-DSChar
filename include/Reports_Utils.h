#ifndef REPORTS_UTILS_H
#define REPORTS_UTILS_H

#include "common.h"

namespace Reports_Utils
{
    string ds_report_base_filename();
    
    string get_ds_name();

    void export_ds_brightness_reports(vector<string>& m_seq_names, 
                                        vector<int>& m_seq_sizes, 
                                        vector<vector<double>>& m_sigma_stats, 
                                        vector<vector<double>>& summary_stats, 
                                        vector<vector_stats>& m_seq_stats);

    void export_ds_contrast_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes, 
                                    vector<vector_stats>& m_weber_stats, 
                                    vector<vector_stats>& m_michelson_stats,
                                    vector<vector_stats>& m_rms_stats,
                                    vector<vector_stats>& m_CR_stats);

    void export_ds_features_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes, 
                                    vector<vector_stats>& SIFT_count_stats, 
                                    vector<vector_stats>& SIFT_dist_abs_stats, 
                                    vector<vector_stats>& SIFT_dist_avg_stats,

                                    vector<vector_stats>& FAST_count_stats, 
                                    vector<vector_stats>& FAST_dist_abs_stats, 
                                    vector<vector_stats>& FAST_dist_avg_stats,

                                    vector<vector_stats>& ORB_count_stats, 
                                    vector<vector_stats>& ORB_dist_abs_stats, 
                                    vector<vector_stats>& ORB_dist_avg_stats);

    void export_ds_single_feature_report(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
                                        vector<vector_stats>& count_stats, 
                                        vector<vector_stats>& dist_abs_stats, 
                                        vector<vector_stats>& dist_avg_stats,
                                        string feature_name);

    void export_ds_revisit_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
                                    vector<vector_stats> m_scores_stats,
                                    vector<vector_stats> m_distance_stats,
                                    vector<int> m_LC_1p0,
                                    vector<int> m_LC_0p9,
                                    vector<int> m_LC_0p5);

    void export_ds_inertial_diff_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
                                        vector<vector_stats> m_gx_stats, vector<vector_stats> m_gy_stats, vector<vector_stats> m_gz_stats,
                                        vector<vector_stats> m_ax_stats, vector<vector_stats> m_ay_stats, vector<vector_stats> m_az_stats,
                                        vector<vector_stats> m_gx_dot_stats, vector<vector_stats> m_gy_dot_stats, vector<vector_stats> m_gz_dot_stats,
                                        vector<vector_stats> m_ax_dot_stats, vector<vector_stats> m_ay_dot_stats, vector<vector_stats> m_az_dot_stats,
                                        vector<vector_stats> m_gx_2dot_stats, vector<vector_stats> m_gy_2dot_stats, vector<vector_stats> m_gz_2dot_stats,
                                        vector<vector_stats> m_ax_2dot_stats, vector<vector_stats> m_ay_2dot_stats, vector<vector_stats> m_az_2dot_stats);

    void export_ds_inertial_DR_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
                                        vector<double> DR_count_gx, vector<double> DR_count_gy, vector<double> DR_count_gz, 
                                        vector<double> DR_count_ax, vector<double> DR_count_ay, vector<double> DR_count_az, 
                                        vector<double> DR_percent_gx, vector<double> DR_percent_gy, vector<double> DR_percent_gz, 
                                        vector<double> DR_percent_ax, vector<double> DR_percent_ay, vector<double> DR_percent_az,
                                        vector<double> DR_cover_gx, vector<double> DR_cover_gy, vector<double> DR_cover_gz, 
                                        vector<double> DR_cover_ax, vector<double> DR_cover_ay, vector<double> DR_cover_az);

    void export_ds_blurring_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
                                    vector<vector_stats> m_blur_score_stats, vector<vector_stats> m_blur_percentage_stats,
                                    vector<double> total_blur, vector<double> local_blur, vector<double> global_blur);

    void export_ds_inertial_rot_only_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
                                            vector<double> rot_only_count, vector<double> rot_only_percent, vector<vector_stats> vec_stats);

    void export_ds_exposure_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
            vector<double> under_exp_count, vector<double> over_exp_count, vector<double> proper_exp_count, 
            vector<double> black_exp_count, vector<double> white_exp_count,
            vector<double> under_exp_percent, vector<double> over_exp_percent, vector<double> proper_exp_percent, 
            vector<double> black_exp_percent, vector<double> white_exp_percent,
            vector<vector_stats> mean_stats, vector<vector_stats> skewness_stats, vector<vector_stats> zone_stats);

    void export_ds_disparity_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
            vector<vector_stats> SBM_avg, vector<vector_stats> SBM_std_div, vector<vector_stats> SGBM_avg, vector<vector_stats> SGBM_std_div);
}


#endif