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

ThreeFrameAX::ThreeFrameAX(const cv::UMat& first, const cv::UMat& second, const cv::UMat& third)
{
	init(first, second, third);
}

cv::UMat ThreeFrameAX::run()
{
	cv::UMat filtered;
 
	cv::threshold(m_diff12, m_diff12, 50, 255, 0);
	cv::threshold(m_diff23, m_diff23, 50, 255, 0);
	cv::bitwise_and(m_diff12, m_diff23, m_and12);
	cv::bitwise_xor(m_diff23, m_and12, m_xor23); 
	cv::dilate(m_xor23, m_xor23, cv::getStructuringElement(cv::MORPH_ELLIPSE, { 7, 7 })); // CROSS or ELLIPSE

	//cv::blur(m_xor23, filtered, { 5, 5 });
	//cv::threshold(filtered, filtered, 50, 255, 0);
	//cv::bitwise_and(m_and12, m_xor23, and14);


	return m_xor23;
}
