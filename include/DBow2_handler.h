#ifndef DBOW2_HANDLER_H
#define DBOW2_HANDLER_H

#include "common.h"

class DBow2_handler : public Processing_Element
{
    private:
        vector<vector<cv::Mat>> features;
        int img_count;
        Sequence* curr_seq;

    public:
        DBow2_handler(int m_img_count, Sequence* m_curr_seq);
        ~DBow2_handler();
        void loadFeatures(IMG_STEREO_SEQ img_seq);
        void changeStructure(const cv::Mat &plain, vector<cv::Mat> &out);
        void testDatabase(DBoW2_Scoreboard* revisit_sb);

};


#endif