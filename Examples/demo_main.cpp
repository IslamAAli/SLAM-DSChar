/**
 * @file demo_main.cpp
 * @author Islam Ali (iaali@ualberta.ca)
 * @brief Demo file to showcase the capabilities of the Framework
 * @version 1.0
 * @date 2021-09-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common.h"


int main(int argc, char *argv[])
{
    // Check if proper input arguments are sent to the program
    if (argc <3)
    {
        cout << "[ERROR] Improper no. of input arguments." << endl;
        cout << "[ERROR] Expecting: dataset_name data_set_file_name" <<endl;
    }
    else
    {
        // vectors to hold read parameters
        vector<string> props;
        vector<string> vals;

        // read the dataset name and the dataset configuration file name from the command line argument
        string ds_name      = argv[1];
        string ds_file_path = argv[2];

        // add read parameters to the vectors
        props.push_back("Dataset Name");
        props.push_back("Config. File Path");

        vals.push_back(ds_name);
        vals.push_back(ds_file_path);

        // print the user intro
        UI_Utils::user_intro_display(props, vals);

        // Set the configuration file of the required dataset
        string DEMO_config_path = CONFIG::CONFIG_IN_PATH + ds_file_path;

        // Create an instance of the dataset class
        Dataset* DEMO_ds = new Dataset(ds_name, DEMO_config_path);

        bool program_done = false;

        while(!program_done)
        {
            char user_choice = UI_Utils::user_menu_display();
            program_done = UI_Utils::module_selector(user_choice, DEMO_ds);
        }

        
    }

    return 0; 
}