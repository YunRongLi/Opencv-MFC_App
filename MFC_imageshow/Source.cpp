#include <afxwin.h>
#include "Header.h"
#include "resource.h"
#include <afxres.h>


//������l��
BOOL imageshowapp::InitInstance(){
	imageframe = new frame;
	m_pMainWnd = imageframe;

	imageframe->ShowWindow(SW_SHOW);

	return true;
}

//�ۭq�����ج[
frame::frame() {
	Create(NULL, "123");
	FMenu = new CMenu;
	FMenu->LoadMenu(IDR_MENU1);
	SetMenu(FMenu);
}

imageshowapp app;