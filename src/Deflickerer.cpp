#include "../headers/Deflickerer.h"

cv::Mat Deflickerer::run(cv::Mat img, int cutOffStrength = 20)
{
	//check if we stored a previous frame of this name. if not, theres nothing we can do. clone and exit
	if (m_prev.rows)  
	{
		uchar* p;
		uchar* prevp;
		for (int i = 0; i < img.rows; ++i)
		{
			p = img.ptr<uchar>(i);
			prevp = m_prev.ptr<uchar>(i);
			for (int j = 0; j < img.cols; ++j) {

				cv::Scalar previntensity = prevp[j];
				cv::Scalar intensity = p[j];
				int strength = abs(intensity.val[0] - previntensity.val[0]);

				if (strength < cutOffStrength) { //the strength of the stimulus must be greater than a certain point, else we do not want to allow the change
					//value 25 works good for medium+ light.  anything higher creates too much blur around moving objects. 
					//in low light however this makes it worse, since low light seems to increase contrasts in flicker - some flickers go from 0 to 255 and back.  :(
					//I need to write a way to track large group movements vs small pixels, and only filter out the small pixel stuff.  maybe blur first?

					if (intensity.val[0] > previntensity.val[0]) {  // use the previous frames value.  Change it by +1 - slow enough to not be noticable flicker
						p[j] = previntensity.val[0] + 1;
					}
					else {
						p[j] = previntensity.val[0] - 1;
					}
				}

			}

		}
	}
	img.copyTo(m_prev);
	return img;
}
