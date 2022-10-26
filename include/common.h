#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <math.h>
#include <iomanip> 

// Support for Python functions
#include <pyhelper.hpp>

// DBoW2
#include "DBoW2.h" // defines OrbVocabulary and OrbDatabase

// dirent
#include "dirent.h"

// indicators
#include "indicators.hpp"

// Class prototypes
class Sequence;
class Dataset;

class Processing_Element;
class Blur_handler;
class Brightness_handler;
class Contrast_handler;
class Disparity_handler;
class General_Metrics_handler;
class Inertial_handler;

class Sensor_Data;
class Visual_data;
class Inertial_data;

class Scoarboard;
class Sequence_Scoreboard;
class Dataset_Scoreboard;
class Blur_Scoreboard;
class Brightness_Scoreboard;
class Inertial_Diff_handler;
class Inertial_DR_handler;
class Contrast_Scoreboard;
class DBoW2_Scoreboard;
class Visual_Feature_Scoreboard;
class Features_Scoreboard;
class Inertial_Diff_Scoreboard;
class Inertial_DR_Scoreboard;
class Inertial_Axis_Diff_Scorebaord;
class Inertial_Axis_DR_Scorebaord;
class General_Char_Scoreboard;
class Disparity_Scoreboard;
class Exposure_Scoreboard;
class Disparity_Method_Scoreboard;
class Rotation_only_handler;
class Rotation_only_Scoreboard;

class System;

// Framework files
#include "defs.h"
#include "Scoreboard.h"
#include "Dataset_Scoreboard.h"
#include "Sequence_Scoreboard.h"
#include "Blur_Scoreboard.h"
#include "Brightness_Scoreboard.h"
#include "Contrast_Scoreboard.h"
#include "DBoW2_Scoreboard.h"
#include "Visual_Feature_Scoreboard.h"
#include "Features_Scoreboard.h"
#include "Inertial_Diff_Scoreboard.h"
#include "Inertial_DR_Scoreboard.h"
#include "Inertial_Axis_Diff_Scorebaord.h"
#include "Inertial_Axis_DR_Scorebaord.h"
#include "General_Char_Scoreboard.h"
#include "Disparity_Method_Scoreboard.h"
#include "Disparity_Scoreboard.h"
#include "Exposure_Scoreboard.h"
#include "Rotation_only_Scoreboard.h"
#include "Sensor_Data.h"
#include "Inertial_data.h"
#include "Visual_data.h"
#include "Sequence.h"
#include "Processing_Element.h"
#include "General_Metrics_handler.h"
#include "Utils.h"
#include "Stats_Utils.h"
#include "Calculus_Utils.h"
#include "Visualization_Utils.h"
#include "Export_Utils.h"
#include "Reports_Utils.h"
#include "Dataset.h"
#include "DBow2_handler.h"
#include "Contrast_handler.h"
#include "Features_handler.h"
#include "Brightness_handler.h"
#include "Inertial_Diff_handler.h"
#include "Inertial_DR_handler.h"
#include "Blur_handler.h"
#include "Exposure_handler.h"
#include "Disparity_handler.h"
#include "System.h" 
#include "UI_Utils.h"
#include "Rotation_only_handler.h"


// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>


using namespace DBoW2;
using namespace std;

#endif
