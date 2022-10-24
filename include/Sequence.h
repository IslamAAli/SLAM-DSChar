#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "common.h"

class Sequence
{
private:
    
    // General dataset and sequence attributes
    string ds_name;
    string seq_name;
    bool stereo_data_status;
    bool inertial_data_status;
    int seq_img_count;
    
    // vector of pointers to different data elements
    vector<Sensor_Data*> seq_data_vec;

    // Visual Data Attributes
    Visual_data* r_img_data;
    Visual_data* l_img_data;

    // Inertial Data Attributes
    Inertial_data* seq_inertial_data;

public:
    
    // Constructors, Destructors, and Initialization Functions
    Sequence(string m_ds_name);
    ~Sequence();
    void init_2nd_stage();
    void reset();
    
    // Set Functions
    void set_seq_name(string m_seq_name);
    void set_stereo_data_status(bool m_stereo_data); 
    void set_inertial_data_status(bool m_inertial_data);
    void set_seq_img_count(int m_seq_img_count);
    void set_ds_name(string m_ds_name);
    
    // Get Functions
    string get_seq_name();
    bool get_stereo_data_status();
    bool get_inertial_data_status();
    int get_seq_img_count();
    string get_ds_name();
    vector<Sensor_Data*> get_sensor_data_ptr();
    
    // Image reading functions
    Visual_data* get_r_imgs();
    Visual_data* get_l_imgs();
    void read_img_list();
    vector<double> get_visual_timestamps_vector(IMG_STEREO_SEQ m_seq_mode);
    cv::Mat read_next_img(IMG_STEREO_SEQ m_seq_folder);

    // Inertial data functions
    Inertial_data* get_seq_inertial_data();
    vector<double> get_inertial_timestamps_vector();

    // register data items to sequence
    void register_stereo_r_data();
    void register_stereo_l_data();
    void register_inertial_data();

    // timestamps reading fucntions
    void read_timestamps();

    // scoring functions
    Sequence_Scoreboard* get_scoreboard();
};


#endif