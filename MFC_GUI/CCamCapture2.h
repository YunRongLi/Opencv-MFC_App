#pragma once

#include <opencv2\opencv.hpp>

#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>

#include "CCamCapture.h"


class CCamCapture2 : public CCamCapture {
	typedef void(__cdecl *pfnCaptureCallback2)(cv::Mat& Frame);

private:
	static void onMouseCB2(int event, int x, int y, int flags, void* param);
	void onGrabLoop_DrawROI(cv::Mat& frame);    //Draw¡@ROI Image

	static cv::Mat   m_Image;
	static cv::Mat   m_ROI;
	static cv::Rect  m_TargetRect;
	static cv::Point m_Origin;
	static cv::Point m_MouseCurrentPoint;

	cv::VideoCapture    m_cap;
	pfnCaptureCallback2 m_pfnCustomCB;

	static int  m_SelectState;
		   

protected:
	static DWORD WINAPI threadGrabImage(LPVOID pparam);

	virtual void doGrabLoop();
	virtual void onGrabLoop_cvInit();
	virtual void onGrabLoop_cvClose();

	static BOOL m_bTargetObj;
public:
	CCamCapture2();
	~CCamCapture2();

	BOOL CreateCapture();

	void DestoryCapture();

	void StartCapture();
	void PauseCapture();
	void StopCapture();

	CCaptureState     GetCaptureState() const;
	cv::Mat           GetSelectedROI()  const;
	cv::Rect          GetTargetRect()   const;

	void SetTargetRect(cv::Rect Rect);
	void SetCaptureCallback(pfnCaptureCallback2 pfnCaptureCB);
};
