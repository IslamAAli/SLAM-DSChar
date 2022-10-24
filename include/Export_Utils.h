#ifndef EXPORT_UTILS_H
#define EXPORT_UTILS_H

#include "common.h"

namespace Export_Utils
{
    void file_export_selector(vector<double> m_vec, file_name_package m_file_details);
    void export_vector(vector<double> m_vec, file_name_package m_file_details);
    void export_dat_file(vector<double> m_vec, file_name_package m_file_details);
    string construct_text_file_name(file_name_package m_file_details);
    void create_vector_tikz_figure(vector_stats m_vector_stats , SYS_CMD m_sys_cmd, file_name_package m_fn_pack, 
                                        string m_title, string m_x_label, string m_y_label);

    string read_file_as_string(string m_file_path);
    void write_file_from_string(string m_file_path, string& file_content);
    void find_and_replace_list(string& file_contents, vector<vector<string>> replacement_list);
    void find_and_replace(string& file_contents, const string& key, const string& replacement);
}

#endif