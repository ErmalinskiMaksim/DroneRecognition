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
	void update(const cv::Mat& frame);
	// subtract background
	virtual cv::Mat run() = 0;
protected:
	void init(const cv::Mat& first, const cv::Mat& second, const cv::Mat& third);

	cv::Mat m_prevFrame;
	cv::Mat m_currentFrame;

	cv::Mat m_diff12;
	cv::Mat m_diff23;
};

#endif // !THREE_FRME_DETECTOR
