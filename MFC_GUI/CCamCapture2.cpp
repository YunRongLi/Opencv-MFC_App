#include "stdafx.h"
#include "CCamCapture2.h"

cv::Mat   CCamCapture2::m_Image;
cv::Mat   CCamCapture2::m_ROI;
cv::Rect  CCamCapture2::m_TargetRect;
cv::Point CCamCapture2::m_Origin;
cv::Point CCamCapture2::m_MouseCurrentPoint;
    BOOL  CCamCapture2::m_bTargetObj;

CCamCapture2::CCamCapture2() {

}

CCamCapture2::~CCamCapture2() {
	m_cap.release();
}

//Finish
BOOL CCamCapture2::CreateCapture() {
	if (m_bCamInited) {
		return true;
	}
	else {
		if (m_heventThreadDone != NULL) {
			CloseHandle(m_heventThreadDone);
		}

		m_heventThreadDone = CreateThread(NULL, 0, CCamCapture2::threadGrabImage, this, 0, m_ThreadId);

		if (m_heventThreadDone == NULL) {
			return false;
		}
		else {
			return true;
		}
	}
}

void CCamCapture2::DestoryCapture() {
	if (m_bCamInited) {
		CCamCapture2::StopCapture();
		WaitForSingleObject(m_heventThreadDone, INFINITE);
	}
}

//Finish
void CCamCapture2::StartCapture() {
	m_State = STARTCAPTURE;
}

//Finish
void CCamCapture2::PauseCapture() {
	m_State = PAUSECAPTURE;
}

//Finish
void CCamCapture2::StopCapture() {
	m_State = STOPCAPTURE;
}

//Finish
CCaptureState CCamCapture2::GetCaptureState() const {
	return m_State;
}

//Finish
DWORD WINAPI CCamCapture2::threadGrabImage(LPVOID pparam) {
	CCamCapture2* pCapture = ((CCamCapture2*)pparam);

	pCapture->doGrabLoop();

	return 0;
}

void CCamCapture2::SetCaptureCallback(pfnCaptureCallback2 pfnCaptureCB) {
	cv::setMouseCallback("MainWindow", onMouseCB2, pfnCaptureCB);
}

void CCamCapture2::doGrabLoop() {
	onGrabLoop_cvInit();
	while (m_bCamInited) {
		if (m_State == STARTCAPTURE) {
			if (m_cap.grab() != NULL) {
				if (m_Image.empty()) {
					cv::Size ImageSize;
					ImageSize.width = m_cap.get(cv::CAP_PROP_FRAME_WIDTH);
					ImageSize.height = m_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
					m_Image.create(ImageSize, CV_8UC3);
				}
			}
			m_cap >> (m_Image);
			cvWaitKey(10);
			onGrabLoop_DrawROI(m_Image);
		}
		else if (m_State == PAUSECAPTURE) {

		}
		else if (m_State == STOPCAPTURE) {
			m_bCamInited = FALSE;
		}
	}
	onGrabLoop_cvClose();
	return;
}

//Finish
void CCamCapture2::onGrabLoop_cvInit() {
	m_cap.open(0);

	if (m_cap.isOpened()) {
		m_bCamInited = TRUE;
		CCamCapture2::StartCapture();
		cvNamedWindow("MainWindow", 1);
		cvNamedWindow("ROIWindow", 1);
		SetCaptureCallback(m_pfnCustomCB);
	}
	else {
		m_bCamInited = FALSE;
	}
}

//Finish
void CCamCapture2::onGrabLoop_cvClose() {
	if (m_cap.isOpened()) {
		m_cap.release();

		cvDestroyWindow("MainWindow");
		cvDestroyWindow("ROIWindow");
	}
}

void CCamCapture2::onMouseCB2(int event, int x, int y, int flass, void* param) {
	if (event == CV_EVENT_MOUSEMOVE) {
		m_MouseCurrentPoint = cv::Point(x, y);
	}

	if (event == CV_EVENT_LBUTTONDOWN) {
		m_Origin = cv::Point(x, y);
		m_bTargetObj = TRUE;
	}
	if (event == CV_EVENT_LBUTTONUP) {
		m_bTargetObj = FALSE;
		if (abs(x - m_Origin.x) > 5 && abs(y - m_Origin.y) > 5) {
		/*	int width = abs(x - m_Origin.x);
			if (width > 680) {
				width = 680 - m_Origin.x;
			}
			int height = abs(y - m_Origin.y);
			if (height > 480) {
				height = 480 - m_Origin.y;
			}*/
			m_TargetRect = cv::Rect(m_Origin.x, m_Origin.y, abs(x - m_Origin.x), abs(y - m_Origin.y));

			cv::Size Size = cv::Size(m_TargetRect.width, m_TargetRect.height);
			m_ROI.create(m_Image.size(), m_Image.type());
			
			m_Image.copyTo(m_ROI);
		 
			cv::Mat mask = m_ROI(m_TargetRect);
			
			cv::imshow("ROIWindow", mask);

		}
	}
}

//Finish
void CCamCapture2::onGrabLoop_DrawROI(cv::Mat &frame) {
	//CvRect targetRect = GetTargetRect();
	if (m_bTargetObj == TRUE) {
		cv::rectangle(frame, m_Origin, m_MouseCurrentPoint, CV_RGB(255, 0, 0), 5);
		cv::imshow("MainWindow", frame);
	}
	else {
		cv::imshow("MainWindow", frame);
	}
}

cv::Mat  CCamCapture2::GetSelectedROI() const {
	return m_ROI;
}

cv::Rect CCamCapture2::GetTargetRect() const {
	return m_TargetRect;
}

void CCamCapture2::SetTargetRect(cv::Rect Rect) {
	m_Image(Rect);
}