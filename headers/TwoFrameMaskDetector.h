#pragma once
#ifndef TWOFRAME_MASK_ANALYSER
#define TWOFRAME_MASK_ANALYSER
#include "opencv2/core/mat.hpp"

class TwoFrameMaskDetector
{
public:
	TwoFrameMaskDetector() = delete;
	explicit TwoFrameMaskDetector(const cv::Mat& staticMask, const cv::Mat& dynamicMask);
	~TwoFrameMaskDetector();

	cv::Mat run(const cv::Mat& frame);
private:
	cv::Mat m_staticMask;
	cv::Mat m_dynamicMask;
	cv::Mat m_staticDiff;
	cv::Mat m_dynamicDiff;
};

#endif