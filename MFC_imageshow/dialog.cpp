// dialog.cpp : ��@��
//

#include "stdafx.h"
#include "dialog.h"
#include "afxdialogex.h"
#include "resource.h"

// dialog ��ܤ��

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


// dialog �T���B�z�`��


void dialog::OnLbnSelchangeList2()
{
	// TODO: �b���[�J����i���B�z�`���{���X
}
