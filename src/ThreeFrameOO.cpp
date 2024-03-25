#include "../headers/ThreeFrameOO.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

ThreeFrameOO::ThreeFrameOO(const cv::Mat& first, const cv::Mat& second, const cv::Mat& third) 
	: m_subtractor(cv::createBackgroundSubtractorMOG2())
{
	init(first, second, third);
	m_currentFrame.copyTo(m_prevOr23);
}

cv::Mat ThreeFrameOO::run()
{
	static int counter = 0;
	cv::Mat filtered;
	//cv::Mat xored;

	m_subtractor->apply(m_currentFrame, m_fgMask);
	cv::bitwise_or(m_diff12, m_diff23, m_or12);
	cv::bitwise_or(m_or12, m_fgMask, m_or23);
	//cv::GaussianBlur(m_or23, filtered, { 3, 3 }, 0);
	cv::blur(m_or23, filtered, { 5, 5 });
	cv::threshold(filtered, filtered, 150, 255, 0);
	cv::imshow("threshold", filtered);
	cv::dilate(filtered, filtered, cv::getStructuringElement(cv::MORPH_CROSS, {7, 7})); // CROSS or ELLIPSE
	//if (counter < 2)
	//	counter++;
	//else
	//{
	//	cv::bitwise_xor(m_prevOr23, filtered, xored);
	//	filtered.copyTo(m_prevOr23);
	//	counter = 0;
	//}
	cv::imshow("dilated", filtered);
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
