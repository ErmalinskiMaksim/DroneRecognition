#pragma once
#ifndef THREE_FRME_DETECTOR
#define THREE_FRAME_DETECTOR
#include "opencv2/core/mat.hpp"
#include "opencv2/imgproc.hpp"

class ThreeFrameDetector
{
public:
	ThreeFrameDetector(const ThreeFrameDetector&) = delete;
	ThreeFrameDetector(ThreeFrameDetector&&) = delete;
	virtual ~ThreeFrameDetector() {}
	ThreeFrameDetector(){}
	// accepts 3-channel images and internally converts them to 1-channel gray. Performs the subtraction
	void update(const cv::UMat& frame);
	// subtract background
	virtual cv::UMat run() = 0;
protected:
	void init(const cv::UMat& first, const cv::UMat& second, const cv::UMat& third);

	cv::UMat m_prevFrame;
	cv::UMat m_currentFrame;

	cv::UMat m_diff12;
	cv::UMat m_diff23;
};

#endif // !THREE_FRME_DETECTOR
