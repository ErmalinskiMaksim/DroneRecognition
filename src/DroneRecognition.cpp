// DroneRecognition.cpp : Defines the entry point for the application.
//
#include "../headers/DroneRecognition.h"
#include "opencv2/tracking.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/bioinspired.hpp"

class SmartTracker // : public cv::DetectionBasedTracker::IDetector
{
public:
	SmartTracker(const cv::UMat& frame) : /*m_Retina{cv::bioinspired::Retina::create(frame.size())},*/m_tracker{cv::TrackerKCF::create()}, m_detector(frame, frame, frame), m_roi{0, 0, 1, 1}
	{
		//retina parameters management methods use sample
		  //-> save current (here default) retina parameters to a xml file (you may use it only one time to get the file and modify it)
		//m_Retina->write("RetinaDefaultParameters.xml");
		// -> load parameters if file exists
		//m_Retina->setup("RetinaSpecificParameters.xml");
		//reset all retina buffers (open your eyes)  
		//m_Retina->clearBuffers();
	}
	void run(cv::UMat& frame)
	{
		if (m_captured)
		{
			if (isFirstCapture) {
				m_tracker->init(frame, m_roi);
				isFirstCapture = false;
			}
			m_captured = m_tracker->update(frame, m_roi);
			if (m_captured)
				cv::rectangle(frame, m_roi, cv::Scalar(255, 0, 0), 2, 8);
		}
		else
		{
			m_detector.update(frame);
			auto filtered = m_detector.run();
			if (m_cf.drawContours(filtered, frame))
			{
				m_roi = m_cf.getROI();
				m_captured = true;
			}
			//// run retina on the input image
			//m_Retina->run(frame);
			////grab retina outputs
			//m_Retina->getMagno(m_retinaBuffer);
			//cv::threshold(m_retinaBuffer, m_retinaBuffer, 100, 255, 0);
			//cv::multiply(m_diffBuff, m_retinaBuffer, m_diffBuff);
			//// draw retina outputs

		}
	}

	~SmartTracker() { m_tracker.release(); //m_Retina.release();
	}
private:

	//cv::Ptr<cv::bioinspired::Retina> m_Retina;
	cv::Ptr<cv::Tracker> m_tracker;
	ThreeFrameOO m_detector;
	ContoursFinder m_cf;
	//cv::Mat m_retinaBuffer{};
	cv::Rect m_roi;
	bool m_captured = false;
	bool isFirstCapture = true;
};

int main()
{
	cv::VideoCapture videoCapture("test_data/LED.mkv");
	const int frameWidth = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
	const int frameHeight = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
	//cv::VideoWriter output("rendered/led.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, { frameWidth, frameHeight });

	cv::UMat frame(frameWidth, frameHeight, CV_8UC1);
	cv::UMat filtered(frameWidth, frameHeight, CV_8UC1);
	cv::UMat ff(frameWidth, frameHeight, CV_8UC1);
	
	videoCapture >> frame;
	ThreeFrameOO analyser(frame, frame, frame);
	ContoursFinder cf;

	//main processing loop
	while (videoCapture.read(frame))
	{
		analyser.update(frame);
		filtered = analyser.run();
		cf.drawContours(filtered, frame);
		//tracker.run(frame);
		
		//output << frame;
		cv::imshow("Output", frame);
		cv::waitKey(5);
	}
	videoCapture.release();
	//output.release();
	cv::destroyAllWindows();
}

