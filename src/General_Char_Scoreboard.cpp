#include "common.h"


General_Char_Scoreboard::General_Char_Scoreboard(Sequence* m_seq): Sequence_Scoreboard(m_seq)
{
}

General_Char_Scoreboard::~General_Char_Scoreboard()
{
}

void General_Char_Scoreboard::export_results()
{
    cout << "[GENERAL_CHAR] *** Exporting Results  ... " << endl;

    // export the sequence general results
    vector<Sensor_Data*> vec_sensors = seq->get_sensor_data_ptr();
    for(unsigned int i=0; i< vec_sensors.size(); i++)
    {
        // total samples
        vector<double> temp_vec;
        f_p.tag = vec_sensors[i]->get_sensor_tag()+"_SAMPLES_COUNT";
        temp_vec.clear();
        temp_vec.push_back((double)vec_sensors[i]->get_sample_count());
        Export_Utils::file_export_selector(temp_vec, f_p); 

        // Sequence Presence
        f_p.tag = vec_sensors[i]->get_sensor_tag()+"_SEQ_COUNT";
        temp_vec.clear();
        temp_vec.push_back(1.0);
        Export_Utils::file_export_selector(temp_vec, f_p);

        // total duration
        f_p.tag = vec_sensors[i]->get_sensor_tag()+"_DURATION";
        temp_vec.clear();
        temp_vec.push_back((double)vec_sensors[i]->get_duration());
        Export_Utils::file_export_selector(temp_vec, f_p);

        // per sample Sampling Rate
        f_p.tag = vec_sensors[i]->get_sensor_tag()+"_SAMPLE_RATE";
        Export_Utils::file_export_selector(vec_sensors[i]->get_persample_sampling_rate_vector(), f_p);
    }

    // export the mismatch vectors
    f_p.tag = "VI_TIMESTAMP_MISMATCH";
    Export_Utils::file_export_selector(visual_inertial_timestamps_mismatch, f_p);
}


void General_Char_Scoreboard::set_timestamp_mismatch_vec(vector<double> m_vec)
{
    visual_inertial_timestamps_mismatch = m_vec;
}

vector<double> General_Char_Scoreboard::get_timestamp_mismatch_vec()
{
    return visual_inertial_timestamps_mismatch;
}