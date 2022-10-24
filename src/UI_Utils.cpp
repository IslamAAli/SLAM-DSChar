#include "common.h"

namespace UI_Utils
{
    void user_intro_display(vector<string> m_props, vector<string> m_vals)
    {   
        cout << "\n" << endl;
        cout << "=> [ DS-EVAL - Version 0p1 ]" << endl;
        cout << "\n" << endl;

        cout << "-> Properties List:" << endl;
        cout << "--------------------" << endl;
        for(unsigned int i=0; i<m_props.size(); i++)
        {
            cout << std::setw(25) << std::right << std::setfill(' ') << m_props[i] << ": ";
            cout << m_vals[i] << endl;
        }
        cout << "\n";
    }


    char user_menu_display()
    {
        cout << "-> Characterization Options:" << endl;
        cout << "-----------------------------" << endl;

        unsigned int string_width = 40;
        char string_fill = '-';
        
        // General Commands
        cout << std::setw(string_width) << std::left << std::setfill(string_fill)<< "\t[g]: CMD_RUN_GENERAL_CHAR " ;
        cout << " Run General Dataset Characterization Module" << endl;

        cout <<endl;

        // Visual Commands
        cout << std::setw(string_width) << std::left << std::setfill(string_fill)<< "\t[1]: CMD_RUN_REVISIT_FREQ " ;
        cout << " Run Revisit Frequency Characterization Module" << endl;
        cout << std::setw(string_width) << std::left << std::setfill(string_fill)<< "\t[2]: CMD_RUN_CONTRAST ";
        cout << " Run Contrast Characterization Module" << endl;
        cout << std::setw(string_width) << std::left << std::setfill(string_fill)<< "\t[3]: CMD_RUN_BRIGHTNESS ";
        cout << " Run Brightness Characterization Module" << endl;
        cout << std::setw(string_width) << std::left << std::setfill(string_fill)<< "\t[4]: CMD_RUN_FEATURES ";
        cout << " Run Visual Features Characterization Module" << endl;
        cout << std::setw(string_width) << std::left << std::setfill(string_fill)<< "\t[5]: CMD_RUN_BLUR ";
        cout << " Run Blurring Detection Module" << endl;
        cout << std::setw(string_width) << std::left << std::setfill(string_fill)<< "\t[6]: CMD_RUN_DISPARITY ";
        cout << " Run Disparity Analysis Module" << endl;
        cout << std::setw(string_width) << std::left << std::setfill(string_fill)<< "\t[7]: CMD_RUN_EXPOSURE ";
        cout << " Run Exposure Analysis Module" << endl;
        // cout << std::setw(string_width) << std::left << std::setfill(string_fill)<< "\t[8]: CMD_RUN_KEYFRAMES ";
        // cout << " Run Exposure Analysis Module" << endl;

        cout << endl;

        // Inertial command
        cout << std::setw(string_width) << std::left << std::setfill(string_fill)<< "\t[a]: CMD_RUN_INERTIAL_DR ";
        cout << " Run Inertial Dynamic Range Characterization Module"<< endl;
        cout << std::setw(string_width) << std::left << std::setfill(string_fill)<< "\t[b]: CMD_RUN_INERTIAL_DIFF ";
        cout << " Run Inertial Time Derivatives Characterization Module" << endl;
        cout << std::setw(string_width) << std::left << std::setfill(string_fill)<< "\t[c]: CMD_RUN_INERTIAL_ROT_ONLY ";
        cout << " Run Inertial Rotation Only Detection Module" << endl;

        cout << endl;

        // Exit Command
        cout << std::setw(string_width) << std::left << std::setfill(string_fill)<< "\t[0]: EXIT ";
        cout << " Exit the Progam"<< endl;


        cout << "\n\n";

        // get user input
        cout << "Select an Option: ";
        char c ;
        cin >> c ;

        return c;
    }

    bool module_selector(char user_choice, Dataset* ds)
    {
        // boolean to check for the exit condition selection
        bool program_done = false;

        // based on user selection, pick the right CMD command
        SYS_CMD user_cmd;
        switch (user_choice)
        {
            case '1':
                user_cmd = SYS_CMD::CMD_RUN_REVISIT_FREQ;
                break;

            case '2':
                user_cmd = SYS_CMD::CMD_RUN_CONTRAST;
                break;
            
            case '3':
                user_cmd = SYS_CMD::CMD_RUN_BRIGHTNESS;
                break;

            case '4':
                user_cmd = SYS_CMD::CMD_RUN_FEATURES;
                break;

            case '5':
                user_cmd = SYS_CMD::CMD_RUN_BLUR;
                break;
            
            case '6':
                user_cmd = SYS_CMD::CMD_RUN_DISPARITY;
                break;

            case '7':
                user_cmd = SYS_CMD::CMD_RUN_EXPOSURE;
                break;

            case '8':
                user_cmd = SYS_CMD::CMD_RUN_KEYFRAMES;
                break;

            case 'a':
            case 'A':
                user_cmd = SYS_CMD::CMD_RUN_INERTIAL_DR;
                break;

            case 'b':
            case 'B':
                user_cmd = SYS_CMD::CMD_RUN_INERTIAL_DIFF;
                break;

            case 'c':
            case 'C':
                user_cmd = SYS_CMD::CMD_RUN_INERTIAL_ROT_ONLY;
                break;
            
            case '0':
                program_done = true;
                break;

            case 'g':
            case 'G':
                user_cmd = SYS_CMD::CMD_RUN_GENERAL_CHAR;
                break;
            
            default:
                cout << "Invalid Input !\n";
                return false;
                break;
        }

        // only execute the command if exit is not selected
        if (!program_done)
        {
            // reset dataset counters
            ds->reset();
            
            // create an instance of the system class and send the dataset to it
            System* SYS_evaluator = new System(ds);

            // initialize the framework operation
            SYS_evaluator->initialize();

            // execute an evaluation command to the system
            SYS_evaluator->execute(user_cmd);

            delete SYS_evaluator;
        }

        // return the exit status for program control
        return program_done;
    }
}