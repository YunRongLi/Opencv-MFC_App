
// MFC_GUI.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMFC_GUIApp: 
// �аѾ\��@�����O�� MFC_GUI.cpp
//

class CMFC_GUIApp : public CWinApp
{
public:
	CMFC_GUIApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CMFC_GUIApp theApp;