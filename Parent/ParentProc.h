#pragma once
#include<windows.h>
#include<windowsX.h>
#include<tchar.h>

class ParentProc
{
public:
	ParentProc();
	static ParentProc* ptr;
	static BOOL CALLBACK DlgProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	void Cls_OnClose(HWND hwnd);
	void Cls_OnCommand(HWND hwdn, int id, HWND hwndCtrl, UINT codeNotify);
};

