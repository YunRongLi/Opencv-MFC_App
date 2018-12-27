
// MFC_GUIDlg.cpp : 實作檔
//

#include <cstring>

#include "stdafx.h"
#include "MFC_GUI.h"
#include "MFC_GUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVisualTracker CMFC_GUIDlg::cvisualtracker;
CCamCapture2 CMFC_GUIDlg::ccamcapture;

// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMFC_GUIDlg 對話方塊

CMFC_GUIDlg::CMFC_GUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_GUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_GUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_Startcapture, m_Button_Startcapture);
	DDX_Control(pDX, IDC_BUTTON_Pause, m_Button_Parse);
	DDX_Control(pDX, IDC_STATIC_Tracking_Method, m_STATIC_Tracking_Method);
	DDX_Control(pDX, IDC_COMBO_Tracking_Method, m_COMBO_Tracking_Method);
	DDX_Control(pDX, IDC_STATIC_Param1, m_STATIC_Param1);
	DDX_Control(pDX, IDC_STATIC_Param2, m_STATIC_Param2);
	DDX_Control(pDX, IDC_STATIC_Param3, m_STATIC_Param3);
	DDX_Control(pDX, IDC_SLIDER_Param1, m_SLIDER_Param1);
	DDX_Control(pDX, IDC_SLIDER_Param2, m_SLIDER_Param2);
	DDX_Control(pDX, IDC_SLIDER_Param3, m_SLIDER_Param3);
	DDX_Control(pDX, IDC_EDIT_Param1_Value, m_EDIT_Param1_Value);
	DDX_Control(pDX, IDC_EDIT_Param2_Value, m_EDIT_Param2_Value);
	DDX_Control(pDX, IDC_EDIT_Param3_Value, m_EDIT_Param3_Value);
}
//Event Handle Function連結
BEGIN_MESSAGE_MAP(CMFC_GUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_Tracking_Method, &CMFC_GUIDlg::OnCbnSelchangeComboTrackingMethod)
	ON_BN_CLICKED(IDC_BUTTON_Startcapture, &CMFC_GUIDlg::OnBnClickedButtonStartcapture)
	ON_BN_CLICKED(IDC_BUTTON_Pause, &CMFC_GUIDlg::OnBnClickedButtonPause)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Param1, &CMFC_GUIDlg::OnNMCustomdrawSliderParam1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Param2, &CMFC_GUIDlg::OnNMCustomdrawSliderParam2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Param3, &CMFC_GUIDlg::OnNMCustomdrawSliderParam3)
	ON_EN_CHANGE(IDC_EDIT_Param1_Value, &CMFC_GUIDlg::OnEnChangeEditParam1Value)
	ON_EN_CHANGE(IDC_EDIT_Param2_Value, &CMFC_GUIDlg::OnEnChangeEditParam2Value)
END_MESSAGE_MAP()

// CMFC_GUIDlg 訊息處理常式

BOOL CMFC_GUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定	

	Capturestate = STOP;

	m_Button_Startcapture.SetWindowTextW(_T("Start Capture"));

	m_Button_Parse.EnableWindow(0);

	m_COMBO_Tracking_Method.AddString(_T("TemplateMatch"));
	m_COMBO_Tracking_Method.AddString(_T("MeanShift"));
	m_COMBO_Tracking_Method.AddString(_T("CamShift"));

	m_COMBO_Tracking_Method.SetCurSel(0);

	cvisualtracker.SetMethodType(VT_Method_Type::TemplateMatch);

	m_STATIC_Param1.SetWindowTextW(_T("TM"));
	m_STATIC_Param2.SetWindowTextW(_T(""));
	m_STATIC_Param3.SetWindowTextW(_T(""));

	m_SLIDER_Param1.SetRange(1, 6, false);

	m_SLIDER_Param1.EnableWindow(0);
	m_SLIDER_Param2.EnableWindow(0);
	m_SLIDER_Param3.EnableWindow(0);
	
	m_EDIT_Param1_Value.EnableWindow(0);
	m_EDIT_Param2_Value.EnableWindow(0);
	m_EDIT_Param3_Value.EnableWindow(0);

	ccamcapture.SetCaptureCallback(CMFC_GUIDlg::CVisualTrackerCB);

	
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFC_GUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFC_GUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFC_GUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFC_GUIDlg::OnCbnSelchangeComboTrackingMethod()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	int Method_index = m_COMBO_Tracking_Method.GetCurSel();
	if(Capturestate == STOP){
		if (Method_index == 0) {
			m_STATIC_Param1.SetWindowTextW(_T("TM"));
			m_STATIC_Param2.SetWindowTextW(_T(""));
			m_STATIC_Param3.SetWindowTextW(_T(""));

			m_SLIDER_Param1.SetRange(1, 6, true);

			cvisualtracker.SetMethodType(VT_Method_Type::TemplateMatch);
		}
		else if(Method_index == 1){
			m_STATIC_Param1.SetWindowTextW(_T("Vmin"));
			m_STATIC_Param2.SetWindowTextW(_T("Vmax"));
			m_STATIC_Param3.SetWindowTextW(_T(""));

			m_SLIDER_Param1.SetRange(0, 255, true);
			m_SLIDER_Param2.SetRange(0, 255, true);

			cvisualtracker.SetMethodType(VT_Method_Type::MeanShift);
		}
		else if (Method_index == 2) {
			m_STATIC_Param1.SetWindowTextW(_T("Vmin"));
			m_STATIC_Param2.SetWindowTextW(_T("Vmax"));
			m_STATIC_Param3.SetWindowTextW(_T("Smin"));

			m_SLIDER_Param1.SetRange(0, 255, true);
			m_SLIDER_Param2.SetRange(0, 255, true);
			m_SLIDER_Param3.SetRange(0, 255, true);

			cvisualtracker.SetMethodType(VT_Method_Type::CAMShift);
		}
	}
	else {
		if (Method_index == 0) {
			m_STATIC_Param1.SetWindowTextW(_T("TM"));
			m_STATIC_Param2.SetWindowTextW(_T(""));
			m_STATIC_Param3.SetWindowTextW(_T(""));

			m_SLIDER_Param2.EnableWindow(0);
			m_SLIDER_Param3.EnableWindow(0);

			m_EDIT_Param2_Value.EnableWindow(0);
			m_EDIT_Param3_Value.EnableWindow(0);

			m_SLIDER_Param1.SetRange(1, 6, true);

			CString SliderTM_Pos_str = NULL;
			SliderTM_Pos_str.Format(_T("%d"), m_Params.TM_Param);

			m_EDIT_Param1_Value.SetWindowTextW(SliderTM_Pos_str);

			m_SLIDER_Param1.SetPos(m_Params.TM_Param);

			cvisualtracker.SetMethodType(VT_Method_Type::TemplateMatch);
		}
		else if (Method_index == 1) {
			m_STATIC_Param1.SetWindowTextW(_T("Vmin"));
			m_STATIC_Param2.SetWindowTextW(_T("Vmax"));
			m_STATIC_Param3.SetWindowTextW(_T(""));

			m_SLIDER_Param2.EnableWindow(1);
			m_SLIDER_Param3.EnableWindow(0);

			m_EDIT_Param2_Value.EnableWindow(1);
			m_EDIT_Param3_Value.EnableWindow(0);

			m_SLIDER_Param1.SetRange(0, 255, true);
			m_SLIDER_Param2.SetRange(0, 255, true);

			CString SliderVmin_Pos_str = NULL;
			CString SliderVmax_Pos_str = NULL;

			SliderVmin_Pos_str.Format(_T("%d"), m_Params.MS_Param.vmin);
			SliderVmax_Pos_str.Format(_T("%d"), m_Params.MS_Param.vmax);

			m_EDIT_Param1_Value.SetWindowTextW(SliderVmin_Pos_str);
			m_EDIT_Param2_Value.SetWindowTextW(SliderVmax_Pos_str);
			
			m_SLIDER_Param1.SetPos(m_Params.MS_Param.vmin);
			m_SLIDER_Param2.SetPos(m_Params.MS_Param.vmax);

			cvisualtracker.SetMethodType(VT_Method_Type::MeanShift);
		}
		else if (Method_index == 2) {
			m_STATIC_Param1.SetWindowTextW(_T("Vmin"));
			m_STATIC_Param2.SetWindowTextW(_T("Vmax"));
			m_STATIC_Param3.SetWindowTextW(_T("Smin"));


			m_SLIDER_Param2.EnableWindow(1);
			m_SLIDER_Param3.EnableWindow(1);

			m_EDIT_Param2_Value.EnableWindow(1);
			m_EDIT_Param3_Value.EnableWindow(1);


			m_SLIDER_Param1.SetRange(0, 255, true);
			m_SLIDER_Param2.SetRange(0, 255, true);
			m_SLIDER_Param3.SetRange(0, 255, true);

			CString SliderVmin_Pos_str = NULL;
			CString SliderVmax_Pos_str = NULL;
			CString SliderSmin_Pos_str = NULL;

			SliderVmin_Pos_str.Format(_T("%d"), m_Params.CS_Param.vmin);
			SliderVmax_Pos_str.Format(_T("%d"), m_Params.CS_Param.vmax);
			SliderSmin_Pos_str.Format(_T("%d"), m_Params.CS_Param.smin);

			m_EDIT_Param1_Value.SetWindowTextW(SliderVmin_Pos_str);
			m_EDIT_Param2_Value.SetWindowTextW(SliderVmax_Pos_str);
			m_EDIT_Param3_Value.SetWindowTextW(SliderSmin_Pos_str);

			m_SLIDER_Param1.SetPos(m_Params.CS_Param.vmin);
			m_SLIDER_Param2.SetPos(m_Params.CS_Param.vmax);
			m_SLIDER_Param3.SetPos(m_Params.CS_Param.smin);

			cvisualtracker.SetMethodType(VT_Method_Type::CAMShift);
		}
	}
	
}


void CMFC_GUIDlg::OnBnClickedButtonStartcapture()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	if (Capturestate == STOP){
		Capturestate = START;

		m_Button_Startcapture.SetWindowTextW(_T("Stop Capture"));
		m_Button_Parse.EnableWindow(1);

		int Method_index = m_COMBO_Tracking_Method.GetCurSel();

		if(Method_index == 0){
			m_SLIDER_Param1.EnableWindow(1);
			m_EDIT_Param1_Value.EnableWindow(1);
		}
		else if (Method_index == 1) {
			m_SLIDER_Param1.EnableWindow(1);
			m_SLIDER_Param2.EnableWindow(1);

			m_EDIT_Param1_Value.EnableWindow(1);
			m_EDIT_Param2_Value.EnableWindow(1);

		}
		else if (Method_index == 2) {
			m_SLIDER_Param1.EnableWindow(1);
			m_SLIDER_Param2.EnableWindow(1);
			m_SLIDER_Param3.EnableWindow(1);

			m_EDIT_Param1_Value.EnableWindow(1);
			m_EDIT_Param2_Value.EnableWindow(1);
			m_EDIT_Param3_Value.EnableWindow(1);
		}

		ccamcapture.CreateCapture();
		
	}
	else{
		Capturestate = STOP;
		
		m_Button_Startcapture.SetWindowTextW(_T("Start Capture"));
		m_Button_Parse.EnableWindow(0);

		m_Button_Parse.SetWindowTextW(_T("Pause"));

		m_SLIDER_Param1.EnableWindow(0);
		m_SLIDER_Param2.EnableWindow(0);
		m_SLIDER_Param3.EnableWindow(0);

		m_EDIT_Param1_Value.EnableWindow(0);
		m_EDIT_Param2_Value.EnableWindow(0);
		m_EDIT_Param3_Value.EnableWindow(0);

		ccamcapture.DestoryCapture();
		
		
	}
}


void CMFC_GUIDlg::OnBnClickedButtonPause()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString Parse_TextStr = NULL;
	m_Button_Parse.GetWindowTextW(Parse_TextStr);
	if(Capturestate == START){
		m_Button_Parse.SetWindowTextW(_T("Continue"));
		Capturestate = PAUSE;

	}
	else{
		m_Button_Parse.SetWindowTextW(_T("Pause"));
		Capturestate = START;
	}
}


void CMFC_GUIDlg::OnNMCustomdrawSliderParam1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;
	
	//float Slider_Pos_;
	CString Slider_Pos_str = NULL;

	int Slider_Pos_ = m_SLIDER_Param1.GetPos();
	Slider_Pos_str.Format(_T("%d"), Slider_Pos_);

	m_EDIT_Param1_Value.SetWindowTextW(Slider_Pos_str);
	
	int Method_index = m_COMBO_Tracking_Method.GetCurSel();
	if (Method_index == 0 && GetFocus() == &m_SLIDER_Param1) {
		switch (Slider_Pos_) {
		case 1:
			m_Params.TM_Param = TempMatchParam::TM_SQDIFF;
			break;
		case 2:
			m_Params.TM_Param = TempMatchParam::TM_SQDIFF_NORMED;
			break;
		case 3:
			m_Params.TM_Param = TempMatchParam::TM_CCORR;
			break;
		case 4:
			m_Params.TM_Param = TempMatchParam::TM_CCORR_NORMED;
			break;
		case 5:
			m_Params.TM_Param = TempMatchParam::TM_CCOEFF;
			break;
		case 6:
			m_Params.TM_Param = TempMatchParam::TM_CCOEFF_NORMED;
			break;
		default:
			break;
		}

		cvisualtracker.SetVT_Params(VT_Method_Type::TemplateMatch, m_Params);
	}
	else if (Method_index == 1 && GetFocus() == &m_SLIDER_Param1) {
		m_Params.MS_Param.vmin = Slider_Pos_;

		cvisualtracker.SetVT_Params(VT_Method_Type::MeanShift, m_Params);
	}
	else if (Method_index == 2 && GetFocus() == &m_SLIDER_Param1) {
		m_Params.CS_Param.vmin = Slider_Pos_;

		cvisualtracker.SetVT_Params(VT_Method_Type::CAMShift, m_Params);
	}


}

void CMFC_GUIDlg::OnNMCustomdrawSliderParam2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;

	int Slider_Pos_ = m_SLIDER_Param2.GetPos();;
	CString Slider_Pos_str = NULL;
	Slider_Pos_str.Format(_T("%d"), Slider_Pos_);

	m_EDIT_Param2_Value.SetWindowTextW(Slider_Pos_str);
	int Method_index = m_COMBO_Tracking_Method.GetCurSel();
	if (Method_index == 1 && GetFocus() == &m_SLIDER_Param2) {
		m_Params.MS_Param.vmax = Slider_Pos_;

		cvisualtracker.SetVT_Params(VT_Method_Type::MeanShift, m_Params);
	}
	else if (Method_index == 2 && GetFocus() == &m_SLIDER_Param2) {
		m_Params.CS_Param.vmax = Slider_Pos_;

		cvisualtracker.SetVT_Params(VT_Method_Type::CAMShift, m_Params);
	}
}

void CMFC_GUIDlg::OnNMCustomdrawSliderParam3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;

	int Slider_Pos_ = m_SLIDER_Param3.GetPos();
	CString Slider_Pos_str = NULL;

	Slider_Pos_str.Format(_T("%d"), Slider_Pos_);

	m_EDIT_Param3_Value.SetWindowTextW(Slider_Pos_str);

	m_Params.CS_Param.vmax = Slider_Pos_;

	cvisualtracker.SetVT_Params(VT_Method_Type::CAMShift, m_Params);
}


void CMFC_GUIDlg::OnEnChangeEditParam1Value()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼

}


void CMFC_GUIDlg::OnEnChangeEditParam2Value()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼


}

BOOL CMFC_GUIDlg::PreTranslateMessage(MSG* pMsg) {
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN && GetFocus() == &m_EDIT_Param1_Value) {
		CString EditParam1Str = NULL;
		int Param1;

		m_EDIT_Param1_Value.GetWindowTextW(EditParam1Str);
		Param1 = _ttoi(EditParam1Str);

		m_SLIDER_Param1.SetPos(Param1);

		int Method_index = m_COMBO_Tracking_Method.GetCurSel();
		if (Method_index == 0) {
			switch (Param1) {
			case 1:
				m_Params.TM_Param = TempMatchParam::TM_SQDIFF;
				break;
			case 2:
				m_Params.TM_Param = TempMatchParam::TM_SQDIFF_NORMED;
				break;
			case 3:
				m_Params.TM_Param = TempMatchParam::TM_CCORR;
				break;
			case 4:
				m_Params.TM_Param = TempMatchParam::TM_CCORR_NORMED;
				break;
			case 5:
				m_Params.TM_Param = TempMatchParam::TM_CCOEFF;
				break;
			case 6:
				m_Params.TM_Param = TempMatchParam::TM_CCOEFF_NORMED;
				break;
			default:
				break;
			}
		}
		else if (Method_index == 1) {
			m_Params.MS_Param.vmin = Param1;
		}
		else if (Method_index == 2) {
			m_Params.CS_Param.vmin = Param1;
		}
		return TRUE;
	}
	else if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN && GetFocus() == &m_EDIT_Param2_Value) {
		CString EditParam2Str = NULL;
		int Param2;

		m_EDIT_Param2_Value.GetWindowTextW(EditParam2Str);
		Param2 = _ttoi(EditParam2Str);

		m_SLIDER_Param2.SetPos(Param2);
		int Method_index = m_COMBO_Tracking_Method.GetCurSel();
		if (Method_index == 1) {
			m_Params.MS_Param.vmax = Param2;
		}
		else if (Method_index == 2) {
			m_Params.CS_Param.vmax = Param2;
		}

		return TRUE;
	}
	else if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN && GetFocus() == &m_EDIT_Param3_Value) {
		CString EditParam3Str = NULL;
		int Param3;

		m_EDIT_Param3_Value.GetWindowTextW(EditParam3Str);
		Param3 = _ttoi(EditParam3Str);

		m_SLIDER_Param3.SetPos(Param3);

		m_Params.CS_Param.smin = Param3;
		return TRUE;
	}

	return FALSE;
}

void CMFC_GUIDlg::CVisualTrackerCB(cv::Mat& Frame) {
	cv::Mat mROI = ccamcapture.GetSelectedROI();
	cv::Mat* mpROI = &mROI;
	cv::Rect TrackRect = ccamcapture.GetTargetRect();

	cvisualtracker.SetROI(mpROI);

	cvisualtracker.Tracking(Frame, TrackRect);

	cvisualtracker.ShowResult(Frame, TrackRect);
}
