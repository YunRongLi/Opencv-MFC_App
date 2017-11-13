#pragma once

#include <opencv\cv.h>
#include <opencv\highgui.h>

#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>

typedef enum {
	STARTCAPTURE,
	PAUSECAPTURE,
	STOPCAPTURE
}CCaptureState;

class CCamCapture {
	typedef void(__cdecl *pfnCaptureCallback)(IplImage);

private:
	static void onMouseCB(int event, int x, int y, int flags, void* param);
	void onGrabLoop_DrawROI(IplImage* frame);    //Draw¡@ROI Image

	static IplImage*   m_pImage;
	static IplImage*   m_pROI;
	static CvRect      m_TargetRect;
	static CvPoint     m_Origin;
	static CvPoint  m_MouseCurrentPoint;

	CvCapture*         m_pCapture;
	pfnCaptureCallback m_pfnCustomCB;

protected:
	static DWORD WINAPI threadGrabImage(LPVOID pparam);

	virtual void doGrabLoop();
	virtual void onGrabLoop_cvInit();
	virtual void onGrabLoop_cvClose();

	BOOL m_bCamInited;          //Camera initial flag

	LPDWORD m_ThreadId;
	HANDLE m_heventThreadDone;

	CCaptureState m_State;

	static BOOL m_bTargetObj;

public:
	CCamCapture();
	~CCamCapture();

	BOOL CreateCapture();

	void DestoryCapture();

	void StartCapture();
	void PauseCapture();
	void StopCapture();

	CCaptureState   GetCaptureState() const;
	IplImage*       GetSelectedROI()  const;
	CvRect          GetTargetRect()   const;

	void SetTargetRect(CvRect Rect);
	void SetCaptureCallback(pfnCaptureCallback pfnCaptureCB);
};