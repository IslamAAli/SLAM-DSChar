#include "common.h"


Sequence::Sequence(string m_ds_name)
{
    seq_name                    = "";
    ds_name                     = m_ds_name;
    stereo_data_status          = false;
    inertial_data_status        = false;
    seq_img_count               = 0;

    r_img_data                  = new Visual_data("RGB_CAM_R");
    l_img_data                  = new Visual_data("RGB_CAM_L");
    seq_inertial_data           = new Inertial_data("IMU");
}

Sequence::~Sequence()
{
}

void Sequence::init_2nd_stage()
{
}

void Sequence::reset()
{
    for(unsigned int i=0; i< seq_data_vec.size(); i++)
    {
        seq_data_vec[i]->reset();
    }
}

void Sequence::register_stereo_r_data()
{
    seq_data_vec.push_back(r_img_data);
}
void Sequence::register_stereo_l_data()
{
    seq_data_vec.push_back(l_img_data);
}
void Sequence::register_inertial_data()
{
    seq_data_vec.push_back(seq_inertial_data);
}

// ==================================================================================
// Set and Get Methods for Sequence Class
// ==================================================================================
void Sequence::set_seq_name(string m_seq_name)
{
    seq_name = m_seq_name;
}

void Sequence::set_stereo_data_status(bool m_stereo_data)
{
    stereo_data_status = m_stereo_data;
}

void Sequence::set_inertial_data_status(bool m_inertial_data)
{
    inertial_data_status = m_inertial_data;
}

void Sequence::set_seq_img_count(int m_seq_img_count)
{
    seq_img_count = m_seq_img_count;
}

void Sequence::set_ds_name(string m_ds_name)
{
    ds_name = m_ds_name;
}

string Sequence::get_seq_name()
{
    return seq_name;
}

bool Sequence::get_stereo_data_status()
{
    return stereo_data_status;
}

bool Sequence::get_inertial_data_status()
{
    return inertial_data_status;
}

int Sequence::get_seq_img_count()
{
    return seq_img_count;
}

string Sequence::get_ds_name()
{
    return ds_name;
}
vector<Sensor_Data*> Sequence::get_sensor_data_ptr()
{
    return seq_data_vec;
}
// ====================================================================
// Get Functions for timestamping
// ====================================================================
vector<double> Sequence::get_visual_timestamps_vector(IMG_STEREO_SEQ m_seq_mode)
{   
    if (m_seq_mode == RIGHT_SEQ)
    {
        return r_img_data->get_timestamps_vector();
    }
    else
    {
        return l_img_data->get_timestamps_vector();
    }
}

// ====================================================================
// Reading Image list functions
// ====================================================================
void Sequence::read_img_list()
{
    // read right image list
    int r_img_count = r_img_data->read_img_list();

    // read left image list if available
    if(stereo_data_status)
        l_img_data->read_img_list();

    // setting the sequence image count parameter
    seq_img_count = r_img_count;

    // continue the initialization
    init_2nd_stage();
}

Visual_data* Sequence::get_r_imgs()
{
    return r_img_data;
}

Visual_data* Sequence::get_l_imgs()
{
    return l_img_data;
}

// ==================================================================================
// reading next image in sequence
// ==================================================================================
cv::Mat Sequence::read_next_img(IMG_STEREO_SEQ m_seq_folder)
{
    if (m_seq_folder == RIGHT_SEQ)
    {
        
        return r_img_data->read_next_img();
    }
    else
    {
        return l_img_data->read_next_img();
    }
}

// ==================================================================================
// reading timestamp vectors from dataset folder
// ==================================================================================
void Sequence::read_timestamps()
{
    r_img_data->read_timestamps();

    if(stereo_data_status)
        l_img_data->read_timestamps();
}
// ==================================================================================
// Inertial Data Functions
// ==================================================================================
Inertial_data* Sequence::get_seq_inertial_data()
{
    return seq_inertial_data;
}

vector<double> Sequence::get_inertial_timestamps_vector()
{
    return seq_inertial_data->get_timestamps_vector();
}