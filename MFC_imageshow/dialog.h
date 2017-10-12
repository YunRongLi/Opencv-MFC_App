#pragma once


// dialog 對話方塊

class dialog : public CDialog
{
	DECLARE_DYNAMIC(dialog)

public:
	dialog(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~dialog();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList2();
};
