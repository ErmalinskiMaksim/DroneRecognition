// DroneRecognition.cpp : Defines the entry point for the application.
//
#include "../headers/DroneRecognition.h"
#include "opencv2/tracking.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/bioinspired.hpp"
#include <chrono>

class SmartTracker
{
public:
	SmartTracker(const cv::Mat& frame) : m_Retina{ cv::bioinspired::Retina::create(frame.size()) }, m_tracker{ cv::TrackerKCF::create() }, m_static(frame), m_dynamic(frame)
	{
		//retina parameters management methods use sample
		  //-> save current (here default) retina parameters to a xml file (you may use it only one time to get the file and modify it)
		m_Retina->write("RetinaDefaultParameters.xml");
		// -> load parameters if file exists
		m_Retina->setup("RetinaSpecificParameters.xml");
		//reset all retina buffers (open your eyes)  
		m_Retina->clearBuffers();
	}
	void run(cv::Mat& frame, cv::Mat& outputFrame)
	{
		//if (m_captured)
		//{
		//	//cv::Ptr<cv::Tracker> tracker = cv::TrackerKCF::create();
		//	if (isFirstCapture) {
		//		m_tracker->init(frame, m_roi);
		//		isFirstCapture = false;
		//	}
		//	if (m_tracker->update(frame, m_roi))
		//		cv::rectangle(frame, m_roi, cv::Scalar(255, 0, 0), 2, 8);
		//	else
		//	{
		//		m_captured = false;
		//		m_roi = {};
		//	}
		//}
		//else
		{

			//cv::bilateralFilter(frameGray, frame, 9, 50, 50);
			//cv::GaussianBlur(frameGray, frame, { 11, 11 }, 0);

			//m_static.getDifference(frame);
			//m_static.thresholdBuffer(100, 255, 0);

			//// get dynamic difference
			//m_dynamic.getDifference(frame);
			//m_dynamic.setMask(frame);
			//cv::multiply(m_static.getBuffer(), m_dynamic.getBuffer(), m_diffBuff);

			//// run retina on the input image
			//m_Retina->run(frame);
			////grab retina outputs
			//m_Retina->getMagno(m_retinaBuffer);
			//cv::threshold(m_retinaBuffer, m_retinaBuffer, 100, 255, 0);
			//cv::multiply(m_diffBuff, m_retinaBuffer, m_diffBuff);
			//// draw retina outputs

			////cv::GaussianBlur(differenceGray, blur, { 5,5 }, 0);
			////cv::threshold(blur, threshold, 20, 255, cv::THRESH_BINARY);
			//cv::threshold(m_diffBuff, m_diffBuff, 20, 255, cv::THRESH_BINARY);
			//cv::dilate(threshold, dialated, cv::Mat());

			//cv::findContours(m_diffBuff, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
			//analiseContours(frame);
		}
	}

	~SmartTracker() { m_tracker.release(); m_Retina.release(); }
private:

	cv::Ptr<cv::bioinspired::Retina> m_Retina;
	cv::Ptr<cv::Tracker> m_tracker;
	TwoFrameMaskDetector m_static;
	TwoFrameMaskDetector m_dynamic;
	cv::Mat m_retinaBuffer{};
	cv::Mat m_diffBuff{};
	bool m_captured = false;
	//bool isFirstCapture = true;
};

int main()
{
	cv::Mat first;
	cv::Mat second;
	cv::Mat third;

	cv::Mat filtered;
	cv::VideoCapture videoCapture(0);

	//int frameWidth = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
	//int frameHeight = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
	////cv::VideoWriter output("output.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(frameWidth, frameHeight));
	//SmartTracker tracker(frame);

	videoCapture >> first;
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	videoCapture >> second;
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	videoCapture >> third;

	//ThreeFrameAX analyser(first, second, third);
	ThreeFrameOO analyser(first, second, third);
	ContoursFinder cf;

	//main processing loop
	while (videoCapture.read(third))
	{
		analyser.update(third);
		filtered = analyser.run();

		cf.drawContours(filtered, third);
		////tracker.run(frameGray, frame);
		cv::imshow("filtered", filtered);
		cv::imshow("Retina Magno", third);
		cv::waitKey(5);
	}

	videoCapture.release();
	cv::destroyAllWindows();
}

