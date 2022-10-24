#include "common.h"


// ===================================================================
// Constructors
Dataset::Dataset(string m_ds_name, string m_ds_config_file_path)
{
    ds_name                 = m_ds_name;
    ds_config_file_path     = m_ds_config_file_path;
    ds_base_img_path        = "";
    
    CONFIG::DATASET_NAME    = m_ds_name+"/";
    ds_scoreboard           = new Dataset_Scoreboard();
    
    read_ds_configuration();
}

void Dataset::reset()
{
    curr_seq = 0;
    for(unsigned int i=0; i<ds_sequence.size(); i++)
    {
        ds_sequence[i].reset();
    }
}

// ===================================================================
// Destructors
Dataset::~Dataset()
{

}

// ===================================================================
// Set and get functions 
int Dataset::get_ds_sequence_count()
{
    return ds_sequence_count;
}

string Dataset::get_ds_name()
{
    return ds_name;
}

Dataset_Scoreboard* Dataset::get_ds_scoreboard()
{
    return ds_scoreboard;
}

// ===================================================================
// Read configuration file and construct the sequences objects vector
bool Dataset::read_ds_configuration()
{
    ifstream in_file(this->ds_config_file_path);
    if (in_file.is_open())
    {
        // reading configurations
        read_ds_config_map(in_file);
        
        // reading the base images path
        ds_base_img_path = ds_config[DS_CONFIG_PARAM::DS_PARAM_BASE_PATH];

        // reading the number of sequences
        ds_sequence_count = stoi(ds_config[DS_CONFIG_PARAM::DS_PARAM_SEQ_COUNT]);

        // for each sequence read its name and the paths to the the image folder inside.
        string in_file_line;
        getline(in_file, in_file_line);
        for(int i=0; i<ds_sequence_count; i++)
        {
            // read the line that contains the sequence name and folder names for right and left images
            getline(in_file, in_file_line );
            vector<string> content = Utils::explode(in_file_line, ' ');
            
            // create a sequence and adjust its parameters accordingly.
            Sequence ds_seq(ds_name);
            ds_seq.set_stereo_data_status(false);
            ds_seq.set_inertial_data_status(false);
            ds_seq.set_seq_name(content[0]);
            ds_seq.get_seq_inertial_data()->set_gyro_DR_pos(stod(ds_config[DS_CONFIG_PARAM::DS_PARAM_GYRO_DR_POS]));
            ds_seq.get_seq_inertial_data()->set_gyro_DR_neg(-1.0*stod(ds_config[DS_CONFIG_PARAM::DS_PARAM_GYRO_DR_NEG]));
            ds_seq.get_seq_inertial_data()->set_acc_DR_pos(stod(ds_config[DS_CONFIG_PARAM::DS_PARAM_ACC_DR_POS]));
            ds_seq.get_seq_inertial_data()->set_acc_DR_neg(-1.0*stod(ds_config[DS_CONFIG_PARAM::DS_PARAM_ACC_DR_NEG]));

            // based on the dataset conditions, read the input files accordingly 
            if (ds_config[DS_CONFIG_PARAM::DS_PARAM_STEREO] == "y")
            {
                // stereo Vision
                ds_seq.set_stereo_data_status(true);
                ds_seq.register_stereo_l_data();
                ds_seq.register_stereo_r_data();
                if(content.size()<5)
                {
                    cout << "[ERROR] Insufficient input data for stereo vision." << endl;
                }
                else
                {
                    // read the stereo vision data
                    ds_seq.get_r_imgs()->set_img_path(ds_base_img_path+content[0]+"/"+content[1]);
                    ds_seq.get_l_imgs()->set_img_path(ds_base_img_path+content[0]+"/"+content[2]);

                    ds_seq.get_r_imgs()->set_timestamps_path(ds_base_img_path+content[0]+"/"+content[3]);
                    ds_seq.get_l_imgs()->set_timestamps_path(ds_base_img_path+content[0]+"/"+content[4]);
                    // check for the imu data files
                    if(ds_config[DS_CONFIG_PARAM::DS_PARAM_IMU] == "y")
                    {
                        if (content.size() <7)
                        {
                            cout << "[ERROR] Insufficient input data for IMU." << endl;
                        }
                        else
                        {
                            // read the inertial data 
                            ds_seq.set_inertial_data_status(true);
                            ds_seq.register_inertial_data();
                            ds_seq.get_seq_inertial_data()->set_inertial_data_path(ds_base_img_path+content[0]+"/"+content[5]);
                            ds_seq.get_seq_inertial_data()->set_timestamps_path(ds_base_img_path+content[0]+"/"+content[6]);
                        }
                    }
                }
            }
            else
            {
                // Monocular Vision
                ds_seq.set_stereo_data_status(false);
                if (content.size() <3)
                {
                    cout << "[ERROR] Insufficient input data for monocular vision." << endl;
                }
                else
                {
                    // read the monocular vision data 
                    ds_seq.get_r_imgs()->set_img_path(ds_base_img_path+content[0]+"/"+content[1]);
                    ds_seq.get_l_imgs()->set_img_path(NULL);

                    ds_seq.get_r_imgs()->set_timestamps_path(ds_base_img_path+content[0]+"/"+content[2]);
                    ds_seq.get_l_imgs()->set_timestamps_path(NULL);

                    // check for the imu data files
                    if(ds_config[DS_CONFIG_PARAM::DS_PARAM_IMU] == "y") 
                    {
                        if (content.size() <5)
                        {
                            cout << "[ERROR] Insufficient input data for IMU." << endl;
                        }
                        else
                        {
                            // read the inertial data 
                            ds_seq.set_inertial_data_status(true);
                            ds_seq.register_inertial_data();
                            ds_seq.get_seq_inertial_data()->set_inertial_data_path(ds_base_img_path+content[0]+"/"+content[3]);
                            ds_seq.get_seq_inertial_data()->set_timestamps_path(ds_base_img_path+content[0]+"/"+content[4]);
                        }
                    }
                }
            }

            // reading the image list for the current sequence.
            ds_seq.read_img_list();

            // read timestamps vectors
            ds_seq.read_timestamps();

            // read inertial data
            ds_seq.get_seq_inertial_data()->read_inertial_data();

            // read inertial timestamps vector
            ds_seq.get_seq_inertial_data()->read_timestamps();

            // adding the sequence to the sequence vector
            ds_sequence.push_back(ds_seq);
        }
    }
    else
    {
        cout << "[ERROR] Couldn't Open Config File !"<<endl;
        return false; 
    }
    in_file.close();
    return true;
}

// ===================================================================
// Read Configuration from file
// ===================================================================
void Dataset::read_ds_config_map(ifstream & m_file)
{
    cout << "-> Dataset Properties :" << endl;
    cout << "------------------------" << endl;

    string param = "";
    string param_val = "";
    bool config_reading = true;
    while(config_reading)
    {
        m_file >> param;
        m_file >> param_val;

        if (param == "-" && param_val == "-")
        {
            config_reading = false;
        }
        else
        {
            // printing the configuration value
            cout << std::setw(25) << std::right << std::setfill(' ') << param << ": ";
            cout << param_val << endl;

            // adding the configuration read to the map
            ds_config.insert(std::pair<string, string>(param, param_val));
        }
    }

    cout << "\n";
}

// ===================================================================
// get next sequence for processing
// ===================================================================
Sequence* Dataset::get_next_sequence()
{
    return &ds_sequence[curr_seq++];
}

// ===================================================================
// Export statistics for plotting
// ===================================================================
void Dataset::export_stats(SYS_CMD m_sys_cmd)
{
    vector<string> seq_names;
    vector<int> seq_sizes;

    for(unsigned int i=0; i<ds_sequence.size(); i++)
    {
        seq_names.push_back(ds_sequence[i].get_seq_name());
        seq_sizes.push_back(ds_sequence[i].get_seq_img_count());
    }

    switch (m_sys_cmd)
    {
        case CMD_RUN_BRIGHTNESS:
        {
            
            vector<vector<double>> sigma_stats;
            vector<vector<double>> summary_stats;
            vector<vector_stats> seq_stats;

            for(unsigned int i=0; i<ds_sequence.size(); i++)
            {
                sigma_stats.push_back(ds_scoreboard->brightness_sb_vec[i]->get_brighness_sigma_scores());
                seq_stats.push_back(ds_scoreboard->brightness_sb_vec[i]->get_brightness_stats());
            }
            Reports_Utils::export_ds_brightness_reports(seq_names, seq_sizes, sigma_stats, summary_stats, seq_stats);
            break;
        }
            
        case CMD_RUN_CONTRAST:
        {
            vector<vector_stats> rms_stats;
            vector<vector_stats> weber_stats;
            vector<vector_stats> michelson_stats;
            vector<vector_stats> CR_stats;
            for(unsigned int i=0; i<ds_sequence.size(); i++)
            {
                rms_stats.push_back(ds_scoreboard->contrast_sb_vec[i]->get_rms_stats());
                weber_stats.push_back(ds_scoreboard->contrast_sb_vec[i]->get_weber_stats());
                michelson_stats.push_back(ds_scoreboard->contrast_sb_vec[i]->get_michelson_stats());
                CR_stats.push_back(ds_scoreboard->contrast_sb_vec[i]->get_CR_stats());
            }
            
            Reports_Utils::export_ds_contrast_reports(seq_names, seq_sizes, weber_stats, michelson_stats, rms_stats, CR_stats);
            break;
        }

        case CMD_RUN_FEATURES:
        {
            vector<vector_stats> SIFT_count_stats;
            vector<vector_stats> SIFT_dist_abs_stats;
            vector<vector_stats> SIFT_dist_avg_stats;

            vector<vector_stats> FAST_count_stats;
            vector<vector_stats> FAST_dist_abs_stats;
            vector<vector_stats> FAST_dist_avg_stats;

            vector<vector_stats> ORB_count_stats;
            vector<vector_stats> ORB_dist_abs_stats;
            vector<vector_stats> ORB_dist_avg_stats;

            for(unsigned int i=0; i<ds_sequence.size(); i++)
            {
                SIFT_count_stats.push_back(ds_scoreboard->features_sb_vec[i]->get_score_count_stats(VF_SIFT));
                SIFT_dist_abs_stats.push_back(ds_scoreboard->features_sb_vec[i]->get_Fdist_abs_stats(VF_SIFT));
                SIFT_dist_avg_stats.push_back(ds_scoreboard->features_sb_vec[i]->get_Fdist_avg_stats(VF_SIFT));

                FAST_count_stats.push_back(ds_scoreboard->features_sb_vec[i]->get_score_count_stats(VF_FAST));
                FAST_dist_abs_stats.push_back(ds_scoreboard->features_sb_vec[i]->get_Fdist_abs_stats(VF_FAST));
                FAST_dist_avg_stats.push_back(ds_scoreboard->features_sb_vec[i]->get_Fdist_avg_stats(VF_FAST));

                ORB_count_stats.push_back(ds_scoreboard->features_sb_vec[i]->get_score_count_stats(VF_ORB));
                ORB_dist_abs_stats.push_back(ds_scoreboard->features_sb_vec[i]->get_Fdist_abs_stats(VF_ORB));
                ORB_dist_avg_stats.push_back(ds_scoreboard->features_sb_vec[i]->get_Fdist_avg_stats(VF_ORB));
            }

            Reports_Utils::export_ds_features_reports(seq_names, seq_sizes, 
                                                        SIFT_count_stats, SIFT_dist_abs_stats, SIFT_dist_avg_stats,
                                                        FAST_count_stats, FAST_dist_abs_stats, FAST_dist_avg_stats,
                                                        ORB_count_stats, ORB_dist_abs_stats, ORB_dist_avg_stats);

            break;
        }

        case CMD_RUN_REVISIT_FREQ:
        {
            vector<vector_stats> scores_stats;
            vector<vector_stats> distance_stats;
            vector<int> LC_1p0;
            vector<int> LC_0p9;
            vector<int> LC_0p5;

            for(unsigned int i=0; i<ds_sequence.size(); i++)
            {
                scores_stats.push_back(ds_scoreboard->revisit_sb_vec[i]->get_score_stats());
                distance_stats.push_back(ds_scoreboard->revisit_sb_vec[i]->get_distance_stats());
                LC_1p0.push_back(ds_scoreboard->revisit_sb_vec[i]->get_revisit_score_1p0());
                LC_0p9.push_back(ds_scoreboard->revisit_sb_vec[i]->get_revisit_score_0p9());
                LC_0p5.push_back(ds_scoreboard->revisit_sb_vec[i]->get_revisit_score_0p5());
            }

            Reports_Utils::export_ds_revisit_reports(seq_names, seq_sizes, scores_stats, distance_stats, LC_1p0, LC_0p9, LC_0p5);

            break;
        }

        case CMD_RUN_INERTIAL_DIFF:
        {
            vector<vector_stats> gx, gy, gz, ax, ay, az;
            vector<vector_stats> gx_dot, gy_dot, gz_dot, ax_dot, ay_dot, az_dot;
            vector<vector_stats> gx_2dot, gy_2dot, gz_2dot, ax_2dot, ay_2dot, az_2dot;

            for(unsigned int i=0; i<ds_sequence.size(); i++)
            {
                

                gx.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_x_axis()->get_g_stats());
                gy.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_y_axis()->get_g_stats());
                gz.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_z_axis()->get_g_stats());
                ax.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_x_axis()->get_a_stats());
                ay.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_y_axis()->get_a_stats());
                az.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_z_axis()->get_a_stats());

                gx_dot.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_x_axis()->get_g_1st_diff_stats());
                gy_dot.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_y_axis()->get_g_1st_diff_stats());
                gz_dot.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_z_axis()->get_g_1st_diff_stats());
                ax_dot.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_x_axis()->get_a_1st_diff_stats());
                ay_dot.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_y_axis()->get_a_1st_diff_stats());
                az_dot.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_z_axis()->get_a_1st_diff_stats());

                gx_2dot.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_x_axis()->get_g_2nd_diff_stats());
                gy_2dot.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_y_axis()->get_g_2nd_diff_stats());
                gz_2dot.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_z_axis()->get_g_2nd_diff_stats());
                ax_2dot.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_x_axis()->get_a_2nd_diff_stats());
                ay_2dot.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_y_axis()->get_a_2nd_diff_stats());
                az_2dot.push_back(ds_scoreboard->inertial_diff_sb_vec[i]->get_z_axis()->get_a_2nd_diff_stats());
            }

            Reports_Utils::export_ds_inertial_diff_reports(seq_names, seq_sizes, gx, gy, gz, ax, ay, az, 
                                                            gx_dot, gy_dot, gz_dot, ax_dot, ay_dot, az_dot,
                                                            gx_2dot, gy_2dot, gz_2dot, ax_2dot, ay_2dot, az_2dot);
            break;
        }
        case CMD_RUN_INERTIAL_DR:
        {
            vector<double> DR_count_gx, DR_count_gy, DR_count_gz, DR_count_ax, DR_count_ay, DR_count_az;
            vector<double> DR_percent_gx, DR_percent_gy, DR_percent_gz, DR_percent_ax, DR_percent_ay, DR_percent_az;
            vector<double> DR_coverage_gx, DR_coverage_gy, DR_coverage_gz, DR_coverage_ax, DR_coverage_ay, DR_coverage_az;

            for(unsigned int i=0; i< ds_sequence.size(); i++)
            {
                
                DR_count_gx.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_x_axis()->get_g_inertial_DR_limit_hit_count());
                DR_count_gy.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_y_axis()->get_g_inertial_DR_limit_hit_count());
                DR_count_gz.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_z_axis()->get_g_inertial_DR_limit_hit_count());
                DR_count_ax.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_x_axis()->get_a_inertial_DR_limit_hit_count());
                DR_count_ay.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_y_axis()->get_a_inertial_DR_limit_hit_count());
                DR_count_az.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_z_axis()->get_a_inertial_DR_limit_hit_count());

                DR_percent_gx.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_x_axis()->get_g_inertial_DR_limit_hit_percentage());
                DR_percent_gy.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_y_axis()->get_g_inertial_DR_limit_hit_percentage());
                DR_percent_gz.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_z_axis()->get_g_inertial_DR_limit_hit_percentage());
                DR_percent_ax.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_x_axis()->get_a_inertial_DR_limit_hit_percentage());
                DR_percent_ay.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_y_axis()->get_a_inertial_DR_limit_hit_percentage());
                DR_percent_az.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_z_axis()->get_a_inertial_DR_limit_hit_percentage());

                DR_coverage_gx.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_x_axis()->get_g_inertial_DR_coverage_percentage());
                DR_coverage_gy.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_y_axis()->get_g_inertial_DR_coverage_percentage());
                DR_coverage_gz.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_z_axis()->get_g_inertial_DR_coverage_percentage());
                DR_coverage_ax.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_x_axis()->get_a_inertial_DR_coverage_percentage());
                DR_coverage_ay.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_y_axis()->get_a_inertial_DR_coverage_percentage());
                DR_coverage_az.push_back(ds_scoreboard->inertial_dr_sb_vec[i]->get_z_axis()->get_a_inertial_DR_coverage_percentage());
            }

            Reports_Utils::export_ds_inertial_DR_reports(seq_names, seq_sizes, 
                                    DR_count_gx, DR_count_gy, DR_count_gz, DR_count_ax, DR_count_ay, DR_count_az,
                                    DR_percent_gx, DR_percent_gy, DR_percent_gz, DR_percent_ax, DR_percent_ay, DR_percent_az, 
                                    DR_coverage_gx, DR_coverage_gy, DR_coverage_gz, DR_coverage_ax, DR_coverage_ay, DR_coverage_az);
            break;
        }

        case CMD_RUN_BLUR:
        {
            vector<double> total_blur, local_blur, global_blur;
            vector<vector_stats> blur_score, blur_percentage;

            for(unsigned int i=0; i< ds_sequence.size(); i++)
            {
                total_blur.push_back(ds_scoreboard->blur_sb_vec[i]->get_blurred_img_percent());
                local_blur.push_back(ds_scoreboard->blur_sb_vec[i]->get_local_blur_percent());
                global_blur.push_back(ds_scoreboard->blur_sb_vec[i]->get_global_blur_percent());
                blur_score.push_back(ds_scoreboard->blur_sb_vec[i]->get_blur_score_stats());
                blur_percentage.push_back(ds_scoreboard->blur_sb_vec[i]->get_blur_percent_stats());
            }

            Reports_Utils::export_ds_blurring_reports(seq_names, seq_sizes, blur_score, blur_percentage, total_blur, local_blur, global_blur);

            break;
        }

        case CMD_RUN_INERTIAL_ROT_ONLY:
        {
            vector<double> rot_only_count, rot_only_percent;
            vector<vector_stats> f_mag_stats;

            for(unsigned int i=0; i<ds_sequence.size(); i++)
            {
                rot_only_count.push_back(ds_scoreboard->rot_only_sb_vec[i]->get_rotation_only_count());
                rot_only_percent.push_back(ds_scoreboard->rot_only_sb_vec[i]->get_rotation_only_percentage());
                f_mag_stats.push_back(ds_scoreboard->rot_only_sb_vec[i]->get_f_mag_stats());
            }

            Reports_Utils::export_ds_inertial_rot_only_reports(seq_names, seq_sizes, rot_only_count, rot_only_percent, f_mag_stats);

            break;
        }

        case CMD_RUN_EXPOSURE:
        {
            vector<double> under_exp_count, over_exp_count, proper_exp_count, black_exp_count, white_exp_count;
            vector<double> under_exp_percent, over_exp_percent, proper_exp_percent, black_exp_percent, white_exp_percent;
            vector<vector_stats> mean_stats, skewness_stats, zone_stats;

            for(unsigned int i=0; i<ds_sequence.size(); i ++)
            {
                under_exp_count.push_back(ds_scoreboard->exposure_sb_vec[i]->get_under_exposure_count());
                over_exp_count.push_back(ds_scoreboard->exposure_sb_vec[i]->get_over_exposure_count());
                proper_exp_count.push_back(ds_scoreboard->exposure_sb_vec[i]->get_proper_exposure_count());
                black_exp_count.push_back(ds_scoreboard->exposure_sb_vec[i]->get_black_exposure_count());
                white_exp_count.push_back(ds_scoreboard->exposure_sb_vec[i]->get_white_exposure_count());

                under_exp_percent.push_back(ds_scoreboard->exposure_sb_vec[i]->get_under_exposure_percent());
                over_exp_percent.push_back(ds_scoreboard->exposure_sb_vec[i]->get_over_exposure_percent());
                proper_exp_percent.push_back(ds_scoreboard->exposure_sb_vec[i]->get_proper_exposure_percent());
                black_exp_percent.push_back(ds_scoreboard->exposure_sb_vec[i]->get_black_exposure_percent());
                white_exp_percent.push_back(ds_scoreboard->exposure_sb_vec[i]->get_white_exposure_percent());

                mean_stats.push_back(ds_scoreboard->exposure_sb_vec[i]->get_mean_vec_stats());
                skewness_stats.push_back(ds_scoreboard->exposure_sb_vec[i]->get_skewness_vec_stats());
                zone_stats.push_back(ds_scoreboard->exposure_sb_vec[i]->get_zone_vec_stats());
            }

            // call the report utils function to export the report data
            Reports_Utils::export_ds_exposure_reports(seq_names, seq_sizes, 
                            under_exp_count, over_exp_count, proper_exp_count, black_exp_count, white_exp_count,
                            under_exp_percent, over_exp_percent, proper_exp_percent, black_exp_percent, white_exp_percent,
                            mean_stats, skewness_stats, zone_stats);

            break; 
        }

        case CMD_RUN_DISPARITY:
        {
            // definition of aggregation tables
            vector<vector_stats> SBM_avg, SBM_std_div, SGBM_avg, SGBM_std_div;

            // loop over sequences to aggregate values
            for(unsigned int i=0; i<ds_sequence.size(); i ++)
            {
                // aggregation of vectors for exporting
                SBM_avg.push_back(ds_scoreboard->disparity_sb_vec[i]->get_avg_disp_vec_stats(STEREO_BM));
                SBM_std_div.push_back(ds_scoreboard->disparity_sb_vec[i]->get_std_div_disp_vec_stats(STEREO_BM));

                SGBM_avg.push_back(ds_scoreboard->disparity_sb_vec[i]->get_avg_disp_vec_stats(STEREO_SGBM));
                SGBM_std_div.push_back(ds_scoreboard->disparity_sb_vec[i]->get_std_div_disp_vec_stats(STEREO_SGBM));
            }

            // export the reports 
            Reports_Utils::export_ds_disparity_reports(seq_names, seq_sizes, SBM_avg, SBM_std_div, SGBM_avg, SGBM_std_div);

            break;
        }

        default:
            break;
    }
}