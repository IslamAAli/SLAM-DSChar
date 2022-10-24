#ifndef DATASET_H
#define DATASET_H

#include "common.h"

class Dataset
{
    private:
        map<string, string> ds_config;
        vector<Sequence> ds_sequence;
        string ds_name;
        string ds_config_file_path;
        string ds_base_img_path;
        int ds_sequence_count;
        int curr_seq;
        Dataset_Scoreboard* ds_scoreboard;

    public:
        Dataset(string m_ds_name, string m_ds_config_file_path);
        ~Dataset();
        void reset();

        // set and get functions
        int get_ds_sequence_count();
        string get_ds_name();
        Dataset_Scoreboard* get_ds_scoreboard();

        // Read dataset information from the config file.
        bool read_ds_configuration();
        void read_ds_config_map(ifstream & m_file);
        Sequence* get_next_sequence();

        // scoreboarding functions
        void export_stats(SYS_CMD m_sys_cmd);
};


#endif