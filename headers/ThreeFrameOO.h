#pragma once
#ifndef THREEFRAMEOO
#define THREEfRAMEOO
#include "ThreeFrameDetector.h"
#include "opencv2/video/background_segm.hpp"
class ThreeFrameOO : public ThreeFrameDetector
{
public:
	ThreeFrameOO() = delete;
	ThreeFrameOO(const ThreeFrameOO&) = delete;
	ThreeFrameOO(ThreeFrameOO&&) = delete;
	// accepts 3-channel colored images and converts internally into 1-channel gray
	ThreeFrameOO(const cv::Mat& first, const cv::Mat& second, const cv::Mat& third);
	~ThreeFrameOO();

	cv::Mat run() override;
private:
	cv::Mat m_or12;
	cv::Mat m_or23;

	cv::Mat m_fgMask;
	cv::Ptr<cv::BackgroundSubtractor> m_subtractor;
};

#endif