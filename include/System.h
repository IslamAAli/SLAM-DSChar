#ifndef SYSTEM_H
#define SYSTEM_H

#include "common.h"

class System
{
    private:
        Dataset* curr_dataset;


    public:
        System(Dataset* m_ds);
        ~System();

        // cosemtics functions
        void print_system_intro();

        // top-level execute function for the whole evaluation system 
        void initialize();
        void execute(SYS_CMD m_sys_cmd);
        bool command_issuer(SYS_CMD m_sys_cmd, Sequence* m_seq);
        void command_error(CMD_ERROR m_error);
        
        // compute the info for the loop closure sub-system
        void compute_revisit_freq(Sequence* m_seq);
        void compute_contrast(Sequence* m_seq);
        void compute_brightness(Sequence* m_seq);
        void compute_features_dist(Sequence* m_seq);
        void compute_inertial_diff(Sequence* m_seq);
        void compute_inertial_diff_axis(Sequence* m_seq, Inertial_Diff_handler* m_calc, Inertial_Diff_Scoreboard* m_sb, INERTIAL_MODE m_mode);
        void compute_inertial_DR(Sequence* m_seq);
        void compute_inertial_DR_axis(Sequence* m_seq, Inertial_DR_handler* m_calc, Inertial_DR_Scoreboard* m_sb, INERTIAL_MODE m_mode);
        void compute_blur(Sequence* m_seq);
        void compute_general_characteristics(Sequence* m_seq);
        void compute_inertial_rot_only(Sequence* m_seq);
        void compute_exposure(Sequence* m_seq);
        void compute_disparity(Sequence* m_seq);
        

};

#endif