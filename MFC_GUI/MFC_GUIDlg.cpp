
// MFC_GUIDlg.cpp : ��@��
//

#include <cstring>

#include "stdafx.h"
#include "MFC_GUI.h"
#include "MFC_GUIDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
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


// CMFC_GUIDlg ��ܤ��



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
//Event Handle Function�s��
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


// CMFC_GUIDlg �T���B�z�`��

BOOL CMFC_GUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
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

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w	

	Capturestate = STOP;

	m_Button_Startcapture.SetWindowTextW(_T("Start Capture"));

	m_Button_Parse.EnableWindow(0);

	m_COMBO_Tracking_Method.AddString(_T("TemplateMatch"));
	m_COMBO_Tracking_Method.AddString(_T("MeanShift"));
	m_COMBO_Tracking_Method.AddString(_T("CamShift"));

	m_COMBO_Tracking_Method.SetCurSel(0);

	m_STATIC_Param1.SetWindowTextW(_T("TM"));
	m_STATIC_Param2.SetWindowTextW(_T(""));
	m_STATIC_Param3.SetWindowTextW(_T(""));

	m_SLIDER_Param1.SetRange(0, 1000, false);

	m_SLIDER_Param1.EnableWindow(0);
	m_SLIDER_Param2.EnableWindow(0);
	m_SLIDER_Param3.EnableWindow(0);

	m_EDIT_Param1_Value.EnableWindow(0);
	m_EDIT_Param2_Value.EnableWindow(0);
	m_EDIT_Param3_Value.EnableWindow(0);

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
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

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CMFC_GUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CMFC_GUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_GUIDlg::OnCbnSelchangeComboTrackingMethod()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int Method_index = m_COMBO_Tracking_Method.GetCurSel();
	if(Capturestate == STOP){
		if (Method_index == 0) {
			m_STATIC_Param1.SetWindowTextW(_T("TM"));
			m_STATIC_Param2.SetWindowTextW(_T(""));
			m_STATIC_Param3.SetWindowTextW(_T(""));

			m_SLIDER_Param1.SetRange(0, 1000, true);
		}
		else if(Method_index == 1){
			m_STATIC_Param1.SetWindowTextW(_T("Vmin"));
			m_STATIC_Param2.SetWindowTextW(_T("Vmax"));
			m_STATIC_Param3.SetWindowTextW(_T(""));

			m_SLIDER_Param1.SetRange(-100, 500, true);
			m_SLIDER_Param2.SetRange(-200, 300, true);
		}
		else if (Method_index == 2) {
			m_STATIC_Param1.SetWindowTextW(_T("Vmin"));
			m_STATIC_Param2.SetWindowTextW(_T("Vmax"));
			m_STATIC_Param3.SetWindowTextW(_T("Smin"));

			m_SLIDER_Param1.SetRange(-250, 250, true);
			m_SLIDER_Param2.SetRange(-500, 500, true);
			m_SLIDER_Param3.SetRange(0, 100, true);
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

			m_SLIDER_Param1.SetRange(0, 1000, true);

			//CString SliderTM_Pos_str = NULL;
			//SliderTM_Pos_str.Format(_T("%.1f"), TM);

			//m_EDIT_Param1_Value.SetWindowTextW(SliderTM_Pos_str);
			int SliderTM_Pos = (int)(TM * 10);
			m_SLIDER_Param1.SetPos(SliderTM_Pos);
		}
		else if (Method_index == 1) {
			m_STATIC_Param1.SetWindowTextW(_T("Vmin"));
			m_STATIC_Param2.SetWindowTextW(_T("Vmax"));
			m_STATIC_Param3.SetWindowTextW(_T(""));

			m_SLIDER_Param2.EnableWindow(1);
			m_SLIDER_Param3.EnableWindow(0);

			m_EDIT_Param2_Value.EnableWindow(1);
			m_EDIT_Param3_Value.EnableWindow(0);

			m_SLIDER_Param1.SetRange(-100, 500, true);
			m_SLIDER_Param2.SetRange(-200, 300, true);


			//CString SliderVmin_Pos_str = NULL;
			//CString SliderVmax_Pos_str = NULL;
			//SliderVmin_Pos_str.Format(_T("%.1f"), MS_Vmin);
			//SliderVmax_Pos_str.Format(_T("%.1f"), MS_Vmax);

			//m_EDIT_Param1_Value.SetWindowTextW(SliderVmin_Pos_str);
			//m_EDIT_Param2_Value.SetWindowTextW(SliderVmax_Pos_str);

		}
		else if (Method_index == 2) {
			m_STATIC_Param1.SetWindowTextW(_T("Vmin"));
			m_STATIC_Param2.SetWindowTextW(_T("Vmax"));
			m_STATIC_Param3.SetWindowTextW(_T("Smin"));


			m_SLIDER_Param2.EnableWindow(1);
			m_SLIDER_Param3.EnableWindow(1);

			m_EDIT_Param2_Value.EnableWindow(1);
			m_EDIT_Param3_Value.EnableWindow(1);


			m_SLIDER_Param1.SetRange(-250, 250, true);
			m_SLIDER_Param2.SetRange(-500, 500, true);
			m_SLIDER_Param3.SetRange(0, 100, true);
		}
	}
}


void CMFC_GUIDlg::OnBnClickedButtonStartcapture()
{
	// TODO: �b���[�J����i���B�z�`���{���X

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
	}
}


void CMFC_GUIDlg::OnBnClickedButtonPause()
{
	// TODO: �b���[�J����i���B�z�`���{���X
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
	// TODO: �b���[�J����i���B�z�`���{���X
	*pResult = 0;

	float Slider_Pos_;
	CString Slider_Pos_str = NULL;
	Slider_Pos_ = (float)m_SLIDER_Param1.GetPos()/10;
	Slider_Pos_str.Format(_T("%.1f"), Slider_Pos_);

	m_EDIT_Param1_Value.SetWindowTextW(Slider_Pos_str);
	
	int Method_index = m_COMBO_Tracking_Method.GetCurSel();
	if (Method_index == 0) {
		TM = Slider_Pos_;
	}
	else if (Method_index == 1) {
		MS_Vmin = Slider_Pos_;
	}
	else if (Method_index == 2) {
		CS_Vmin = Slider_Pos_;
	}
}

void CMFC_GUIDlg::OnNMCustomdrawSliderParam2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �b���[�J����i���B�z�`���{���X
	*pResult = 0;

	float Slider_Pos_;
	CString Slider_Pos_str = NULL;
	Slider_Pos_ = (float)m_SLIDER_Param2.GetPos()/10;
	Slider_Pos_str.Format(_T("%.1f"), Slider_Pos_);

	m_EDIT_Param2_Value.SetWindowTextW(Slider_Pos_str);
	int Method_index = m_COMBO_Tracking_Method.GetCurSel();
	if (Method_index == 1) {
		MS_Vmax = Slider_Pos_;
	}
	else if (Method_index == 2) {
		CS_Vmax = Slider_Pos_;
	}

}

void CMFC_GUIDlg::OnNMCustomdrawSliderParam3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �b���[�J����i���B�z�`���{���X
	*pResult = 0;

	float Slider_Pos_;
	CString Slider_Pos_str = NULL;
	Slider_Pos_ = (float)m_SLIDER_Param3.GetPos()/10;
	Slider_Pos_str.Format(_T("%.1f"), Slider_Pos_);

	m_EDIT_Param3_Value.SetWindowTextW(Slider_Pos_str);

	CS_Smin = Slider_Pos_;
}


void CMFC_GUIDlg::OnEnChangeEditParam1Value()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X

}


void CMFC_GUIDlg::OnEnChangeEditParam2Value()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X


}

BOOL CMFC_GUIDlg::PreTranslateMessage(MSG* pMsg) {
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN && GetFocus() == &m_EDIT_Param1_Value) {
		CString EditParam1Str = NULL;
		int intNum;
		double floatNum;

		m_EDIT_Param1_Value.GetWindowTextW(EditParam1Str);
		floatNum = _ttof(EditParam1Str);
		intNum = (int)(floatNum * 10);

		m_SLIDER_Param1.SetPos(intNum);

		int Method_index = m_COMBO_Tracking_Method.GetCurSel();
		if (Method_index == 0) {
			TM = floatNum;
		}
		else if (Method_index == 1) {
			MS_Vmin = floatNum;
		}
		else if (Method_index == 2) {
			CS_Vmin = floatNum;
		}
		return TRUE;
	}
	else if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN && GetFocus() == &m_EDIT_Param2_Value) {
		CString EditParam2Str = NULL;
		int intNum;
		double floatNum;

		m_EDIT_Param2_Value.GetWindowTextW(EditParam2Str);
		floatNum = _ttof(EditParam2Str);
		intNum = (int)(floatNum * 10);

		m_SLIDER_Param2.SetPos(intNum);
		int Method_index = m_COMBO_Tracking_Method.GetCurSel();
		if (Method_index == 1) {
			MS_Vmax = floatNum;
		}
		else if (Method_index == 2) {
			CS_Vmax = floatNum;
		}

		return TRUE;
	}
	else if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN && GetFocus() == &m_EDIT_Param3_Value) {
		CString EditParam3Str = NULL;
		int intNum;
		double floatNum;

		m_EDIT_Param3_Value.GetWindowTextW(EditParam3Str);
		floatNum = _ttof(EditParam3Str);
		intNum = (int)(floatNum * 10);

		m_SLIDER_Param3.SetPos(intNum);

		CS_Smin = floatNum;
		return TRUE;
	}

	return FALSE;
}