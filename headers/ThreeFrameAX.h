#pragma once
#ifndef THREEFRAMEAX
#define THREEFRAMEAX
#include "ThreeFrameDetector.h"

// three-frame AND-XOR background subtracktor
class ThreeFrameAX : public ThreeFrameDetector
{
public:
	ThreeFrameAX() = delete;
	ThreeFrameAX(const ThreeFrameAX&) = delete;
	ThreeFrameAX(ThreeFrameAX&&) = delete;
	~ThreeFrameAX();
	// accepts 3-channel images and internally converts them to 1-channel gray
	explicit ThreeFrameAX(const cv::Mat& first, const cv::Mat& second, const cv::Mat& third);
	cv::Mat run() override;
private:
	cv::Mat m_and12;
	cv::Mat m_xor23;
};
#endif // !THREEFRAMEAX