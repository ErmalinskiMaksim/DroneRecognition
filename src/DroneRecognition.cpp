// DroneRecognition.cpp : Defines the entry point for the application.
//
#include "../headers/DroneRecognition.h"
#include "opencv2/tracking.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/bioinspired.hpp"

class SmartTracker
{
public:
	SmartTracker(const cv::Mat& frame) : /*m_Retina{cv::bioinspired::Retina::create(frame.size())},*/m_tracker{cv::TrackerKCF::create()}, m_detector(frame, frame, frame)
	{
		//retina parameters management methods use sample
		  //-> save current (here default) retina parameters to a xml file (you may use it only one time to get the file and modify it)
		//m_Retina->write("RetinaDefaultParameters.xml");
		// -> load parameters if file exists
		//m_Retina->setup("RetinaSpecificParameters.xml");
		//reset all retina buffers (open your eyes)  
		//m_Retina->clearBuffers();
	}
	void run(cv::Mat& frame, cv::Mat& outputFrame)
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
	//TwoFrameMaskDetector m_detector;
	//cv::Mat m_retinaBuffer{};
	//cv::Mat m_diffBuff{};
	cv::Rect m_roi;
	bool m_captured = false;
	bool isFirstCapture = true;
};

int main()
{
	cv::Mat frame;
	
	cv::Mat filtered;
	cv::VideoCapture videoCapture("test_data/2024-02-28 20-10-56.mkv");

	/*int frameWidth = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
	int frameHeight = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
	cv::VideoWriter output("TwoFrame.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(frameWidth, frameHeight));*/
	//SmartTracker tracker(frame);

	videoCapture >> frame;
	//ThreeFrameAX analyser(first, second, third);
	ThreeFrameOO analyser(frame, frame, frame);
	ContoursFinder cf;
	//TwoFrameMaskDetector detector(third, third);
	//Benchmark benchmark;
	//main processing loop
	while (videoCapture.read(frame))
	{
		analyser.update(frame);
		//benchmark.start();
		filtered = analyser.run();
		//filtered = analyser.run();
		//benchmark.reset();
			
		cf.drawContours(filtered, frame);
		////tracker.run(frameGray, frame);
		//cv::imshow("filtered", filtered);

		//output << third;
		cv::imshow("Output", frame);
		cv::waitKey(5);
	}
	//benchmark.write("twoFrame.txt");
	videoCapture.release();
	//output.release();
	cv::destroyAllWindows();
}

