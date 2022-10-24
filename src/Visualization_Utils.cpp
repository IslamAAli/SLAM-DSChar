#include "common.h"

namespace Visualization_Utils
{
    void visualize_matrix(cv::Mat m_mat, double resize_factor)
    {
        cv::Mat dst;
        cv::resize(m_mat, dst, cv::Size(m_mat.cols*resize_factor, m_mat.rows*resize_factor), 0, 0, cv::INTER_AREA);
        cv::normalize(dst, dst, 0, 1, cv::NORM_MINMAX, CV_32FC1);
        cv::imshow("test", dst);
        cv::waitKey(1);
    }


    void print_vector(vector<string> vec)
    {
        for(unsigned int i=0; i<vec.size();i++)
        {
            cout<< vec[i] <<endl;   
        }
    }

    void print_vector(vector<double> vec)
    {
        for(unsigned int i=0; i<vec.size();i++)
        {
            cout<< vec[i] <<endl;   
        }
    }

    indicators::ProgressBar* create_progress_bar()
    {
        indicators::show_console_cursor(false);
        indicators::ProgressBar* bar = new indicators::ProgressBar{
            indicators::option::BarWidth{50},
            indicators::option::Start{"["},
            indicators::option::Fill{"■"},
            indicators::option::Lead{"■"},
            indicators::option::Remainder{"-"},
            indicators::option::End{" ]"},
            indicators::option::PostfixText{"Done"},
            indicators::option::ShowPercentage(true),
            indicators::option::ForegroundColor{indicators::Color::yellow},
            indicators::option::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}
        };

        return bar;
    }

    void close_progress_bar()
    {
        cout<<endl;
        indicators::show_console_cursor(true);
        cout << termcolor::reset;
    }
}
