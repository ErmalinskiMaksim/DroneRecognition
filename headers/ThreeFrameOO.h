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
	explicit ThreeFrameOO(const cv::UMat& first, const cv::UMat& second, const cv::UMat& third);
	~ThreeFrameOO();

	cv::UMat run() override;
private:
	cv::UMat m_or12;
	cv::UMat m_or23;

	cv::UMat m_fgMask;
	cv::Ptr<cv::BackgroundSubtractor> m_subtractor;
};

#endif