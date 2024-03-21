#include "../headers/ContourFinder.h"
#include "opencv2/opencv.hpp"

void ContoursFinder::drawContours(const cv::Mat& gray, cv::Mat& output)
{
	cv::findContours(gray, m_contours, m_hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

	if (!m_contours.empty())
	{
		double maxArea = cv::contourArea(m_contours[0]);
		for (auto&& a : m_contours)
		{
			auto rect = cv::boundingRect(a);
			double area = cv::contourArea(a);
			cv::rectangle(output, rect.tl(), rect.br(), { 255, 0, 0 });
			if (area > maxArea)
			{
				m_roi = rect;
				maxArea = area;
			}
		}
		cv::rectangle(output, m_roi.tl(), m_roi.br(), { 255, 0, 0 });
	}
}
