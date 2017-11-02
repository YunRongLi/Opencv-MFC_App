#include "CCamCapture.h"

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

		m_heventThreadDone = CreateThread(NULL, 0, CCamCapture::threadGrabImage, NULL, 0, m_ThreadId);

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
	m_State = START;
}

//Finish
void CCamCapture::PauseCapture() {
	m_State = PAUSE;
}

//Finish
void CCamCapture::StopCapture() {
	m_State = STOP;
}

//Finish
CaptureState CCamCapture::GetCaptureState() const {
	return m_State;
}

//Finish
DWORD WINAPI CCamCapture::threadGrabImage(LPVOID pparam) {
	CCamCapture* pCapture = ((CCamCapture*)pparam);

	pCapture->doGrabLoop();
}

void CCamCapture::SetCaptureCallback(pfnCaptureCallback pfnCaptureCB) {
	cvSetMouseCallback("主畫面", onMouseCB, NULL);
}

void CCamCapture::doGrabLoop() {
	while (m_bCamInited) {
		if (m_State == START) {
			if (cvGrabFrame(m_pCapture)) {
				if (m_pImage = NULL) {
					IplImage* Image = NULL;
					IplImage* Image_mask = NULL;

					CvSize ImageSize = cvGetSize(m_pCapture);
					Image = cvCreateImage(ImageSize, IPL_DEPTH_8U, 3);
					Image = cvQueryFrame(m_pCapture);

					cvCopy(m_pImage, Image, Image_mask);

					onGrabLoop_DrawROI(m_pImage);

					if (m_bTargetObj) {

					}

				}
			}
		}
		else if (m_State == PAUSE) {

		}
		else if (m_State == STOP) {
			m_bCamInited = FALSE;
			cvReleaseImage(&m_pImage);
			cvReleaseImage(&m_pROI);
			//check Image had been release
		}
	}

	CloseHandle(m_heventThreadDone);
}

//Finish
void CCamCapture::onGrabLoop_cvInit() {
	m_pCapture = cvCaptureFromCAM(0);

	if (m_pCapture) {
		m_bCamInited = TRUE;
		CCamCapture::StartCapture();
		cvNamedWindow("主畫面", 0);
		cvNamedWindow("ROI畫面", 0);
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
		cvReleaseCapture(&m_pCapture);
	}
}

void CCamCapture::onMouseCB(int event, int x, int y, int flass, void* param) {
	if (event == CV_EVENT_LBUTTONDOWN) {
		m_Origin = cvPoint(x, y);
	}
	if (event == CV_EVENT_LBUTTONUP) {
		m_TargetRect = cvRect(m_Origin.x, m_Origin.y, x - m_Origin.x, y - m_Origin.y);
	}
}

void CCamCapture::onGrabLoop_DrawROI(IplImage* frame) {


}

IplImage* CCamCapture::GetSelectedROI() const {
	return m_pROI;
}

CvRect CCamCapture::GetTargetRect() const {
	return cvGetImageROI(m_pImage);
}

void CCamCapture::SetTargetRect(CvRect Rect) {
	cvSetImageROI(m_pImage, Rect);
}