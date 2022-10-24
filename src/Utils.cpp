#include "common.h"

namespace Utils
{
    // source: https://stackoverflow.com/questions/12966957/is-there-an-equivalent-in-c-of-phps-explode-function
    vector<string> explode(string const & s, char delim)
    {
        vector<string> result;
        istringstream iss(s);

        for (string token; getline(iss, token, delim); )
        {
            result.push_back(move(token));
        }

        return result;
    }

    // source: https://www.tutorialspoint.com/How-can-I-get-the-list-of-files-in-a-directory-using-C-Cplusplus
    vector<string> read_dir_files(string path)
    {
        vector<string> res;
        
        struct dirent *entry;
        const char * c_path = path.c_str();
        DIR *dir = opendir(c_path);
        
        if (dir == NULL) {
            return res;
        }
        while ((entry = readdir(dir)) != NULL) {
            if (!(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")))
            {
              res.push_back(entry->d_name);
            }
            
        }
        closedir(dir);

        return res;
    }

    // Adopted from: https://alexsm.com/cpp-closest-lower-bound/
    double search_closest(const std::vector<double>& sorted_array, double x) 
    {
        auto iter_geq = std::lower_bound(
            sorted_array.begin(), 
            sorted_array.end(), 
            x
        );

        if (iter_geq == sorted_array.begin()) 
        {
            return 0;
        }

        double a = *(iter_geq - 1);
        double b = *(iter_geq);

        if (fabs(x - a) < fabs(x - b)) 
        {
            return iter_geq - sorted_array.begin() - 1;
        }

        return iter_geq - sorted_array.begin();

    }
    

    template <class T>
    T vector_values_sum(vector<T> m_in_vec)
    {   
        T sum = 0 ;
        for(unsigned int i=0; i<m_in_vec.size(); i++)
        {
            sum += m_in_vec[i];
        }
        return sum;
    }
}

