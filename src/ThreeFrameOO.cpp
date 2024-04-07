#include "../headers/ThreeFrameOO.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

ThreeFrameOO::ThreeFrameOO(const cv::UMat& first, const cv::UMat& second, const cv::UMat& third) 
	: m_subtractor(cv::createBackgroundSubtractorMOG2())
{
	init(first, second, third);
}
cv::UMat ThreeFrameOO::run()
{
	cv::UMat filtered;

	m_subtractor->apply(m_currentFrame, m_fgMask);
	cv::bitwise_or(m_diff12, m_diff23, m_or12);
	cv::bitwise_or(m_or12, m_fgMask, m_or23);
	cv::threshold(m_or23, filtered, 190, 255, 3);
	cv::blur(m_or23, filtered, { 8, 3 });
	//cv::GaussianBlur(m_or23, filtered, {3, 7}, 240, 240);
	cv::threshold(filtered, filtered, 180, 255, 0);
	cv::dilate(filtered, filtered, cv::getStructuringElement(cv::MORPH_ELLIPSE, {7, 7})); // CROSS or ELLIPSE
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
