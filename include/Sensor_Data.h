#ifndef SENSOR_DATA_H
#define SESNOR_DATA_H

#include "common.h"

class Sensor_Data
{
private:
    vector<double> timestamps;
    string timestamps_path;
    vector<double> per_sample_sampling_rate;
    double seq_duration;
    int samples_count;
    string sensor_tag;

public:
    Sensor_Data(string m_sensor_tag);
    ~Sensor_Data();
    virtual void reset() = 0;

    string get_timestamps_path();
    void set_timestamps_path(string m_timestamps_path);
    vector<double> get_timestamps_vector();
    void read_timestamps();
    double get_sampling_rate();
    int get_sensor_data_size();

    void set_persample_sampling_rate(vector<double> m_sampling_rate_vec);
    vector<double> get_persample_sampling_rate_vector();

    void set_duration(double m_duration);
    double get_duration();

    void set_samples_count(int m_count);
    int get_sample_count();

    string get_sensor_tag();
};

#endif