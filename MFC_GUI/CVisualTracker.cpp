#include "stdafx.h"
#include "CVisualTracker.h"

CVisualTracker::CVisualTracker() {

}

CVisualTracker::~CVisualTracker() {

}

BOOL CVisualTracker::TrackingByTempMatching(cv::Mat& frame, cv::Rect &TrackRect) {
	cv::Mat Frame;
	frame.copyTo(Frame);


	if (GetROI() != NULL) {
		return false;
	}

	int result_cols = Frame.cols - m_pROI->cols + 1;
	int result_rows = Frame.rows - m_pROI->rows + 1;

	cv::Mat result;
	cv::Mat templ;

	result.create(result_rows, result_cols,  Frame.type());

	//cv::matchTemplate(frame, &GetROI(), result, );

	return true;
}

void CVisualTracker::SetMethodType(VT_Method_Type Type) {
	m_CurType = Type;
}

VT_Method_Type CVisualTracker::GetMethodType() const {
	return m_CurType;
}

void CVisualTracker::SetVT_Params(VT_Method_Type Type, VT_Params Param) {

}

VT_Params CVisualTracker::GetVT_Params() const {
	return m_CurParams;
}

void CVisualTracker::SetROI(cv::Mat* pROI) {
	m_pROI = pROI;
}

cv::Mat* CVisualTracker::GetROI() const {
	return m_pROI;
}

BOOL CVisualTracker::Tracking(cv::Mat &Frame, cv::Rect &TrackRect) {
	return true;
}

void CVisualTracker::ShowResult(cv::Mat &Frame, cv::Rect &TrackRect) {

}


