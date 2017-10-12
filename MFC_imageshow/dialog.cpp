// dialog.cpp : 實作檔
//

#include "stdafx.h"
#include "dialog.h"
#include "afxdialogex.h"
#include "resource.h"

// dialog 對話方塊

IMPLEMENT_DYNAMIC(dialog, CDialog)

dialog::dialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

dialog::~dialog()
{
}

void dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(dialog, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST2, &dialog::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// dialog 訊息處理常式


void dialog::OnLbnSelchangeList2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}
