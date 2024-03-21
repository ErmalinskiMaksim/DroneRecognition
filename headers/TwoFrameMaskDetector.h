#pragma once
#ifndef TWOFRAME_MASK_ANALYSER
#define TWOFRAME_MASK_ANALYSER
#include "opencv2/core/mat.hpp"

class TwoFrameMaskDetector
{
public:
	TwoFrameMaskDetector(const cv::Mat& mask);
	const cv::Mat& getBuffer() const;
	void setMask(const cv::Mat& mask);
	void thresholdBuffer(double sigma1, double sigma2, int type);
	void getDifference(const cv::Mat& mask);
	~TwoFrameMaskDetector();
private:
	cv::Mat m_mask;
	cv::Mat m_buffer;
};

#endif