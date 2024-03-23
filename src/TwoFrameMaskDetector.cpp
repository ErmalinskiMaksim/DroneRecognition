#include "../headers/TwoFrameMaskDetector.h"
#include "opencv2/imgproc.hpp"

TwoFrameMaskDetector::TwoFrameMaskDetector(const cv::Mat& staticMask, const cv::Mat& dynamicMask)
	: m_dynamicDiff{}, m_staticDiff{}
{
	cv::cvtColor(staticMask, m_staticMask, cv::COLOR_BGR2GRAY);
	cv::cvtColor(dynamicMask, m_dynamicMask, cv::COLOR_BGR2GRAY);
}

cv::Mat TwoFrameMaskDetector::run(const cv::Mat& frame)
{
	cv::Mat frameGray;
	cv::Mat filtered;
	cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);
	cv::absdiff(m_staticMask, frameGray, m_staticDiff);
	cv::threshold(m_staticDiff, m_staticDiff, 100, 250, 0);

	cv::absdiff(m_dynamicMask, frameGray, m_dynamicDiff);
	frameGray.copyTo(m_dynamicMask);

	cv::multiply(m_staticDiff, m_dynamicDiff, filtered);
	//cv::GaussianBlur(frameGray, frame, { 11, 11 }, 0);
	cv::threshold(filtered, filtered, 50, 250, 0);
	//cv::threshold(m_dynamicDiff, m_dynamicDiff, 50, 250, 0);
	return filtered;
}

TwoFrameMaskDetector::~TwoFrameMaskDetector()
{
	m_dynamicDiff.release();
	m_staticDiff.release();
	m_dynamicMask.release();
	m_staticMask.release();
}
