#include "../headers/ThreeFrameAX.h"
#include "opencv2/highgui.hpp"

ThreeFrameAX::~ThreeFrameAX()
{
	m_xor23.release();
	m_and12.release();
	m_diff23.release();
	m_diff12.release();
	m_currentFrame.release();
	m_prevFrame.release();
}

ThreeFrameAX::ThreeFrameAX(const cv::Mat& first, const cv::Mat& second, const cv::Mat& third)
{
	init(first, second, third);
}

cv::Mat ThreeFrameAX::run()
{
	cv::Mat and14;
 
	cv::threshold(m_diff12, m_diff12, 50, 255, 0);
	cv::threshold(m_diff23, m_diff23, 50, 255, 0);
	cv::bitwise_and(m_diff12, m_diff23, m_and12);
	cv::bitwise_xor(m_diff23, m_and12, m_xor23);

	//cv::threshold(xor23, xor23, 100, 255, 0);
	cv::bitwise_and(m_and12, m_xor23, and14);
	//cv::imshow("and12", m_and12);
	//cv::imshow("xor23", m_xor23);
	//cv::imshow("and14", and14);

	return and14;
}
