
// MFC_GUIDlg.h : 標頭檔
//

#pragma once
#include "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\atlmfc\include\afxwin.h"
#include "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\atlmfc\include\afxcmn.h"

#include <opencv\cv.h>
#include <opencv\highgui.h>

#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>

#include "CCamCapture2.h"

typedef enum {
	START,
	PAUSE,
	STOP
}CaptureState;

#define MAX_THREADS 1;
#define BUF_SIZE 255;
// CMFC_GUIDlg 對話方塊
class CMFC_GUIDlg : public CDialogEx
{
// 建構
public:
	CMFC_GUIDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_GUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CaptureState Capturestate;

	CButton m_Button_Startcapture;
	CButton m_Button_Parse;
	CStatic m_STATIC_Tracking_Method;
	CComboBox m_COMBO_Tracking_Method;
	CStatic m_STATIC_Param1;
	CStatic m_STATIC_Param2;
	CStatic m_STATIC_Param3;
	CSliderCtrl m_SLIDER_Param1;
	CSliderCtrl m_SLIDER_Param2;
	CSliderCtrl m_SLIDER_Param3;
	CEdit m_EDIT_Param1_Value;
	CEdit m_EDIT_Param2_Value;
	CEdit m_EDIT_Param3_Value;

	afx_msg void OnCbnSelchangeComboTrackingMethod();
	afx_msg void OnBnClickedButtonStartcapture();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnNMCustomdrawSliderParam1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderParam2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderParam3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditParam1Value();
	afx_msg void OnEnChangeEditParam2Value();

	float TM_Param = 0.0;
	float MS_Vmin_Param = 0.0;
	float MS_Vmax_Param = 0.0;
	float CS_Vmin_Param = 0.0;
	float CS_Vmax_Param = 0.0;
	float CS_Smin_Param = 0.0;

	CCamCapture2 ccamcapture;
};




