#include "ParentProc.h"

ParentProc* ParentProc::ptr = NULL;

ParentProc::ParentProc()
{
	ptr = this;
}

BOOL ParentProc::DlgProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage) {
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
	}
	return FALSE;
}

void ParentProc::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

void ParentProc::Cls_OnCommand(HWND hwdn, int id, HWND hwndCtrl, UINT codeNotify)
{
	if (id == IDOK) {
		CreateMutex(NULL, FALSE, TEXT("{263170C8 - C514 - 4A50 - AB1D - 2B302332E98C}"));

		STARTUPINFO st = { sizeof(st) };
		PROCESS_INFORMATION pr;

		TCHAR szFileName[40] = {};
		_stprintf_s(szFileName, TEXT("%s"), TEXT("WriteThread.exe"));

		if (!CreateProcess(NULL, szFileName, NULL, NULL, NULL, NULL, NULL, NULL, &st, &pr)) {
			MessageBox(0, 0, 0, 0);
			return;
		}

		CloseHandle(pr.hProcess);
		ZeroMemory(&st, sizeof(st));
		st.cb = sizeof(st);

		_stprintf_s(szFileName, TEXT("%s"), TEXT("ReadThread.exe"));

		if (!CreateProcess(NULL, szFileName, NULL, NULL, NULL, NULL, NULL, NULL, &st, &pr)) {
			MessageBox(0, 0, 0, 0);
			return;
		}

		CloseHandle(pr.hProcess);
		ZeroMemory(&st, sizeof(st));
	}
}
