#pragma once


// dialog ��ܤ��

class dialog : public CDialog
{
	DECLARE_DYNAMIC(dialog)

public:
	dialog(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~dialog();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList2();
};
