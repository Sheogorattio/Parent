#pragma once
#include<windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <fstream>
#include"resource.h"

using namespace std;

class ReadThread
{
public:
	ReadThread(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static ReadThread* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	HWND hDialog;
};

