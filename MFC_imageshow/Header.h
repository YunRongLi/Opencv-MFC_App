#include <afxwin.h>

class imageshowapp : public CWinApp {
public:
	BOOL InitInstance();

	CFrameWnd *imageframe;
};

class frame : public CFrameWnd {
private:
	CMenu *FMenu;
public:
	frame();
};
