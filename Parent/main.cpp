#include"ParentProc.h"
#include"resource.h"

BOOL WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE instPrev, LPTSTR lpszCmdLine, int nCmdShow) {
	ParentProc parent;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)ParentProc::DlgProc);
}