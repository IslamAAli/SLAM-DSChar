#include "common.h"

// ==================================================================================
// Constructors and Destructors
// ==================================================================================
Inertial_data::Inertial_data(string m_sensor_tag): Sensor_Data(m_sensor_tag)
{
}

Inertial_data::~Inertial_data()
{
}

void Inertial_data::reset()
{ 
}

// ==================================================================================
// Setters and Getters
// ==================================================================================
void Inertial_data::set_inertial_data_path(string m_path)
{
    inertial_data_path = m_path;
}

// ==================================================================================
// Read data from files
// ==================================================================================
void Inertial_data::read_inertial_data()
{
    ifstream r_file;
    r_file.open(inertial_data_path);

    double gx, gy, gz, ax, ay, az;
    while(r_file >> gx >> gy >> gz >> ax >> ay >> az)
    {        
        gyro_x.push_back(gx);
        gyro_y.push_back(gy);
        gyro_z.push_back(gz);

        acc_x.push_back(ax);
        acc_y.push_back(ay);
        acc_z.push_back(az);
    }
    r_file.close();
}


vector<double> Inertial_data::get_inertial_data_axis(INERTIAL_MODE m_mode)
{
    vector<double> data;
    switch (m_mode)
    {
        case GYRO_X:
            data=gyro_x;
            break;

        case GYRO_Y:
            data=gyro_y;
            break;

        case GYRO_Z:
            data=gyro_z;
            break;

        case ACC_X:
            data=acc_x;
            break;

        case ACC_Y:
            data=acc_y;
            break;

        case ACC_Z:
            data=acc_z;
            break;
    
        default:
            break;
    }
    return data;
}

void Inertial_data::get_sensor_DR_limits_axis(INERTIAL_MODE m_mode, double& m_upper_limit, double& m_lower_limit)
{
    switch (m_mode)
    {
        case GYRO_X:
        case GYRO_Y:
        case GYRO_Z:
            m_upper_limit = gyro_DR_pos;
            m_lower_limit = gyro_DR_neg;
            break;

        case ACC_X:
        case ACC_Y:
        case ACC_Z:
            m_upper_limit = acc_DR_pos;
            m_lower_limit = acc_DR_neg;
            break;
    
        default:
            m_upper_limit = 0;
            m_lower_limit = 0;
            break;
    }
}

vector<double> Inertial_data::get_gyro_x()
{
    return gyro_x;
}
vector<double> Inertial_data::get_gyro_y()
{
    return gyro_y;
}
vector<double> Inertial_data::get_gyro_z()
{
    return gyro_z;
}
vector<double> Inertial_data::get_acc_x()
{
    return acc_x;
}
vector<double> Inertial_data::get_acc_y()
{
    return acc_y;
}
vector<double> Inertial_data::get_acc_z()
{
    return acc_z;
}

void Inertial_data::set_gyro_DR_pos(double m_value)
{
    gyro_DR_pos = m_value;
}

void Inertial_data::set_gyro_DR_neg(double m_value)
{
    gyro_DR_neg = m_value;
}

void Inertial_data::set_acc_DR_pos(double m_value)
{
    acc_DR_pos = m_value;
}

void Inertial_data::set_acc_DR_neg(double m_value)
{
    acc_DR_neg = m_value;
}

double Inertial_data::get_gyro_DR_pos()
{
    return gyro_DR_pos;
}

double Inertial_data::get_gyro_DR_neg()
{
    return gyro_DR_neg;
}

double Inertial_data::get_acc_DR_pos()
{
    return acc_DR_pos;
}

double Inertial_data::get_acc_DR_neg()
{
    return acc_DR_neg;
}

void Inertial_data::get_inertial_data_by_axis(INERTIAL_MODE m_mode, vector<double>& g_vec, vector<double>& a_vec)
{
    switch (m_mode)
    {
        case GYRO_X:
        case ACC_X:
            g_vec = gyro_x;
            a_vec = acc_x;
            break;

        case GYRO_Y:
        case ACC_Y:
            g_vec = gyro_y;
            a_vec = acc_y;
            break;

        case GYRO_Z:
        case ACC_Z:
            g_vec = gyro_z;
            a_vec = acc_z;
            break;

        default:
            break;
    }
}