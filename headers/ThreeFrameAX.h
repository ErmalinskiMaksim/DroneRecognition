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
	explicit ThreeFrameAX(const cv::UMat& first, const cv::UMat& second, const cv::UMat& third);
	cv::UMat run() override;
private:
	cv::UMat m_and12;
	cv::UMat m_xor23;
};
#endif // !THREEFRAMEAX