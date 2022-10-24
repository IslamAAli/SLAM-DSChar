#ifndef DATASET_SCOREBOARD_H
#define DATASET_SCOREBOARD_H

class Dataset_Scoreboard: public Scoreboard
{
    friend class Dataset;
    private:
        // characterization scoreboards - vectors for each metric
        vector<Blur_Scoreboard*> blur_sb_vec;
        vector<Brightness_Scoreboard*> brightness_sb_vec;
        vector<Contrast_Scoreboard*> contrast_sb_vec;
        vector<DBoW2_Scoreboard*> revisit_sb_vec;
        vector<Features_Scoreboard*> features_sb_vec;
        vector<Inertial_Diff_Scoreboard*> inertial_diff_sb_vec;
        vector<Inertial_DR_Scoreboard*> inertial_dr_sb_vec;
        vector<General_Char_Scoreboard*> general_char_sb_vec;
        vector<Rotation_only_Scoreboard*> rot_only_sb_vec;
        vector<Exposure_Scoreboard*> exposure_sb_vec;
        vector<Disparity_Scoreboard*> disparity_sb_vec;

    public:
        // contructor and destructor
        Dataset_Scoreboard(/* args */);
        ~Dataset_Scoreboard();

        // save and export functions
        void export_and_save(Blur_Scoreboard* m_b_sb);
        void export_and_save(Brightness_Scoreboard* m_b_sb);
        void export_and_save(Contrast_Scoreboard* m_c_sb);
        void export_and_save(DBoW2_Scoreboard* m_rv_sb);
        void export_and_save(Features_Scoreboard* m_f_sb);
        void export_and_save(Inertial_Diff_Scoreboard* i_diff_sb);
        void export_and_save(Inertial_DR_Scoreboard* i_dr_sb);
        void export_and_save(General_Char_Scoreboard* m_gc_sb);
        void export_and_save(Rotation_only_Scoreboard* m_rot_only_sb);
        void export_and_save(Exposure_Scoreboard* m_exposure_sb);
        void export_and_save(Disparity_Scoreboard* m_disp_sb);
};



#endif