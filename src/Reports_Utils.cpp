#include "common.h"

namespace Reports_Utils
{
    string ds_report_base_filename()
    {
        return CONFIG::CONFIG_OUT_PATH_DATASET_REPORTS+CONFIG::DATASET_NAME;
    }

    // -----------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------

    string get_ds_name()
    {
        return CONFIG::DATASET_NAME.substr(0, CONFIG::DATASET_NAME.size()-1);
    }

    // -----------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------

    void export_boxplt_data_file(string m_file_path, string m_tag, vector<string>& m_seq_names)
    {
        ofstream out_file(m_file_path);
        out_file  << "filenames = ["  << endl;
        for(unsigned int i=0; i<m_seq_names.size();i++)
        {
            if(i != 0 )
            {
                out_file << ",";
            }

            out_file << "'" << CONFIG::CONFIG_OUT_PATH_REPORTS 
                            << CONFIG::DATASET_NAME 
                            << m_tag 
                            << get_ds_name() << "_"
                            << m_seq_names[i] 
                            << ".txt'" << endl;
        }
        out_file  << "]"  << endl;
        out_file.close();
    }

    // -----------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------

    void export_boxplt_label_file(string m_file_path, vector<string>& m_seq_names)
    {
        ofstream out_file(m_file_path);
        out_file  << "dlabels = ["  << endl;
        for(unsigned int i=0; i<m_seq_names.size();i++)
        {
            if(i != 0 )
            {
                out_file << ",";
            }
            out_file << "'" << m_seq_names[i] << "'" << endl;
        }
        out_file  << "]"  << endl;
        out_file.close();
    }

    // -----------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------

    void export_ds_brightness_reports(vector<string>& m_seq_names,
                                        vector<int>& m_seq_sizes,
                                        vector<vector<double>>& m_sigma_stats,
                                        vector<vector<double>>& summary_stats,
                                        vector<vector_stats>& m_seq_stats)
    {   
        // handle unused parameters
        (void)summary_stats;

        // Export file paths
        string summary_file_path    = ds_report_base_filename()+"[BRIGHTNESS]"+"summary.txt";
        string boxpltF_file_path    = ds_report_base_filename()+"[BRIGHTNESS]"+"boxplot_files_data.txt";
        string boxpltL_file_path    = ds_report_base_filename()+"[BRIGHTNESS]"+"boxplot_labels_data.txt";
        string barchart_file_path   = ds_report_base_filename()+"[BRIGHTNESS]"+"barchart_data.dat";

        // export boxplot files
        export_boxplt_data_file(boxpltF_file_path, "[BRIGHTNESS]", m_seq_names);
        export_boxplt_label_file(boxpltL_file_path, m_seq_names);
        
        // open output files for export
        ofstream summary_file(summary_file_path);
        ofstream barchart_file(barchart_file_path);
        
        // file headers
        barchart_file           << "name,count,1sigma,1sigmaP,2sigma,2sigmaP,3sigma,3sigmaP" << endl;

        // loop over sequences and extract needed data 
        for(unsigned int i=0; i<m_seq_names.size(); i++)
        {   
            // summary table data
            summary_file << m_seq_names[i] << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_seq_stats[i].arith_mean << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_seq_stats[i].std_dev << " & ";
            summary_file << std::fixed << std::setprecision(0) << m_sigma_stats[i][0] << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_sigma_stats[i][1] << " & ";
            summary_file << std::fixed << std::setprecision(0) << m_sigma_stats[i][2] << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_sigma_stats[i][3] << " & ";
            summary_file << std::fixed << std::setprecision(0) << m_sigma_stats[i][4] << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_sigma_stats[i][5] << " \\\\ " <<endl;

            // barchart data
            barchart_file << m_seq_names[i]      << ",";
            barchart_file << m_seq_sizes[i]      << ",";
            barchart_file << m_sigma_stats[i][0] << "," << m_sigma_stats[i][1] << "," ;
            barchart_file << m_sigma_stats[i][2] << "," << m_sigma_stats[i][3] << "," ;
            barchart_file << m_sigma_stats[i][4] << "," << m_sigma_stats[i][5] << endl ;
        }

        // close opened files
        summary_file.close();
        barchart_file.close();
    }



    void export_ds_contrast_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes, 
                                    vector<vector_stats>& m_weber_stats, 
                                    vector<vector_stats>& m_michelson_stats,
                                    vector<vector_stats>& m_rms_stats,
                                    vector<vector_stats>& m_CR_stats)
    {
        // handle unused variables
        (void)m_seq_sizes;
        // set the paths to output files
        string summary_file_path    = ds_report_base_filename()+"[CONTRAST]"+"summary.txt";
        string boxpltF_file_path_W  = ds_report_base_filename()+"[CONTRAST]"+"boxplot_files_data_weber.txt";
        string boxpltF_file_path_M  = ds_report_base_filename()+"[CONTRAST]"+"boxplot_files_data_michelson.txt";
        string boxpltF_file_path_R  = ds_report_base_filename()+"[CONTRAST]"+"boxplot_files_data_rms.txt";
        string boxpltF_file_path_C  = ds_report_base_filename()+"[CONTRAST]"+"boxplot_files_data_CR.txt";
        string boxpltL_file_path    = ds_report_base_filename()+"[CONTRAST]"+"boxplot_labels_data.txt";

        // export boxplot files
        export_boxplt_label_file(boxpltL_file_path, m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_W, "[CONTRAST_WEBER]" , m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_M, "[CONTRAST_MICHELSON]" , m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_R, "[CONTRAST_RMS]" , m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_C, "[CONTRAST_CR]" , m_seq_names);

        // open output files for export
        ofstream summary_file(summary_file_path);

        // loop over sequences to add information to reports
        for(unsigned int i=0; i< m_seq_names.size(); i++)
        {
            // export summary table data
            summary_file << m_seq_names[i] << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_CR_stats[i].arith_mean << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_CR_stats[i].std_dev << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_weber_stats[i].arith_mean << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_weber_stats[i].std_dev << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_michelson_stats[i].arith_mean << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_michelson_stats[i].std_dev << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_rms_stats[i].arith_mean << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_rms_stats[i].std_dev << " \\\\ " <<endl;
        }

        // close opened files
        summary_file.close();
    }


    void export_ds_features_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes, 
                                    vector<vector_stats>& SIFT_count_stats, 
                                    vector<vector_stats>& SIFT_dist_abs_stats, 
                                    vector<vector_stats>& SIFT_dist_avg_stats,

                                    vector<vector_stats>& FAST_count_stats, 
                                    vector<vector_stats>& FAST_dist_abs_stats, 
                                    vector<vector_stats>& FAST_dist_avg_stats,

                                    vector<vector_stats>& ORB_count_stats, 
                                    vector<vector_stats>& ORB_dist_abs_stats, 
                                    vector<vector_stats>& ORB_dist_avg_stats)
    {
        export_ds_single_feature_report(m_seq_names, m_seq_sizes, SIFT_count_stats, SIFT_dist_abs_stats, SIFT_dist_avg_stats, "SIFT");
        export_ds_single_feature_report(m_seq_names, m_seq_sizes, FAST_count_stats, FAST_dist_abs_stats, FAST_dist_avg_stats, "FAST");
        export_ds_single_feature_report(m_seq_names, m_seq_sizes, ORB_count_stats, ORB_dist_abs_stats, ORB_dist_avg_stats, "ORB");
    }

    void export_ds_single_feature_report(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
                                        vector<vector_stats>& count_stats, 
                                        vector<vector_stats>& dist_abs_stats, 
                                        vector<vector_stats>& dist_avg_stats,
                                        string feature_name)
    {
        // handle unused variables
        (void)m_seq_sizes;
        // set the paths to output files
        string summary_file_path    = ds_report_base_filename()+"[FEATURES_"+feature_name+"]"+"summary.txt";
        string boxpltF_file_path_C  = ds_report_base_filename()+"[FEATURES_"+feature_name+"]"+"boxplot_files_data_count.txt";
        string boxpltF_file_path_A  = ds_report_base_filename()+"[FEATURES_"+feature_name+"]"+"boxplot_files_data_abs.txt";
        string boxpltF_file_path_V  = ds_report_base_filename()+"[FEATURES_"+feature_name+"]"+"boxplot_files_data_avg.txt";
        string boxpltL_file_path    = ds_report_base_filename()+"[FEATURES_"+feature_name+"]"+"boxplot_labels_data.txt";

        // export boxplot files
        export_boxplt_label_file(boxpltL_file_path, m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_C, "["+feature_name+"_COUNT]", m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_A, "["+feature_name+"_DIST_ABS]", m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_V, "["+feature_name+"_DIST_AVG]", m_seq_names);

        // open output files for export
        ofstream summary_file(summary_file_path);

        // loop over sequences to add information to reports
        for(unsigned int i=0; i< m_seq_names.size(); i++)
        {
            // export summary table data
            summary_file << m_seq_names[i] << " & " ;
            summary_file << std::fixed << std::setprecision(2) << count_stats[i].arith_mean << " & ";
            summary_file << std::fixed << std::setprecision(2) << count_stats[i].std_dev << " & ";

            summary_file << std::fixed << std::setprecision(2) << dist_abs_stats[i].arith_mean << " & ";
            summary_file << std::fixed << std::setprecision(2) << dist_abs_stats[i].std_dev << " & ";

            summary_file << std::fixed << std::setprecision(2) << dist_avg_stats[i].arith_mean << " & ";
            summary_file << std::fixed << std::setprecision(2) << dist_avg_stats[i].std_dev << " \\\\ " <<endl;

        }

        // close opened files
        summary_file.close();
    }

    void export_ds_revisit_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
                                    vector<vector_stats> m_scores_stats,
                                    vector<vector_stats> m_distance_stats,
                                    vector<int> m_LC_1p0,
                                    vector<int> m_LC_0p9,
                                    vector<int> m_LC_0p5)

    {
        // Export file paths
        string summary_file_path    = ds_report_base_filename()+"[REVISIT_FREQ]"+"summary.txt";
        string boxpltF_file_path_S  = ds_report_base_filename()+"[REVISIT_FREQ]"+"boxplot_score_files_data.txt";
        string boxpltF_file_path_D  = ds_report_base_filename()+"[REVISIT_FREQ]"+"boxplot_distance_files_data.txt";
        string boxpltL_file_path    = ds_report_base_filename()+"[REVISIT_FREQ]"+"boxplot_labels_data.txt";
        string barchart_file_path   = ds_report_base_filename()+"[REVISIT_FREQ]"+"barchart_data.dat";

        // export box plot files
        export_boxplt_label_file(boxpltL_file_path, m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_S, "[REVISIT_SCORE]", m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_D, "[REVISIT_DIST]", m_seq_names);

        // open output files for export
        ofstream summary_file(summary_file_path);
        ofstream barchart_file(barchart_file_path);
        
        // file headers
        barchart_file               << "name,size, LC_1p0, LC_0p9, LC_0p5" << endl;


        // loop over sequences and extract needed data 
        for(unsigned int i=0; i<m_seq_names.size(); i++)
        {   
            // summary table data
            summary_file << m_seq_names[i] << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_scores_stats[i].arith_mean      << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_scores_stats[i].std_dev         << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_distance_stats[i].arith_mean    << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_distance_stats[i].std_dev       << " & ";
            summary_file << m_LC_1p0[i] << " & ";
            summary_file << m_LC_0p9[i] << " & ";
            summary_file << m_LC_0p5[i] << " \\\\ " <<endl;

            // barchart data
            barchart_file << m_seq_names[i] << ",";
            barchart_file << m_seq_sizes[i] << ",";
            barchart_file << m_LC_1p0[i]    << "," ;
            barchart_file << m_LC_0p9[i]    << "," ;
            barchart_file << m_LC_0p5[i]    << endl ;
        }

        // close opened files
        summary_file.close();
        barchart_file.close();
    }


    void export_ds_inertial_diff_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
                                        vector<vector_stats> m_gx_stats, vector<vector_stats> m_gy_stats, vector<vector_stats> m_gz_stats,
                                        vector<vector_stats> m_ax_stats, vector<vector_stats> m_ay_stats, vector<vector_stats> m_az_stats,
                                        vector<vector_stats> m_gx_dot_stats, vector<vector_stats> m_gy_dot_stats, vector<vector_stats> m_gz_dot_stats,
                                        vector<vector_stats> m_ax_dot_stats, vector<vector_stats> m_ay_dot_stats, vector<vector_stats> m_az_dot_stats,
                                        vector<vector_stats> m_gx_2dot_stats, vector<vector_stats> m_gy_2dot_stats, vector<vector_stats> m_gz_2dot_stats,
                                        vector<vector_stats> m_ax_2dot_stats, vector<vector_stats> m_ay_2dot_stats, vector<vector_stats> m_az_2dot_stats)
    {
        // handle unused variables
        (void)m_seq_sizes;
        // set file path names
        string summary_raw_file_path        = ds_report_base_filename()+"[INERTIAL_DIFF]"+"summary_raw.txt";
        string summary_dot_file_path        = ds_report_base_filename()+"[INERTIAL_DIFF]"+"summary_dot.txt";
        string summary_2dot_file_path       = ds_report_base_filename()+"[INERTIAL_DIFF]"+"summary_2dot.txt";

        string boxplt_gx_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_gx.txt";
        string boxplt_gy_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_gy.txt";
        string boxplt_gz_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_gz.txt";
        string boxplt_ax_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_ax.txt";
        string boxplt_ay_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_ay.txt";
        string boxplt_az_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_az.txt";

        string boxplt_gx_dot_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_gx_dot.txt";
        string boxplt_gy_dot_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_gy_dot.txt";
        string boxplt_gz_dot_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_gz_dot.txt";
        string boxplt_ax_dot_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_ax_dot.txt";
        string boxplt_ay_dot_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_ay_dot.txt";
        string boxplt_az_dot_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_az_dot.txt";

        string boxplt_gx_2dot_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_gx_2dot.txt";
        string boxplt_gy_2dot_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_gy_2dot.txt";
        string boxplt_gz_2dot_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_gz_2dot.txt";
        string boxplt_ax_2dot_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_ax_2dot.txt";
        string boxplt_ay_2dot_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_ay_2dot.txt";
        string boxplt_az_2dot_file_path          = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_az_2dot.txt";

        string boxpltL_file_path    = ds_report_base_filename()+"[INERTIAL_DIFF]"+"boxplot_labels_data.txt";

        // export box plot files
        export_boxplt_label_file(boxpltL_file_path, m_seq_names);
        export_boxplt_data_file(boxplt_gx_file_path, "[GX]", m_seq_names);
        export_boxplt_data_file(boxplt_gy_file_path, "[GY]", m_seq_names);
        export_boxplt_data_file(boxplt_gz_file_path, "[GZ]", m_seq_names);
        export_boxplt_data_file(boxplt_ax_file_path, "[AX]", m_seq_names);
        export_boxplt_data_file(boxplt_ay_file_path, "[AY]", m_seq_names);
        export_boxplt_data_file(boxplt_az_file_path, "[AZ]", m_seq_names);

        export_boxplt_data_file(boxplt_gx_dot_file_path, "[GX_1ST_DIFF]", m_seq_names);
        export_boxplt_data_file(boxplt_gy_dot_file_path, "[GY_1ST_DIFF]", m_seq_names);
        export_boxplt_data_file(boxplt_gz_dot_file_path, "[GZ_1ST_DIFF]", m_seq_names);
        export_boxplt_data_file(boxplt_ax_dot_file_path, "[AX_1ST_DIFF]", m_seq_names);
        export_boxplt_data_file(boxplt_ay_dot_file_path, "[AY_1ST_DIFF]", m_seq_names);
        export_boxplt_data_file(boxplt_az_dot_file_path, "[AZ_1ST_DIFF]", m_seq_names);

        export_boxplt_data_file(boxplt_gx_2dot_file_path, "[GX_2ND_DIFF]", m_seq_names);
        export_boxplt_data_file(boxplt_gy_2dot_file_path, "[GY_2ND_DIFF]", m_seq_names);
        export_boxplt_data_file(boxplt_gz_2dot_file_path, "[GZ_2ND_DIFF]", m_seq_names);
        export_boxplt_data_file(boxplt_ax_2dot_file_path, "[AX_2ND_DIFF]", m_seq_names);
        export_boxplt_data_file(boxplt_ay_2dot_file_path, "[AY_2ND_DIFF]", m_seq_names);
        export_boxplt_data_file(boxplt_az_2dot_file_path, "[AZ_2ND_DIFF]", m_seq_names);

        // open summary tables
        ofstream summary_file(summary_raw_file_path);
        ofstream summary_dot_file(summary_dot_file_path);
        ofstream summary_2dot_file(summary_2dot_file_path);

        // export summary tables
        for(unsigned int i=0; i< m_seq_names.size(); i++)
        {
            // raw summary table
            summary_file << m_seq_names[i] << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_gx_stats[i].arith_mean      << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_gx_stats[i].std_dev         << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_gy_stats[i].arith_mean      << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_gy_stats[i].std_dev         << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_gz_stats[i].arith_mean      << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_gz_stats[i].std_dev         << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_ax_stats[i].arith_mean      << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_ax_stats[i].std_dev         << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_ay_stats[i].arith_mean      << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_ay_stats[i].std_dev         << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_az_stats[i].arith_mean      << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_az_stats[i].std_dev         ;
            summary_file << " \\\\ " <<endl;

            summary_dot_file << m_seq_names[i] << " & ";
            summary_dot_file << std::fixed << std::setprecision(2) << m_gx_dot_stats[i].arith_mean      << " & ";
            summary_dot_file << std::fixed << std::setprecision(2) << m_gx_dot_stats[i].std_dev         << " & ";
            summary_dot_file << std::fixed << std::setprecision(2) << m_gy_dot_stats[i].arith_mean      << " & ";
            summary_dot_file << std::fixed << std::setprecision(2) << m_gy_dot_stats[i].std_dev         << " & ";
            summary_dot_file << std::fixed << std::setprecision(2) << m_gz_dot_stats[i].arith_mean      << " & ";
            summary_dot_file << std::fixed << std::setprecision(2) << m_gz_dot_stats[i].std_dev         << " & ";
            summary_dot_file << std::fixed << std::setprecision(2) << m_ax_dot_stats[i].arith_mean      << " & ";
            summary_dot_file << std::fixed << std::setprecision(2) << m_ax_dot_stats[i].std_dev         << " & ";
            summary_dot_file << std::fixed << std::setprecision(2) << m_ay_dot_stats[i].arith_mean      << " & ";
            summary_dot_file << std::fixed << std::setprecision(2) << m_ay_dot_stats[i].std_dev         << " & ";
            summary_dot_file << std::fixed << std::setprecision(2) << m_az_dot_stats[i].arith_mean      << " & ";
            summary_dot_file << std::fixed << std::setprecision(2) << m_az_dot_stats[i].std_dev         ;
            summary_dot_file << " \\\\ " <<endl;

            summary_2dot_file << m_seq_names[i] << " & ";
            summary_2dot_file << std::fixed << std::setprecision(2) << m_gx_2dot_stats[i].arith_mean      << " & ";
            summary_2dot_file << std::fixed << std::setprecision(2) << m_gx_2dot_stats[i].std_dev         << " & ";
            summary_2dot_file << std::fixed << std::setprecision(2) << m_gy_2dot_stats[i].arith_mean      << " & ";
            summary_2dot_file << std::fixed << std::setprecision(2) << m_gy_2dot_stats[i].std_dev         << " & ";
            summary_2dot_file << std::fixed << std::setprecision(2) << m_gz_2dot_stats[i].arith_mean      << " & ";
            summary_2dot_file << std::fixed << std::setprecision(2) << m_gz_2dot_stats[i].std_dev         << " & ";
            summary_2dot_file << std::fixed << std::setprecision(2) << m_ax_2dot_stats[i].arith_mean      << " & ";
            summary_2dot_file << std::fixed << std::setprecision(2) << m_ax_2dot_stats[i].std_dev         << " & ";
            summary_2dot_file << std::fixed << std::setprecision(2) << m_ay_2dot_stats[i].arith_mean      << " & ";
            summary_2dot_file << std::fixed << std::setprecision(2) << m_ay_2dot_stats[i].std_dev         << " & ";
            summary_2dot_file << std::fixed << std::setprecision(2) << m_az_2dot_stats[i].arith_mean      << " & ";
            summary_2dot_file << std::fixed << std::setprecision(2) << m_az_2dot_stats[i].std_dev         ;
            summary_2dot_file << " \\\\ " <<endl;
        }

        summary_file.close();
        summary_dot_file.close();
        summary_2dot_file.close();
    }


    void export_ds_inertial_DR_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
                                        vector<double> DR_count_gx, vector<double> DR_count_gy, vector<double> DR_count_gz, 
                                        vector<double> DR_count_ax, vector<double> DR_count_ay, vector<double> DR_count_az, 
                                        vector<double> DR_percent_gx, vector<double> DR_percent_gy, vector<double> DR_percent_gz, 
                                        vector<double> DR_percent_ax, vector<double> DR_percent_ay, vector<double> DR_percent_az,
                                        vector<double> DR_cover_gx, vector<double> DR_cover_gy, vector<double> DR_cover_gz, 
                                        vector<double> DR_cover_ax, vector<double> DR_cover_ay, vector<double> DR_cover_az)
    {
        // handle unused variables
        (void)m_seq_sizes;
        // set file path names
        string summaryG_file_path = ds_report_base_filename()+"[INERTIAL_DR]"+"summary_gyro.txt";
        string summaryA_file_path = ds_report_base_filename()+"[INERTIAL_DR]"+"summary_acc.txt";
        ofstream summaryG_file(summaryG_file_path);
        ofstream summaryA_file(summaryA_file_path);

        for(unsigned int i=0; i<m_seq_names.size(); i++)
        {
            summaryG_file << m_seq_names[i] << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << DR_count_gx[i]    << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << DR_count_gy[i]    << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << DR_count_gz[i]    << " & ";

            summaryG_file << std::fixed << std::setprecision(2) << DR_percent_gx[i]  << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << DR_percent_gy[i]  << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << DR_percent_gz[i]  << " & ";
            
            summaryG_file << std::fixed << std::setprecision(2) << DR_cover_gx[i]    << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << DR_cover_gy[i]    << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << DR_cover_gz[i]            ;
            summaryG_file << " \\\\ " <<endl;

            summaryA_file << m_seq_names[i] << " & ";
            summaryA_file << std::fixed << std::setprecision(2) << DR_count_ax[i]    << " & ";
            summaryA_file << std::fixed << std::setprecision(2) << DR_count_ay[i]    << " & ";
            summaryA_file << std::fixed << std::setprecision(2) << DR_count_az[i]    << " & ";

            summaryA_file << std::fixed << std::setprecision(2) << DR_percent_ax[i]  << " & ";
            summaryA_file << std::fixed << std::setprecision(2) << DR_percent_ay[i]  << " & ";
            summaryA_file << std::fixed << std::setprecision(2) << DR_percent_az[i]  << " & ";

            summaryA_file << std::fixed << std::setprecision(2) << DR_cover_ax[i]    << " & ";
            summaryA_file << std::fixed << std::setprecision(2) << DR_cover_ay[i]    << " & ";
            summaryA_file << std::fixed << std::setprecision(2) << DR_cover_az[i]            ;
            summaryA_file << " \\\\ " <<endl;
        }

        // closing opened file
        summaryG_file.close();
        summaryA_file.close();
    }


    void export_ds_blurring_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
                                    vector<vector_stats> m_blur_score_stats, vector<vector_stats> m_blur_percentage_stats,
                                    vector<double> total_blur, vector<double> local_blur, vector<double> global_blur)
    {
        // handle unused variables
        (void)m_seq_sizes;

        // export box plots 
        string boxpltF_file_path_S  = ds_report_base_filename()+"[BLUR]"+"boxplot_blur_score.txt";
        string boxpltF_file_path_P  = ds_report_base_filename()+"[BLUR]"+"boxplot_blur_percentage.txt";
        string boxpltL_file_path    = ds_report_base_filename()+"[BLUR]"+"boxplot_labels_data.txt";

        export_boxplt_label_file(boxpltL_file_path, m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_S, "[BLUR_SCORE]" , m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_P, "[BLUR_PERCENT]" , m_seq_names);

        // set file path names
        string summary_file_path = ds_report_base_filename()+"[BLUR]"+"summary.txt";
        ofstream summary_file(summary_file_path);

        for(unsigned int i=0; i<m_seq_names.size(); i++)
        {
            summary_file << m_seq_names[i] << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_blur_score_stats[i].arith_mean          << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_blur_score_stats[i].std_dev             << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_blur_percentage_stats[i].arith_mean     << " & ";
            summary_file << std::fixed << std::setprecision(2) << m_blur_percentage_stats[i].std_dev        << " & ";
            summary_file << std::fixed << std::setprecision(2) << local_blur[i] << " & ";   // > 0
            summary_file << std::fixed << std::setprecision(2) << total_blur[i] << " & ";   // > 50
            summary_file << std::fixed << std::setprecision(2) << global_blur[i] ;          // > 90
            summary_file << " \\\\ " <<endl;
        }
        summary_file.close();
    }

    void export_ds_inertial_rot_only_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
                                            vector<double> rot_only_count, vector<double> rot_only_percent, vector<vector_stats> vec_stats)
    {
        // handle unused variables
        (void)m_seq_sizes;

        // export box plots 
        string boxpltF_file_path_S  = ds_report_base_filename()+"[ACC_MAG]"+"boxplot_acc_mag_data.txt";
        string boxpltL_file_path    = ds_report_base_filename()+"[ACC_MAG]"+"boxplot_labels_data.txt";

        export_boxplt_label_file(boxpltL_file_path, m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_S, "[ACC_MAG]" , m_seq_names);

        // set file path names
        string summaryG_file_path = ds_report_base_filename()+"[INERTIA_ROT_ONLY]"+"summary.txt";
        ofstream summaryG_file(summaryG_file_path);

        for(unsigned int i=0; i<m_seq_names.size(); i++)
        {
            summaryG_file << m_seq_names[i] << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << vec_stats[i].arith_mean  << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << vec_stats[i].std_dev     << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << rot_only_count[i]        << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << rot_only_percent[i];
            summaryG_file << " \\\\ " <<endl;
        }

        // closing opened file
        summaryG_file.close();
    }

    void export_ds_exposure_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
            vector<double> under_exp_count, vector<double> over_exp_count, vector<double> proper_exp_count, 
            vector<double> black_exp_count, vector<double> white_exp_count,
            vector<double> under_exp_percent, vector<double> over_exp_percent, vector<double> proper_exp_percent, 
            vector<double> black_exp_percent, vector<double> white_exp_percent,
            vector<vector_stats> mean_stats, vector<vector_stats> skewness_stats, vector<vector_stats> zone_stats)
    {
        // handle unused variables
        (void)m_seq_sizes;

        // export box plots 
        string boxpltF_file_path_d1  = ds_report_base_filename()+"[EXPOSURE_ZONE]"+"boxplot_exp_zone_data.txt";
        string boxpltF_file_path_d2  = ds_report_base_filename()+"[EXPOSURE_MEAN]"+"boxplot_exp_mean_data.txt";
        string boxpltF_file_path_d3  = ds_report_base_filename()+"[EXPOSURE_SKEW]"+"boxplot_exp_skew_data.txt";

        string boxpltL_file_path     = ds_report_base_filename()+"[EXPOSURE]"+"boxplot_labels.txt";

        export_boxplt_label_file(boxpltL_file_path, m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_d1, "[EXPOSURE_ZONE]" , m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_d2, "[EXPOSURE_MEAN]" , m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_d3, "[EXPOSURE_SKEW]" , m_seq_names);

        // set file path names
        string summaryG_file_path = ds_report_base_filename()+"[EXPOSURE]"+"summary.txt";
        ofstream summaryG_file(summaryG_file_path);

        for(unsigned int i=0; i<m_seq_names.size(); i++)
        {
            summaryG_file << m_seq_names[i] << " & ";
            
            summaryG_file << std::fixed << std::setprecision(2) << proper_exp_count[i]      << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << proper_exp_percent[i]    << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << under_exp_count[i]       << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << under_exp_percent[i]     << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << over_exp_count[i]        << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << over_exp_percent[i]      << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << black_exp_count[i]       << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << black_exp_percent[i]     << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << white_exp_count[i]       << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << white_exp_percent[i]     << " & ";

            summaryG_file << std::fixed << std::setprecision(2) << mean_stats[i].arith_mean         << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << mean_stats[i].std_dev            << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << skewness_stats[i].arith_mean     << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << skewness_stats[i].std_dev        << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << zone_stats[i].arith_mean         << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << zone_stats[i].std_dev;
            summaryG_file << " \\\\ " <<endl;
        }

        // closing opened file
        summaryG_file.close();
    }

    void export_ds_disparity_reports(vector<string>& m_seq_names, vector<int>& m_seq_sizes,
            vector<vector_stats> SBM_avg, vector<vector_stats> SBM_std_div, vector<vector_stats> SGBM_avg, vector<vector_stats> SGBM_std_div)
    {
        // handle unused variables
        (void)m_seq_sizes;

        // export box plots 
        string boxpltF_file_path_d1  = ds_report_base_filename()+"[DISPARITY]"+"boxplot_disparityBM_avg_data.txt";
        string boxpltF_file_path_d2  = ds_report_base_filename()+"[DISPARITY]"+"boxplot_disparityBM_std_div_data.txt";
        string boxpltF_file_path_d3  = ds_report_base_filename()+"[DISPARITY]"+"boxplot_disparitySGBM_avg_data.txt";
        string boxpltF_file_path_d4  = ds_report_base_filename()+"[DISPARITY]"+"boxplot_disparitySGBM_std_div_data.txt";

        string boxpltL_file_path     = ds_report_base_filename()+"[DISPARITY]"+"boxplot_labels.txt";

        export_boxplt_label_file(boxpltL_file_path, m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_d1, "[DISPARITY_BM_AVG]" , m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_d2, "[DISPARITY_BM_STD_DIV]" , m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_d3, "[DISPARITY_SGBM_AVG]" , m_seq_names);
        export_boxplt_data_file(boxpltF_file_path_d4, "[DISPARITY_SGBM_STD_DIV]" , m_seq_names);

        // set file path names
        string summaryG_file_path = ds_report_base_filename()+"[DISPARITY]"+"summary.txt";
        ofstream summaryG_file(summaryG_file_path);

        for(unsigned int i=0; i<m_seq_names.size(); i++)
        {
            summaryG_file << m_seq_names[i] << " & ";
            
            summaryG_file << std::fixed << std::setprecision(2) << SBM_avg[i].arith_mean       << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << SBM_avg[i].std_dev          << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << SBM_std_div[i].arith_mean   << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << SBM_std_div[i].std_dev      << " & ";

            summaryG_file << std::fixed << std::setprecision(2) << SGBM_avg[i].arith_mean      << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << SGBM_avg[i].std_dev         << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << SGBM_std_div[i].arith_mean  << " & ";
            summaryG_file << std::fixed << std::setprecision(2) << SGBM_std_div[i].std_dev;
            summaryG_file << " \\\\ " <<endl;
        }

        // closing opened file
        summaryG_file.close();
    }

}