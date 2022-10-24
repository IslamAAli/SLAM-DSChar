#include "common.h"

DBow2_handler::DBow2_handler(int m_img_count, Sequence* m_curr_seq)
{
    img_count = m_img_count;
    curr_seq = m_curr_seq;
}

DBow2_handler::~DBow2_handler()
{

}

void DBow2_handler::loadFeatures(IMG_STEREO_SEQ img_seq)
{
    features.clear();
    features.reserve(this->img_count);

    cv::Ptr<cv::ORB> orb = cv::ORB::create();

    cout << "==>[DBoW2 Handler] Extracting ORB features..." << endl;

    // Hide cursor and create a progress bar
    indicators::ProgressBar* bar = Visualization_Utils::create_progress_bar();

    for(int i = 0; i < this->img_count; ++i)
    {
        bar->set_progress(((double)i/(double)this->img_count)*100.0);

        cv::Mat image = curr_seq->read_next_img(img_seq);
        cv::Mat mask;
        vector<cv::KeyPoint> keypoints;
        cv::Mat descriptors;
        orb->detectAndCompute(image, mask, keypoints, descriptors);

        features.push_back(vector<cv::Mat >());
        changeStructure(descriptors, features.back());
    }
    // Show cursor after the progress is complete
    Visualization_Utils::close_progress_bar();
}


void DBow2_handler::changeStructure(const cv::Mat &plain, vector<cv::Mat> &out)
{
  	out.resize(plain.rows);

	for(int i = 0; i < plain.rows; ++i)
	{
		out[i] = plain.row(i);
	}
}


void DBow2_handler::testDatabase(DBoW2_Scoreboard* revisit_sb)
{
	cout << "==>[DBoW2 Handler] Creating a database..." << endl;

	// load the vocabulary from disk
	OrbVocabulary voc;
	voc.loadFromTextFile("ORBvoc.txt");

	OrbDatabase db(voc, false, 0); // false = do not use direct index
	// add images to the database
	for(int i = 0; i < this->img_count; i++)
	{
		db.add(features[i]);
	}

	cout << "==>[DBoW2 Handler] Database information: " << endl;
	cout << "==>[DBoW2 Handler] " << db << endl;

	// and query the database
	cout << "==>[DBoW2 Handler] Querying the database. " << endl;


	// Hide cursor and create a progress bar
	indicators::ProgressBar* bar = Visualization_Utils::create_progress_bar();

	QueryResults ret;
	for(int i = 0; i < this->img_count; i++)
	{
		bar->set_progress(((double)i/(double)this->img_count)*100.0);

		db.query(features[i], ret, 2);
		for(unsigned int j=0; j<ret.size(); j++)
		{
			// check for loop closure (ids must be different and the score must be matching the min score.)
			if (i != (int)(ret[j].Id))
			{
				revisit_sb->add_revisit_score( (ret[j]).Score, abs((int)(ret[j].Id)-i) );
			}
		}
	}
	// Show cursor after the progress is complete
	Visualization_Utils::close_progress_bar();
}