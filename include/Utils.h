#ifndef UTILS_H
#define UTILS_H

namespace Utils
{
    vector<string> explode(string const & s, char delim);
    vector<string> read_dir_files(string path);  
    double search_closest(const std::vector<double>& sorted_array, double x);  
    template <class T>
    T vector_values_sum(vector<T> m_in_vec);
}

#endif