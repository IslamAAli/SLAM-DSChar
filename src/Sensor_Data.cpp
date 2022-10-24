#include "common.h"

Sensor_Data::Sensor_Data(string m_sensor_tag)
{
    seq_duration = 0;
    samples_count = 0;
    sensor_tag = m_sensor_tag;
}

Sensor_Data::~Sensor_Data()
{
}

void Sensor_Data::set_timestamps_path(string m_timestamps_path)
{
    timestamps_path = m_timestamps_path;
}

string Sensor_Data::get_timestamps_path()
{
    return timestamps_path;
}

vector<double> Sensor_Data::get_timestamps_vector()
{
    return timestamps;
}

void Sensor_Data::read_timestamps()
{
    ifstream r_file;
    r_file.open(timestamps_path);

    double file_data;
    while(r_file>>file_data)
    {        
        timestamps.push_back(file_data);
    }
    r_file.close();
}

double Sensor_Data::get_sampling_rate()
{
    double sum = 0 ;
    for(unsigned int i=1 ; i<timestamps.size(); i++)
    {
        sum += (timestamps[i]- timestamps[i-1]);
    }
    return sum/(timestamps.size()-1);
}

int Sensor_Data::get_sensor_data_size()
{
    return timestamps.size();
}

void Sensor_Data::set_persample_sampling_rate(vector<double> m_sampling_rate_vec)
{
    per_sample_sampling_rate = m_sampling_rate_vec;
}

vector<double> Sensor_Data::get_persample_sampling_rate_vector()
{
    return per_sample_sampling_rate;
}

void Sensor_Data::set_duration(double m_duration)
{
    seq_duration = m_duration;
}
double Sensor_Data::get_duration()
{
    return seq_duration;
}

void Sensor_Data::set_samples_count(int m_count)
{
    samples_count = m_count;
}

int Sensor_Data::get_sample_count()
{
    return samples_count;
}

string Sensor_Data::get_sensor_tag()
{
    return sensor_tag;
}