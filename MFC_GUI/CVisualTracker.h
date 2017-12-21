#pragma once

#include <opencv2\opencv.hpp>

#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>

enum TempMatchParam {
	TM_SQDIFF = CV_TM_SQDIFF, TM_SQDIFF_NORMED, TM_CCORR, TM_CCORR_NORMED, TM_CCOEFF, TM_CCOEFF_NORMED
};

enum VT_Method_Type {
	TemplateMatch = 1, MeanShift, CAMShift
};

typedef struct {
	int vmin;
	int vmax;
}MeanShiftParam;

typedef struct {
	int vmin;
	int vmax;
	int smin;
}CamShiftParam;

typedef struct {
	TempMatchParam TM_Param;
	MeanShiftParam MS_Param;
	CamShiftParam  CS_Param;
}VT_Params;

class CVisualTracker {
private:
	BOOL TrackingByTempMatching(cv::Mat &Frame, cv::Rect &TrackRect);
	VT_Method_Type m_CurType;
	VT_Params m_CurParams;
	TempMatchParam  m_CurTMMethod;
	cv::Mat* m_pROI;
	
public:
	CVisualTracker();
	~CVisualTracker();

	void SetMethodType(VT_Method_Type);
	VT_Method_Type GetMethodType() const;

	void SetVT_Params(VT_Method_Type Type, VT_Params Param);
	VT_Params GetVT_Params() const;

	void SetROI(cv::Mat* pROI);
	cv::Mat* GetROI() const;

	BOOL Tracking(cv::Mat &Frame, cv::Rect &TrackRect);
	void ShowResult(cv::Mat &Frame, cv::Rect &TrackRect);
};
