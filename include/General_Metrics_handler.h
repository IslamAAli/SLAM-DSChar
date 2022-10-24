#ifndef GENERAL_METRICS_HANDLER_H
#define GENERAL_METRICS_HANDLER_H

#include "common.h"


class General_Metrics_handler
{
    private:
        /**/

    public:
        General_Metrics_handler(/* args */);
        ~General_Metrics_handler();

        // calculate the dataset size
        void add_seq_data_size(int size, vector<int>& m_out_vec);

        // calculate the sampling rate per sample for statistical analysis
        vector<double> calculate_sampling_rate(vector<double> m_input_vec);

        // calculate the timestamp mismatch between sensors.
        void calculate_timestamp_mismatch(vector<double> m_in_vec_1, vector<double> m_in_vec_2, vector<double>& m_out_vec);

        // caluclate the total sequences' durations per sequence
        double calculate_seq_total_duration(vector<double> m_in_vec);
};


#endif