#include "stdafx.h"
#include "CVisualTracker.h"

CVisualTracker::CVisualTracker() {

}

CVisualTracker::~CVisualTracker() {

}

BOOL CVisualTracker::TrackingByTempMatching(cv::Mat& frame, cv::Rect &TrackRect) {
	cv::Mat templ;
	
	cv::Point MaxPoint;
	cv::Point MinPoint;

	double MaxVal;
	double MinVal;

	if (GetROI() == NULL) {
		return false;
	}
	
	int result_cols = frame.cols - TrackRect.width + 1;
	int result_rows = frame.rows - TrackRect.height + 1;

	cv::Mat result;
	cv::Mat result_normalize;

	result.create(result_rows, result_cols,  frame.type());

	templ = *m_pROI;

	cv::matchTemplate(frame, templ, result, GetVT_Params().TM_Param);

	//result.convertTo(result_normalize, CV_8UC1, 255.0, 0.0);

	cv::minMaxLoc(result, &MinVal, &MaxVal, &MinPoint, &MaxPoint, cv::noArray());

	if (m_CurParams.TM_Param == cv::TM_SQDIFF || m_CurParams.TM_Param == cv::TM_SQDIFF_NORMED) {
		TrackRect.x = MinPoint.x;
		TrackRect.y = MinPoint.y;
	}
	else {
		TrackRect.x = MaxPoint.x;
		TrackRect.y = MaxPoint.y;
	}

	return true;
}

BOOL CVisualTracker::TrackingByMeanShift(cv::Mat &Frame, cv::Rect &TrackRect) {
	if (GetROI() == NULL) {
		return false;
	}

	m_vmin = GetVT_Params().MS_Param.vmin;
	m_vmax = GetVT_Params().MS_Param.vmax;
	m_smin = 30;

	ImgHueExtraction(Frame);

}

void CVisualTracker::SetMethodType(VT_Method_Type Type) {
	m_CurType = Type;
}

VT_Method_Type CVisualTracker::GetMethodType() const {
	return m_CurType;
}

void CVisualTracker::SetVT_Params(VT_Method_Type Type, VT_Params Param) {
	switch (Type) {
	case VT_Method_Type::TemplateMatch:
		m_CurParams.TM_Param = Param.TM_Param;
		break;
	case VT_Method_Type::CAMShift:
		m_CurParams.CS_Param = Param.CS_Param;
		break;
	case VT_Method_Type::MeanShift: 
		m_CurParams.MS_Param = Param.MS_Param;
		break;
	default:
		break;
	}
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
	return TrackingByTempMatching(Frame, TrackRect);
}

void CVisualTracker::ShowResult(cv::Mat &Frame, cv::Rect &TrackRect) {
	cv::rectangle(Frame, TrackRect, CV_RGB(255, 0, 0), 1, 8, 0);
	cv::imshow("MainWindow", Frame);
}


void CVisualTracker::ImgHueExtraction(cv::Mat &Frame) {
	cv::Mat r, r2, b, g;

	cv::cvtColor(Frame, m_hsv, CV_BGR2HSV);
	
	cv::inRange(m_hsv, cv::Scalar(0, m_smin, m_vmin), cv::Scalar(10, 255, m_vmax), r);

	cv::inRange(m_hsv, cv::Scalar(170, m_smin, m_vmin), cv::Scalar(180, 255, m_vmax), r2);

	cv::inRange(m_hsv, cv::Scalar(50, m_smin, m_vmin), cv::Scalar(70, 255, m_vmax), b);

	cv::inRange(m_hsv, cv::Scalar(110, m_smin, m_vmin), cv::Scalar(130, 255, m_vmax), g);

	m_mask = r + r2 + b + g;

	m_hue.create(m_hsv.size(), m_hsv.type());

	int from_to[] = { 0,0 };

	cv::mixChannels(m_hsv, m_hue, from_to, 1);
}

void CVisualTracker::PrepareForBackProject(cv::Rect &selection) {

}

