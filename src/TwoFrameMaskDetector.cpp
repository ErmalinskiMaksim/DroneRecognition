#include "../headers/TwoFrameMaskDetector.h"
#include "opencv2/imgproc.hpp"

TwoFrameMaskDetector::TwoFrameMaskDetector(const cv::Mat& mask)
	: m_buffer{}
{
	cv::Mat gray;
	cv::cvtColor(mask, gray, cv::COLOR_BGR2GRAY);
	cv::bilateralFilter(gray, m_mask, 9, 50, 50);
}

const cv::Mat& TwoFrameMaskDetector::getBuffer() const
{
	return m_buffer;
}

void TwoFrameMaskDetector::setMask(const cv::Mat& mask)
{
	m_mask.release();
	mask.copyTo(m_mask);
}

void TwoFrameMaskDetector::thresholdBuffer(double sigma1, double sigma2, int type)
{
	cv::threshold(m_buffer, m_buffer, sigma1, sigma2, type);
}

void TwoFrameMaskDetector::getDifference(const cv::Mat& mask)
{
	m_buffer.release();
	cv::absdiff(m_mask, mask, m_buffer);
}

TwoFrameMaskDetector::~TwoFrameMaskDetector()
{
	m_buffer.release(); m_mask.release();
}
