// OpencvTest.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2\core\core_c.h>


int main()
{
	CvCapture* Camcapture = cvCaptureFromCAM(0);
	IplImage* m_IplImage;
	IplImage* m_second;
	IplImage* mask;

	char key;

	cvNamedWindow("Main", 1);
	cvNamedWindow("Second", 0);


	while (true) {
		m_IplImage = cvQueryFrame(Camcapture);
		CvSize size = cvSize(100, 100);
		m_second = cvCreateImage(size, m_IplImage->depth, m_IplImage->nChannels);
		mask = cvCreateImage(cvGetSize(m_IplImage), m_IplImage->depth, m_IplImage->nChannels);

		cvShowImage("Main", m_IplImage);

		CvRect Rect = cvRect(10, 10, 100, 100);
		cvSetImageROI(m_IplImage, Rect);

		cvCopy(m_IplImage, m_second, NULL);

		cvWaitKey(10);

		cvShowImage("Second", m_IplImage);
		cvResetImageROI(m_IplImage);

		key = cvWaitKey(10);

		if (key == 27) {
			break;
		}
	}
	cvReleaseImage(&m_IplImage);
	//cvReleaseCapture(&Camcapture);
	cvDestroyWindow("Main");

    return 0;
}

