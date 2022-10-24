#include "common.h"

Visual_data::Visual_data(string m_sensor_tag): Sensor_Data(m_sensor_tag)
{
    img_path            = "";
    curr_img            = 0;
}

void Visual_data::reset()
{
    curr_img            = 0;
}

Visual_data::~Visual_data()
{
}

void Visual_data::set_img_path(string m_img_path)
{
    img_path = m_img_path;
}

string Visual_data::get_img_path()
{
    return img_path;
}

int Visual_data::read_img_list()
{
    // read right image folder
    img_list = Utils::read_dir_files(img_path);
    
    // sort the images
    sort(img_list.begin(), img_list.end());

    // return the number of images in the sequence
    return img_list.size();
}

cv::Mat Visual_data::read_next_img()
{
    if (curr_img < (int)img_list.size())
    {
        string full_img_path = img_path + img_list[curr_img];
        curr_img ++;
        cv::Mat image = cv::imread(full_img_path, cv::IMREAD_GRAYSCALE);
        return image;
    }
    else
    {
        return cv::Mat();
    }
}