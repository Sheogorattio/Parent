#pragma once
#include<Windows.h>
#include<windowsx.h>
#include<tchar.h>
#include<fstream>
#include"resource.h"

class WriteThread
{
public:
	HWND hDialog;
	WriteThread();
	static WriteThread* ptr;
	static BOOL CALLBACK DlgProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCLose(HWND hwdn);
};

