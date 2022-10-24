#ifndef INERTIAL_DATA_H
#define INERTIAL_DATA_H

#include "common.h"

class Inertial_data : public Sensor_Data
{
friend class Sequence;
private:
    string inertial_data_path;
    double gyro_DR_pos;
    double gyro_DR_neg;
    double acc_DR_pos;
    double acc_DR_neg;

    vector<double> gyro_x;
    vector<double> gyro_y;
    vector<double> gyro_z;

    vector<double> acc_x;
    vector<double> acc_y;
    vector<double> acc_z;

    vector<double> timestamps;

public:
    Inertial_data(string m_sensor_tag);
    ~Inertial_data();
    void reset();

    // set and get functions
    void set_inertial_data_path(string m_path);

    // read data from file
    void read_inertial_data();

    // get inertial data vectors
    vector<double> get_inertial_data_axis(INERTIAL_MODE m_mode);
    vector<double> get_gyro_x();
    vector<double> get_gyro_y();
    vector<double> get_gyro_z();

    vector<double> get_acc_x();
    vector<double> get_acc_y();
    vector<double> get_acc_z();

    // set and get dynamic range information
    void set_gyro_DR_pos(double m_value);
    void set_gyro_DR_neg(double m_value);
    void set_acc_DR_pos(double m_value);
    void set_acc_DR_neg(double m_value);

    void get_sensor_DR_limits_axis(INERTIAL_MODE m_mode, double& m_upper_limit, double& m_lower_limit);
    double get_gyro_DR_pos();
    double get_gyro_DR_neg();
    double get_acc_DR_pos();
    double get_acc_DR_neg();

    void get_inertial_data_by_axis(INERTIAL_MODE m_mode, vector<double>& g_vec, vector<double>& a_vec);
};


#endif