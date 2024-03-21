#include "../headers/ThreeFrameOO.h"
#include "opencv2/highgui.hpp"

ThreeFrameOO::ThreeFrameOO(const cv::Mat& first, const cv::Mat& second, const cv::Mat& third) 
	: m_subtractor(cv::createBackgroundSubtractorMOG2())
{
	init(first, second, third);
}

cv::Mat ThreeFrameOO::run()
{
	cv::Mat filtered;

	m_subtractor->apply(m_currentFrame, m_fgMask);
	cv::bitwise_or(m_diff12, m_diff23, m_or12);
	cv::bitwise_or(m_or12, m_fgMask, m_or23);
	cv::medianBlur(m_or23, filtered, 7);
	cv::threshold(filtered, filtered, 180, 255, 0);
	return filtered;
}

ThreeFrameOO::~ThreeFrameOO()
{
	m_subtractor.release();
	m_fgMask.release();
	m_or23.release();
	m_or12.release();
	m_diff23.release();
	m_diff12.release();
	m_currentFrame.release();
	m_prevFrame.release();
}
