#include "common.h"

namespace Export_Utils
{
    string construct_text_file_name(file_name_package m_file_details)
    {
        // construct the file name based on the info gathered 
        return "["+m_file_details.tag+"]"+m_file_details.ds_name+"_"+m_file_details.seq_name+m_file_details.extension;
    }

    void export_vector(vector<double> m_vec, file_name_package m_file_details)
    {
        // get the file name from the helper function
        string f_name = Export_Utils::construct_text_file_name(m_file_details);

        // construct the path to the output file
        string f_path = CONFIG::CONFIG_OUT_PATH_REPORTS+CONFIG::DATASET_NAME+f_name;
        
        // export the text file
        ofstream o_file;
        o_file.open(f_path);
        for(unsigned int i=0; i<m_vec.size(); i++)
        {
            o_file << m_vec[i];
            if (i != m_vec.size()-1)
                o_file << "\n";
        }
        o_file.close();
    }

    void export_dat_file(vector<double> m_vec, file_name_package m_file_details)
    {
        // get the file name from the helper function
        m_file_details.extension = ".dat";
        string f_name = Export_Utils::construct_text_file_name(m_file_details);

        // construct the path to the output file
        string f_path = CONFIG::CONFIG_OUT_PATH_REPORTS+CONFIG::DATASET_NAME+f_name;
        
        // export the text file
        ofstream o_file;
        o_file.open(f_path);
        o_file  << "x\ty"<<endl;
        for(unsigned int i=0; i<m_vec.size(); i++)
        {
            o_file << i+1 << "\t"<< m_vec[i];
            if (i != m_vec.size()-1)
              o_file << "\n";
        }
        o_file.close();// get the file name from the helper function
    }

    void file_export_selector(vector<double> m_vec, file_name_package m_file_details)
    {
        switch (CONFIG::CONFIG_EXPORT_MODE)
        {
            case EXPORT_TXT:
                export_vector(m_vec, m_file_details);
                break;
            
            case EXPORT_DAT:
                export_dat_file(m_vec, m_file_details);
                break;

            case EXPORT_ALL:
            default:
                export_vector(m_vec, m_file_details);
                export_dat_file(m_vec, m_file_details);
                break;
          }
    }

    void create_vector_tikz_figure(vector_stats m_vector_stats , SYS_CMD m_sys_cmd, file_name_package m_fn_pack, 
                                        string m_title, string m_x_label, string m_y_label)
    {
        // handle unused variables
        (void)m_sys_cmd;

        // handle template file
        string template_file = CONFIG::CONFIG_IN_PATH_TEMPLATES+FILE_NAMES::FILE_TIKZ_PLOT_TEMPLATE;
        vector<vector<string>> replacement_table;
        file_name_package temp_pack = m_fn_pack;
        temp_pack.extension = ".dat";
        temp_pack.tag =  m_fn_pack.tag.substr(0, m_fn_pack.tag.size()-4);

        // create the data file name
        string data_fn = CONFIG::CONFIG_OUT_PATH_TEX_REPORTS+CONFIG::DATASET_NAME+Export_Utils::construct_text_file_name(temp_pack);

        // construct the list of strings to be repalce
        replacement_table.push_back({"TEMP_TITLE"        , m_title});
        replacement_table.push_back({"X_LABEL_DATA"      , m_x_label});
        replacement_table.push_back({"Y_LABEL_DATA"      , m_y_label});
        replacement_table.push_back({"TEMP_XMAX"         , to_string((int)(m_vector_stats.count+500))});
        replacement_table.push_back({"TEMP_FILENAME"     , data_fn});
        replacement_table.push_back({"TEMP_SAMPLES"      , to_string((int)m_vector_stats.count)});
        replacement_table.push_back({"TEMP_MU"           , to_string(m_vector_stats.arith_mean)});
        replacement_table.push_back({"TEMP_MINUS_1SIGMA" , to_string(m_vector_stats.arith_mean-m_vector_stats.std_dev)});
        replacement_table.push_back({"TEMP_MINUS_2SIGMA" , to_string(m_vector_stats.arith_mean-2*m_vector_stats.std_dev)});
        replacement_table.push_back({"TEMP_MINUS_3SIGMA" , to_string(m_vector_stats.arith_mean-3*m_vector_stats.std_dev)});
        replacement_table.push_back({"TEMP_PLUS_1SIGMA"  , to_string(m_vector_stats.arith_mean+m_vector_stats.std_dev)});
        replacement_table.push_back({"TEMP_PLUS_2SIGMA"  , to_string(m_vector_stats.arith_mean+2*m_vector_stats.std_dev)});
        replacement_table.push_back({"TEMP_PLUS_3SIGMA"  , to_string(m_vector_stats.arith_mean+3*m_vector_stats.std_dev)});

        // read the template file as string
        string temp_file_content = read_file_as_string(template_file);

        // construct the tikz file name
        string out_file_name = CONFIG::CONFIG_OUT_PATH_TIKZ_FIGS+CONFIG::DATASET_NAME+construct_text_file_name(m_fn_pack);

        // perform the replacement procedure of tags vs. values
        find_and_replace_list(temp_file_content, replacement_table);

        //export the edited file as tex file
        write_file_from_string(out_file_name, temp_file_content);
    }


    string read_file_as_string(string m_file_path)
    {
        ifstream is; 
        is.open(m_file_path);

        string contents;
        // Here is one way to read the whole file
        for (char ch; is.get(ch); contents.push_back(ch)) {}
        return contents;
    }

    void write_file_from_string(string m_file_path, string& file_content)
    {
        ofstream of;
        of.open(m_file_path);

        of << file_content;

        of.close();
    }

    void find_and_replace_list(string& file_contents, vector<vector<string>> replacement_list)
    {   
        for(unsigned int i=0; i< replacement_list.size(); i++)
        {
            find_and_replace(file_contents, replacement_list[i][0], replacement_list[i][1]);
        }
    }

    void find_and_replace(string& file_contents, const string& key, const string& replacement) 
    {
        // This searches the file for the first occurence of the morn string.
        auto pos = file_contents.find(key);
        while (pos != string::npos) 
        {
            file_contents.replace(pos, key.length(), replacement);
            // Continue searching from here.
            pos = file_contents.find(key, pos);
        }
    }
}
