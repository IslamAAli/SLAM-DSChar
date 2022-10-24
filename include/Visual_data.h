#ifndef VISUAL_DATA_H
#define VISUAL_DATA_H

#include "common.h"

class Visual_data : public Sensor_Data
{
private:
    string img_path;
    int curr_img;
    vector<string> img_list;

public:
    Visual_data(string m_sensor_tag);
    ~Visual_data();
    void reset();


    // ===================================================================
    // Set Functions
    // ===================================================================
    void set_img_path(string m_r_img_path);

    // ===================================================================
    // Get Functions
    // ===================================================================
    string get_img_path();
    
    // ===================================================================
    // Image reading functions
    // ===================================================================
    int read_img_list();
    cv::Mat read_next_img();
};


#endif