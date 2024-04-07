#include "../headers/ThreeFrameDetector.h"

void ThreeFrameDetector::update(const cv::UMat& frame)
{
	m_currentFrame.copyTo(m_prevFrame);
	cv::cvtColor(frame, m_currentFrame, cv::COLOR_BGR2GRAY);

	m_diff23.copyTo(m_diff12);
	cv::absdiff(m_prevFrame, m_currentFrame, m_diff23);
}

void ThreeFrameDetector::init(const cv::UMat& first, const cv::UMat& second, const cv::UMat& third)
{
	cv::cvtColor(first, m_currentFrame, cv::COLOR_BGR2GRAY);
	cv::cvtColor(second, m_prevFrame, cv::COLOR_BGR2GRAY);
	cv::absdiff(m_currentFrame, m_prevFrame, m_diff12);
	cv::cvtColor(third, m_currentFrame, cv::COLOR_BGR2GRAY);
	cv::absdiff(m_prevFrame, m_currentFrame, m_diff23);
}
