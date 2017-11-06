#include "stdafx.h"
#include "CCamCapture.h"

IplImage* CCamCapture::m_pImage = NULL;
IplImage* CCamCapture::m_pROI = NULL;
CvRect CCamCapture::m_TargetRect = NULL;
CvPoint CCamCapture::m_Origin = NULL;
CvPoint CCamCapture::m_MouseCurrentPoint = NULL;
BOOL CCamCapture::m_bTargetObj = NULL;

CCamCapture::CCamCapture() {

}

CCamCapture::~CCamCapture() {

}

//Finish
BOOL CCamCapture::CreateCapture() {
	if (m_bCamInited) {
		return true;
	}
	else {
		if (m_heventThreadDone != NULL) {
			CloseHandle(m_heventThreadDone);
		}

		m_heventThreadDone = CreateThread(NULL, 0, CCamCapture::threadGrabImage, this, 0, m_ThreadId);

		if (m_heventThreadDone == NULL) {
			return false;
		}
		else {
			return true;
		}
	}
}

void CCamCapture::DestoryCapture() {
	if (m_bCamInited) {
		CCamCapture::StopCapture();
		WaitForSingleObject(m_heventThreadDone, INFINITE);
	}
}

//Finish
void CCamCapture::StartCapture() {
	m_State = STARTCAPTURE;
}

//Finish
void CCamCapture::PauseCapture() {
	m_State = PAUSECAPTURE;
}

//Finish
void CCamCapture::StopCapture() {
	m_State = STOPCAPTURE;
}

//Finish
CCaptureState CCamCapture::GetCaptureState() const {
	return m_State;
}

//Finish
DWORD WINAPI CCamCapture::threadGrabImage(LPVOID pparam) {
	CCamCapture* pCapture = ((CCamCapture*)pparam);

	pCapture->doGrabLoop();

	return 0;
}

void CCamCapture::SetCaptureCallback(pfnCaptureCallback pfnCaptureCB) {
	cvSetMouseCallback("MainWindow", onMouseCB, pfnCaptureCB);
}

void CCamCapture::doGrabLoop() {
	onGrabLoop_cvInit();
	while (m_bCamInited) {
		if (m_State == STARTCAPTURE) {
			if (cvGrabFrame(m_pCapture) != NULL) {	
				if(m_pImage == NULL){
					CvSize ImageSize;
					ImageSize.width  = cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_FRAME_WIDTH);
					ImageSize.height = cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_FRAME_HEIGHT);
					m_pImage = cvCreateImage(ImageSize, IPL_DEPTH_8U, 3);
					//cvAddS(m_pImage, CV_RGB(255, 255, 255), m_pImage, NULL);
				}
				cvRetrieveFrame(m_pCapture);
			}
			m_pImage = cvQueryFrame(m_pCapture); //
			cvWaitKey(10);
			onGrabLoop_DrawROI(m_pImage);	
		}
		else if (m_State == PAUSECAPTURE) {
			
		}
		else if (m_State == STOPCAPTURE) {
			m_bCamInited = FALSE;
			onGrabLoop_cvClose();
			//check Image had been release
		}
	}
	return;
}

//Finish
void CCamCapture::onGrabLoop_cvInit() {
	m_pCapture = cvCaptureFromCAM(0);

	if (m_pCapture) {
		m_bCamInited = TRUE;
		CCamCapture::StartCapture();
		cvNamedWindow("MainWindow", 1);
		cvNamedWindow("ROIWindow", 1);
		SetCaptureCallback(m_pfnCustomCB);
	}
	else {
		m_bCamInited = FALSE;
	}
}

//Finish
void CCamCapture::onGrabLoop_cvClose() {
	if (m_pCapture != NULL || m_pImage != NULL || m_pROI != NULL) {
		cvReleaseImage(&m_pImage);
		cvReleaseImage(&m_pROI);

		//cvReleaseCapture(&m_pCapture);
		
		cvDestroyWindow("MainWindow");
		cvDestroyWindow("ROIWindow");
	}
}

void CCamCapture::onMouseCB(int event, int x, int y, int flass, void* param) {
	if (event == CV_EVENT_MOUSEMOVE) {
		m_MouseCurrentPoint = cvPoint(x, y);
	}

	if (event == CV_EVENT_LBUTTONDOWN) {
		m_Origin = cvPoint(x, y);
		m_bTargetObj = TRUE;
	}
	if (event == CV_EVENT_LBUTTONUP) {
		m_bTargetObj = FALSE;
		if(abs(x - m_Origin.x) > 10 && abs(y - m_Origin.y)){
			if (m_TargetRect.x != 0 || m_TargetRect.y != 0 || m_TargetRect.width != 0 || m_TargetRect.height != 0) {
				cvSetImageROI(m_pImage, NULL);
			}
			m_TargetRect = cvRect(m_Origin.x, m_Origin.y, abs(x - m_Origin.x), abs(y - m_Origin.y));

			CvSize Size = cvSize(m_TargetRect.width, m_TargetRect.height);
			IplImage* mask = cvCreateImage(Size, m_pImage->depth, m_pImage->nChannels);
			m_pROI = cvCreateImage(Size, m_pImage->depth, m_pImage->nChannels);
			//m_pROI Size of image equal m_pImage size of ROI.
			cvSetImageROI(m_pImage, m_TargetRect);

			cvCopy(m_pImage, m_pROI, mask);
			cvShowImage("ROIWindow", m_pROI);

			cvResetImageROI(m_pImage);
			cvReleaseImage(&m_pROI);
			cvReleaseImage(&mask);
		}
	}
}

//Finish
void CCamCapture::onGrabLoop_DrawROI(IplImage* frame) {
	CvRect targetRect = GetTargetRect();
	if (m_bTargetObj == TRUE) {
		cvRectangle(frame, m_Origin, m_MouseCurrentPoint, CV_RGB(255,0,0),5);
		cvShowImage("MainWindow", frame);
		//cvReleaseImage(&frame);
	}
	else{
		cvShowImage("MainWindow",frame);
	}
}

IplImage* CCamCapture::GetSelectedROI() const {
	return m_pROI;
}

CvRect CCamCapture::GetTargetRect() const {
	return m_TargetRect;
}

void CCamCapture::SetTargetRect(CvRect Rect) {
	cvSetImageROI(m_pImage, Rect);
}