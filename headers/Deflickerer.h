#pragma once
#ifndef DEFLICKERER
#define DEFLICKERER
#include "opencv2/core/mat.hpp"

class Deflickerer
{
public:
	Deflickerer(){}
	// accepts 1-channel gray images
	//comp ares each pixel of the frame to a previously stored frame, and throttle small changes in pixels
	cv::Mat run(cv::Mat img, int cutOffStrength);
private:
	cv::Mat m_prev;
};
#endif // !DEFLICKERER
