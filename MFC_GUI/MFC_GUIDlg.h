
// MFC_GUIDlg.h : ���Y��
//

#pragma once
#include "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\atlmfc\include\afxwin.h"
#include "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\atlmfc\include\afxcmn.h"


// CMFC_GUIDlg ��ܤ��
class CMFC_GUIDlg : public CDialogEx
{
// �غc
public:
	CMFC_GUIDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_GUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	typedef enum{
		START,
		PAUSE,
		STOP
	}CaptureState;

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

	double TM = 0.0;
	double MS_Vmin = 0.0;
	double MS_Vmax = 0.0;
	double CS_Vmin = 0.0;
	double CS_Vmax = 0.0;
	double CS_Smin = 0.0;
};



