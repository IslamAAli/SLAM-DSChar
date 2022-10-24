#include "common.h"

// ==================================================================================
System::System(Dataset* m_ds)
{
    curr_dataset = m_ds;
    // curr_dataset->read_ds_configuration();
}
// ==================================================================================
System::~System()
{
}

// ==================================================================================
void System::initialize()
{
    print_system_intro();
}

// ==================================================================================
void System::execute(SYS_CMD m_sys_cmd)
{
    cout << "[SYSTEM] Processing Dataset: " << curr_dataset->get_ds_name() << endl <<endl;

    int sequences_count = curr_dataset->get_ds_sequence_count();
    bool command_success = false;
    // loop over sequences in dataset and execute the characterization function on them
    for(int i=0; i<sequences_count; i++)
    {
        // get the current sequence point to start the processing
        Sequence* seq = curr_dataset->get_next_sequence();
        //cout<<seq->get_seq_name()<<endl;

        cout << "[SYSTEM] * Processing Sequence" << " (" << i+1 << "/" <<sequences_count <<"): " <<  seq->get_seq_name() << endl;

        // execute selcted command
        command_success = command_issuer(m_sys_cmd, seq);

        if (command_success)
            cout << "[SYSTEM] ** Execution Successful ** " << endl;
        else
            cout << "[SYSTEM] ** Execution Problem ** " << endl;

        cout << endl;
    }

    // Export dataset Results
    if (command_success)
        curr_dataset->export_stats(m_sys_cmd);
}

// ==================================================================================
bool System::command_issuer(SYS_CMD m_sys_cmd, Sequence* m_seq)
{
    bool command_status = true;
    switch (m_sys_cmd)
    {
        // -------------------------------------------------------------------------------
        // compute the revisit freuqnecy on the selected sequence
        case CMD_RUN_REVISIT_FREQ:
            compute_revisit_freq(m_seq);
            break;
        
        // -------------------------------------------------------------------------------
        // Compute the image contrast 
        case CMD_RUN_CONTRAST:
            compute_contrast(m_seq);
            break;

        // -------------------------------------------------------------------------------
        // Compute the image brightness 
        case CMD_RUN_BRIGHTNESS:
            compute_brightness(m_seq);
            break;
        // -------------------------------------------------------------------------------
        // Compute image features' distribution ratios
        case CMD_RUN_FEATURES:
            compute_features_dist(m_seq);
            break;
        // -------------------------------------------------------------------------------
        // Compute inertial diff metrics
        case CMD_RUN_INERTIAL_DIFF:
            // check for the existence of inertial data
            if (m_seq->get_inertial_data_status())
            {
                compute_inertial_diff(m_seq);   
            }
            else
            {
                command_error(INERTIAL_DATA_ERROR);
                command_status = false;
            }

            break;
        // -------------------------------------------------------------------------------
        //Compute inertial DR metrics
        case CMD_RUN_INERTIAL_DR:
            // check for the existence of inertial data
            if (m_seq->get_inertial_data_status())
            {
                compute_inertial_DR(m_seq);
            }
            else
            {
                command_error(INERTIAL_DATA_ERROR);
                command_status = false;
            }

            break;

        case CMD_RUN_INERTIAL_ROT_ONLY:
            // check for the existence of inertial data
            if (m_seq->get_inertial_data_status())
            {
                compute_inertial_rot_only(m_seq);
            }
            else
            {
                command_error(INERTIAL_DATA_ERROR);
                command_status = false;
            }

            break;
        // -------------------------------------------------------------------------------
        // Compute image blur metrics
        case CMD_RUN_BLUR: 
            compute_blur(m_seq);
            break; 

        // -------------------------------------------------------------------------------
        // Compute Disparity metrics
        case CMD_RUN_DISPARITY:
            if (m_seq->get_stereo_data_status())
            {
                compute_disparity(m_seq);
            }
            else
            {
                command_error(STEREO_DATA_ERROR);
                command_status = false;
            }
            break;

        // -------------------------------------------------------------------------------
        // compute exposure 
        case CMD_RUN_EXPOSURE:
            compute_exposure(m_seq);
            break;

        // -------------------------------------------------------------------------------
        //run general characterization module
        case CMD_RUN_GENERAL_CHAR:
            compute_general_characteristics(m_seq);
            break;

        // -------------------------------------------------------------------------------
        // Run all metrics calculation functions
        case CMD_RUN_ALL:
            compute_revisit_freq(m_seq);
            compute_contrast(m_seq);
            compute_brightness(m_seq);
            compute_features_dist(m_seq);
            compute_inertial_diff(m_seq);
            compute_inertial_DR(m_seq);
            compute_blur(m_seq);
            compute_general_characteristics(m_seq);
            compute_exposure(m_seq);
        default:
            break;
    }

    return command_status;
}

void System::command_error(CMD_ERROR m_error)
{
    switch (m_error)
    {
        case INERTIAL_DATA_ERROR:
        {
            cout << "[SYSTEM] ** ERROR ** No Inertial Data Available. " << endl;
            break;
        }
        case STEREO_DATA_ERROR:
        {
            cout << "[SYSTEM] ** ERROR ** No Stereo Data Available. " << endl;
            break;
        }
        
        default:
            break;
    }
}
// ==================================================================================
void System::compute_revisit_freq(Sequence* m_seq)
{
    cout << "[SYSTEM] ** Calculating Revisit Frequency" << endl;
    DBow2_handler* revisit_handler = new DBow2_handler(m_seq->get_seq_img_count(), m_seq);
    DBoW2_Scoreboard* revisit_sb = new DBoW2_Scoreboard(m_seq);
    revisit_handler->loadFeatures(RIGHT_SEQ);
    revisit_handler->testDatabase(revisit_sb);

    // record the sequence results
    curr_dataset->get_ds_scoreboard()->export_and_save(revisit_sb);

    // clean up
    delete revisit_handler;
}

// ==================================================================================
void System::compute_contrast(Sequence* m_seq)
{
    cout << "[SYSTEM] ** Calculating Contrast Metrics" << endl;

    // Hide cursor and create a progress bar
    indicators::ProgressBar* bar = Visualization_Utils::create_progress_bar();

    // create a pointer to the contrast calculator to start the calculation
    Contrast_handler* contrast_calculator = new Contrast_handler();
    Contrast_Scoreboard* constrast_sb = new Contrast_Scoreboard(m_seq);

    for(int i=0; i<m_seq->get_seq_img_count(); i++)
    {
        bar->set_progress(((double)i/(double)m_seq->get_seq_img_count())*100.0);
        
        // read current image
        cv::Mat curr_img = m_seq->read_next_img(RIGHT_SEQ);
        // calculate the contrast with different methods.
        double rms_contrast         = contrast_calculator->contrast_rms(curr_img);
        double weber_contrast       = contrast_calculator->contrast_weber(curr_img);
        double michelson_contrast   = contrast_calculator->contrast_michelson(curr_img);
        double CR                   = contrast_calculator->contrast_ratio(curr_img);

        // debugging
        // cout << i << ": "<<rms_contrast << " " << weber_contrast << " " << michelson_contrast << endl;

        // update sequence score board
        constrast_sb->add_contrast_scores(rms_contrast, weber_contrast, michelson_contrast, CR);
    }

    curr_dataset->get_ds_scoreboard()->export_and_save(constrast_sb);

    // Show cursor after the progress is complete
    Visualization_Utils::close_progress_bar();
    
    // clean up 
    delete bar;
    delete contrast_calculator;
}


// ==================================================================================
void System::compute_brightness(Sequence* m_seq)
{
    cout << "[SYSTEM] ** Calculating Brightness Metrics" << endl;

    // Hide cursor and create a progress bar
    indicators::ProgressBar* bar = Visualization_Utils::create_progress_bar();

    // initiate the brightness handler object
    Brightness_handler* brightness_calculator = new Brightness_handler();
    Brightness_Scoreboard* b_sb = new Brightness_Scoreboard(m_seq);

    // loop over sequences to calculate brightness metrics
    for(int i=0; i<m_seq->get_seq_img_count(); i++)
    {
        // progress bar
        bar->set_progress(((double)i/(double)m_seq->get_seq_img_count())*100.0);

        // read current image
        cv::Mat curr_img = m_seq->read_next_img(RIGHT_SEQ);

        // get the brightness value
        double img_b = brightness_calculator->calc_avg_brightness(curr_img);

        // update the sequence scoreboard
        b_sb->add_brightness_score(img_b);

        // handle 
    }

    // calcualte brightness changing metrics
    int score_1sigma, score_2sigma, score_3sigma;
    vector<double> brightness_diff;
    vector_stats brightness_diff_stats;
    brightness_calculator->calc_brightness_changes(b_sb->get_brightness_scores(), m_seq->get_visual_timestamps_vector(RIGHT_SEQ), 
                                                    score_1sigma, score_2sigma, score_3sigma, brightness_diff, brightness_diff_stats);

    b_sb->set_brightness_scores_diff(brightness_diff); 
    b_sb->set_brightness_diff_stats(brightness_diff_stats);

    // record brightness change scroes in the sequence class
    b_sb->add_brightness_change_score((double) score_1sigma, (double) score_2sigma, (double) score_3sigma);

    // export and save results
    curr_dataset->get_ds_scoreboard()->export_and_save(b_sb);

    // Show cursor after the progress is complete
    Visualization_Utils::close_progress_bar();
    
    // clean up 
    delete bar;
    delete brightness_calculator;
}

// ==================================================================================
void System::compute_features_dist(Sequence* m_seq)
{
    cout << "[SYSTEM] ** Calculating Spatial Features Metrics" << endl;

    // Hide cursor and create a progress bar
    indicators::ProgressBar* bar = Visualization_Utils::create_progress_bar();

    Features_handler* features_calculator = new Features_handler();
    Features_Scoreboard* features_sb = new Features_Scoreboard(m_seq);
    

    for(int i=0; i< m_seq->get_seq_img_count(); i++)
    {
        // progress bar
        bar->set_progress(((double)i/(double) m_seq->get_seq_img_count())*100.0);

        // read current image
        cv::Mat curr_img = m_seq->read_next_img(RIGHT_SEQ);

        // local variables to hold the returned scores from the features calculator
        int f_count;
        double f_dist_abs, f_dist_avg;

        // =========== SIFT Features =========== 
        features_calculator->calc_features_metrics(curr_img, VF_SIFT ,f_count, f_dist_abs, f_dist_avg);
        features_sb->add_features_metric_scrore(f_count, f_dist_abs, f_dist_avg, VF_SIFT);

        // =========== FAST Features =========== 
        features_calculator->calc_features_metrics(curr_img, VF_FAST ,f_count, f_dist_abs, f_dist_avg);
        features_sb->add_features_metric_scrore(f_count, f_dist_abs, f_dist_avg, VF_FAST);
        
        // =========== ORB Features  =========== 
        features_calculator->calc_features_metrics(curr_img, VF_ORB ,f_count, f_dist_abs, f_dist_avg);
        features_sb->add_features_metric_scrore(f_count, f_dist_abs, f_dist_avg, VF_ORB);
    }

    // add the scoraboarding element to the ds scoreboard
    curr_dataset->get_ds_scoreboard()->export_and_save(features_sb);

    // Show cursor after the progress is complete
    Visualization_Utils::close_progress_bar();

    // clean up
    delete bar;
    delete features_calculator;
}

// ==================================================================================
void System::compute_blur(Sequence* m_seq)
{
    cout << "[SYSTEM] ** Calculating Blur Score and Statistics" << endl;

    // Hide cursor and create a progress bar
    indicators::ProgressBar* bar = Visualization_Utils::create_progress_bar();

    // initiate the blurring handler and its scorabord
    Blur_handler* blur_calculator = new Blur_handler();
    Blur_Scoreboard* blur_sb = new Blur_Scoreboard(m_seq);

    // loop over sequences to calculate brightness metrics
    for(int i=0; i<m_seq->get_seq_img_count(); i++)
    {
        // progress bar
        bar->set_progress(((double)i/(double)m_seq->get_seq_img_count())*100.0);

        // read current image
        cv::Mat curr_img = m_seq->read_next_img(RIGHT_SEQ);

        // get the blurring results
        double image_blur_score, blur_percentage;
        bool blur_result, global_blur, local_blur;
        vector<double> sub_score;
        vector<bool> sub_status;

        blur_calculator->calculate_segmented_blur_detection(curr_img, CONFIG::CONFIG_BLUR_BIN_SIZE, CONFIG::CONFIG_BLUR_THRESH,
                    image_blur_score, blur_percentage, blur_result, local_blur, global_blur, sub_score, sub_status);

        // push values to the scoreboard
        blur_sb->add_blur_metric_scores(image_blur_score, blur_percentage, blur_result, global_blur, local_blur);
    }

    // save the blurring scoreboard for the current sequence
    curr_dataset->get_ds_scoreboard()->export_and_save(blur_sb);

    // Show cursor after the progress is complete
    Visualization_Utils::close_progress_bar();

    // clean up
    delete bar;
    delete blur_calculator;
}
// ==================================================================================
void System::compute_disparity(Sequence* m_seq)
{
    cout << "[SYSTEM] ** Calculating Disparity Score and Statistics" << endl;

    // Hide cursor and create a progress bar
    indicators::ProgressBar* bar = Visualization_Utils::create_progress_bar();

    // initiate the blurring handler and its scorabord
    Disparity_handler* disp_calculator = new Disparity_handler();
    Disparity_Scoreboard* disp_sb = new Disparity_Scoreboard(m_seq);

    // loop over sequences to calculate brightness metrics
    for(int i=0; i<m_seq->get_seq_img_count(); i++)
    {
        // progress bar
        bar->set_progress(((double)i/(double)m_seq->get_seq_img_count())*100.0);

        // read current image
        cv::Mat curr_img_r = m_seq->read_next_img(RIGHT_SEQ);
        cv::Mat curr_img_l = m_seq->read_next_img(LEFT_SEQ);

        // check if the image pair is correct
        if (!curr_img_r.empty() && !curr_img_l.empty())
        {
            // execute the disparity calculation and record the scoreboard
            double min_disparity_val, max_disparity_val, avg_disparity_val, std_div_disparity_val;
            disp_calculator->calculate_disparity(curr_img_r, curr_img_l,
                        min_disparity_val, max_disparity_val, avg_disparity_val, std_div_disparity_val, STEREO_BM);
            disp_sb->add_results(min_disparity_val, max_disparity_val, avg_disparity_val, std_div_disparity_val, STEREO_BM);

            disp_calculator->calculate_disparity(curr_img_r, curr_img_l,
                        min_disparity_val, max_disparity_val, avg_disparity_val, std_div_disparity_val, STEREO_SGBM);
            disp_sb->add_results(min_disparity_val, max_disparity_val, avg_disparity_val, std_div_disparity_val, STEREO_SGBM);
        }
    }

    // save the blurring scoreboard for the current sequence
    curr_dataset->get_ds_scoreboard()->export_and_save(disp_sb);

    // Show cursor after the progress is complete
    Visualization_Utils::close_progress_bar();

    // clean up
    delete bar;
    delete disp_calculator;
}
// ==================================================================================
void System::compute_exposure(Sequence* m_seq)
{
    cout << "[SYSTEM] ** Calculating Exposure Score and Statistics" << endl;

    // Hide cursor and create a progress bar
    indicators::ProgressBar* bar = Visualization_Utils::create_progress_bar();

    // initiate the blurring handler and its scorabord
    Exposure_handler* exposure_calculator = new Exposure_handler();
    Exposure_Scoreboard* exposure_sb = new Exposure_Scoreboard(m_seq);

    // loop over sequences to calculate brightness metrics
    for(int i=0; i<m_seq->get_seq_img_count(); i++)
    {
        // progress bar
        bar->set_progress(((double)i/(double)m_seq->get_seq_img_count())*100.0);

        // read current image
        cv::Mat curr_img = m_seq->read_next_img(RIGHT_SEQ);

        if (curr_img.cols >0 and curr_img.rows >0)
        {
            // get the blurring results
            EXPOSURE_STATUS img_exposure_status;
            double exposure_mean, exposure_skewness, exposure_zone;

            exposure_calculator->calculate_exposure_status(curr_img, img_exposure_status, exposure_mean, exposure_skewness, exposure_zone);

            // push values to the scoreboard
            exposure_sb->add_exposure_results_entry(img_exposure_status, exposure_mean, exposure_skewness, exposure_zone);
        }
    }

    // save the blurring scoreboard for the current sequence
    curr_dataset->get_ds_scoreboard()->export_and_save(exposure_sb);

    // Show cursor after the progress is complete
    Visualization_Utils::close_progress_bar();

    // clean up
    delete bar;
    delete exposure_calculator;
}
// ==================================================================================
void System::compute_inertial_diff(Sequence* m_seq)
{
    cout << "[SYSTEM] ** Calculating Higher-Order Time Derivatives of Inertial Data" << endl;
    Inertial_Diff_handler* inertial_diff_calculator = new Inertial_Diff_handler();
    Inertial_Diff_Scoreboard* inertial_diff_sb = new Inertial_Diff_Scoreboard(m_seq);

    // calculate the 1st and second order derivatives and save them to scoreboard
    // Gyroscope
    cout << "[SYSTEM] ** Processing GX" << endl;
    compute_inertial_diff_axis(m_seq, inertial_diff_calculator, inertial_diff_sb, INERTIAL_MODE::GYRO_X);
    cout << "[SYSTEM] ** Processing GY" << endl;
    compute_inertial_diff_axis(m_seq, inertial_diff_calculator, inertial_diff_sb, INERTIAL_MODE::GYRO_Y);
    cout << "[SYSTEM] ** Processing GZ" << endl;
    compute_inertial_diff_axis(m_seq, inertial_diff_calculator, inertial_diff_sb, INERTIAL_MODE::GYRO_Z);

    // Accelerometer
    cout << "[SYSTEM] ** Processing AX" << endl;
    compute_inertial_diff_axis(m_seq, inertial_diff_calculator, inertial_diff_sb, INERTIAL_MODE::ACC_X);
    cout << "[SYSTEM] ** Processing AY" << endl;
    compute_inertial_diff_axis(m_seq, inertial_diff_calculator, inertial_diff_sb, INERTIAL_MODE::ACC_Y);
    cout << "[SYSTEM] ** Processing AZ" << endl;
    compute_inertial_diff_axis(m_seq, inertial_diff_calculator, inertial_diff_sb, INERTIAL_MODE::ACC_Z);

    // save the scoreboard to the ds scoreboard repo
    curr_dataset->get_ds_scoreboard()->export_and_save(inertial_diff_sb);

    // clean up
    delete inertial_diff_calculator;
}

void System::compute_inertial_diff_axis(Sequence* m_seq, Inertial_Diff_handler* m_calc, Inertial_Diff_Scoreboard* m_sb, INERTIAL_MODE m_mode)
{
    vector<double> diff_1st, time_1st, diff_2nd, time_2nd, data, time;
    time = m_seq->get_seq_inertial_data()->get_timestamps_vector();

    // read the required data from the inertial data database
    data = m_seq->get_seq_inertial_data()->get_inertial_data_axis(m_mode);

    // calculate higher order derivatives
    m_calc->calculate_higher_order_derivatives(data, time, diff_1st, time_1st, diff_2nd, time_2nd);

    // register to the scoreboard
    m_sb->add_inertial_diff_results(m_mode, diff_1st, diff_2nd, time_1st, time_2nd);
}
// ==================================================================================
void System::compute_inertial_DR(Sequence* m_seq)
{
    cout << "[SYSTEM] ** Calculating Saturation Condition Occurrances in Inertial Data" << endl;
    Inertial_DR_handler* inertial_dr_calculator = new Inertial_DR_handler();
    Inertial_DR_Scoreboard* inertal_DR_sb = new Inertial_DR_Scoreboard(m_seq);

    // calculate the 1st and second order derivatives and save them to scoreboard
    // Gyroscope
    cout << "[SYSTEM] ** Processing GX" << endl;
    compute_inertial_DR_axis(m_seq, inertial_dr_calculator, inertal_DR_sb, INERTIAL_MODE::GYRO_X);
    cout << "[SYSTEM] ** Processing GY" << endl;
    compute_inertial_DR_axis(m_seq, inertial_dr_calculator, inertal_DR_sb, INERTIAL_MODE::GYRO_Y);
    cout << "[SYSTEM] ** Processing GZ" << endl;
    compute_inertial_DR_axis(m_seq, inertial_dr_calculator, inertal_DR_sb, INERTIAL_MODE::GYRO_Z);

    // Accelerometer
    cout << "[SYSTEM] ** Processing AX" << endl;
    compute_inertial_DR_axis(m_seq, inertial_dr_calculator, inertal_DR_sb, INERTIAL_MODE::ACC_X);
    cout << "[SYSTEM] ** Processing AY" << endl;
    compute_inertial_DR_axis(m_seq, inertial_dr_calculator, inertal_DR_sb, INERTIAL_MODE::ACC_Y);
    cout << "[SYSTEM] ** Processing AZ" << endl;
    compute_inertial_DR_axis(m_seq, inertial_dr_calculator, inertal_DR_sb, INERTIAL_MODE::ACC_Z);

    // save and export the results
    curr_dataset->get_ds_scoreboard()->export_and_save(inertal_DR_sb);

    // clean up
    delete inertial_dr_calculator;
}

void System::compute_inertial_DR_axis(Sequence* m_seq, Inertial_DR_handler* m_calc, Inertial_DR_Scoreboard* m_sb, INERTIAL_MODE m_mode)
{
    // get the data from the inertial data repo
    vector<double> data = m_seq->get_seq_inertial_data()->get_inertial_data_axis(m_mode);

    // get the upper and lower limits based on the sensor
    double upper_limit, lower_limit;
    m_seq->get_seq_inertial_data()->get_sensor_DR_limits_axis(m_mode, upper_limit, lower_limit);

    // calculate the DR limits metrics 
    int DR_hit_count                = m_calc->dynamic_range_limits_checker(data, lower_limit, upper_limit);
    double DR_hit_percentage        = m_calc->dynamic_range_limits_hitting_percentage(data.size());
    double DR_coverage_percentage   = m_calc->dynamic_range_coverage_percentage(data, lower_limit, upper_limit);


    // record the information in the scoreboard
    m_sb->add_inertial_DR_results(m_mode, DR_hit_count, DR_hit_percentage, DR_coverage_percentage);
}

// ==================================================================================
void System::compute_general_characteristics(Sequence* m_seq)
{
    cout << "[SYSTEM] ** Calculating General Dataset Characteristics" << endl;
    
    // create an object of the general characterization class
    General_Metrics_handler* gmh = new General_Metrics_handler();
    General_Char_Scoreboard* gc_sb = new General_Char_Scoreboard(m_seq);

    vector<Sensor_Data*> vec_sensors = m_seq->get_sensor_data_ptr();

    for(unsigned int i=0; i< vec_sensors.size(); i++)
    {
        vector<double> sensor_timestamp = vec_sensors[i]->get_timestamps_vector();

        // total samples
        vec_sensors[i]->set_samples_count(sensor_timestamp.size());

        // total duration
        vec_sensors[i]->set_duration(gmh->calculate_seq_total_duration(sensor_timestamp));

        // per sample Sampling Rate
        vec_sensors[i]->set_persample_sampling_rate(gmh->calculate_sampling_rate(sensor_timestamp));
    }
    
    // sensors mismatching detection between visual and inertial data
    vector<double> mismatch_vals;
    gmh->calculate_timestamp_mismatch(
        m_seq->get_inertial_timestamps_vector(),
        m_seq->get_visual_timestamps_vector(IMG_STEREO_SEQ::RIGHT_SEQ),
        mismatch_vals
    );
    gc_sb->set_timestamp_mismatch_vec(mismatch_vals);

    // export and save the results
    curr_dataset->get_ds_scoreboard()->export_and_save(gc_sb);

    // clean-up
    delete gmh;
}
// ==================================================================================
void System::compute_inertial_rot_only(Sequence* m_seq)
{
    cout << "[SYSTEM] ** Calculating Rotation-Only Detection Metrics" << endl;
    Rotation_only_handler* rot_only_calculator = new Rotation_only_handler();
    Rotation_only_Scoreboard* rot_only_sb = new Rotation_only_Scoreboard(m_seq);

    vector<double> f_mag = rot_only_calculator->calculate_acc_magnitude(m_seq->get_seq_inertial_data()->get_acc_x(), 
                                                                        m_seq->get_seq_inertial_data()->get_acc_x(),
                                                                        m_seq->get_seq_inertial_data()->get_acc_z());
    
    int rot_only_count = rot_only_calculator->count_rotation_only_motion(f_mag, CONFIG::CONFIG_GRAVITY_VAL, CONFIG::CONFIG_GRAVITY_ERR_PERCENT);

    // record the result to the scoreboard
    rot_only_sb->set_f_mag(f_mag);
    rot_only_sb->set_rotation_only_count(rot_only_count);
    rot_only_sb->set_rotation_only_percentage(((double)rot_only_count / (double)m_seq->get_seq_inertial_data()->get_acc_x().size())*100);

    // record in the dataset scoreboard
    curr_dataset->get_ds_scoreboard()->export_and_save(rot_only_sb);
}
// ==================================================================================
void System::print_system_intro()
{
    cout << "\n\n";
    cout << "------------------------------------------------------------------" << endl;
    cout << "EVAL-DS Framework Initialized " << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "\n\n";
}