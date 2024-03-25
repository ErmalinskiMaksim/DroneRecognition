#include "../headers/ContourFinder.h"
#include "opencv2/opencv.hpp"

bool ContoursFinder::drawContours(const cv::Mat& gray, cv::Mat& output)
{
	cv::findContours(gray, m_contours, m_hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	if (!m_contours.empty())
	{
		double maxArea = cv::contourArea(m_contours[0]);
		double area = maxArea;
		for (auto&& a : m_contours)
		{
			auto rect = cv::boundingRect(a);
			area = cv::contourArea(a);
			cv::rectangle(output, rect.tl(), rect.br(), { 0, 0, 255 });
			if (area >= maxArea)
			{
				m_roi = rect;
				maxArea = area;
			}
		}
		cv::rectangle(output, m_roi.tl(), m_roi.br(), { 0, 0, 255 });
		return true;
	}
	else return false;
}

const cv::Rect& ContoursFinder::getROI() const
{
	return m_roi;
}
