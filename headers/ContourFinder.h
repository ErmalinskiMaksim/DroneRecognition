#pragma once
#ifndef CONTOURS_FINDER
#define CONTOURS_FINDER
#include <vector>
#include "opencv2/core/mat.hpp"

class ContoursFinder
{
public:
	void drawContours(const cv::Mat& gray, cv::Mat& output);
private:
	cv::Rect m_roi{};
	std::vector<std::vector<cv::Point>> m_contours{};
	std::vector<cv::Vec4i> m_hierarchy{};
};
#endif // !CONTOURS_FINDER

