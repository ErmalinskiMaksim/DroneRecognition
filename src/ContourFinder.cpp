#include "../headers/ContourFinder.h"
#include "opencv2/opencv.hpp"

bool ContoursFinder::drawContours(const cv::UMat& gray, cv::UMat& output)
{
	//cv::UMat empty(gray.rows, gray.cols, CV_8UC3, 0);
	//cv::UMat emptyGray(gray.rows, gray.cols, CV_8UC1, 0);
	cv::findContours(gray, m_contours, m_hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	//// find contours again
	//for (auto&& a : m_contours)
	//{
	//	auto rect = cv::boundingRect(a);
	//	cv::rectangle(empty, rect.tl(), rect.br(), { 0, 0, 255 }, cv::FILLED);
	//}
	//cv::imshow("1", empty);
	//cv::cvtColor(empty, emptyGray, cv::COLOR_BGR2GRAY);
	//cv::findContours(emptyGray, m_contours, m_hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	//for (auto&& a : m_contours)
	//{
	//	auto rect = cv::boundingRect(a);
	//	cv::rectangle(empty, rect.tl(), rect.br(), { 0, 0, 255 }, cv::FILLED);
	//}
	//cv::imshow("2", empty);
	//cv::cvtColor(empty, emptyGray, cv::COLOR_BGR2GRAY);
	//cv::findContours(emptyGray, m_contours, m_hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (auto&& a : m_contours)
	{
		auto rect = cv::boundingRect(a);
		cv::rectangle(output, rect.tl(), rect.br(), { 0, 0, 255 });
	}
	return !m_contours.empty();
}

const cv::Rect& ContoursFinder::getROI() const
{
	return m_roi;
}
