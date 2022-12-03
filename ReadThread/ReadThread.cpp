#include "ReadThread.h"

ReadThread* ReadThread::ptr = NULL;

ReadThread::ReadThread(void)
{
	ptr = this;
}

void ReadThread::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI Read_Thread(LPVOID lp)
{
	ReadThread* ptr = (ReadThread*)lp;
	char buf[4096];

	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("{263170C8 - C514 - 4A50 - AB1D - 2B302332E98C}"));

	DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);
	if (dwAnswer == WAIT_OBJECT_0)
	{
		ifstream in(TEXT("coding.txt"), ios::_Nocreate | ios::in);
		if (!in)
		{
			MessageBox(ptr->hDialog, TEXT("Ошибка открытия файла!"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
			return 1;
		}
		ofstream out("newFile.txt",  ios::out | ios::trunc);
		const int KEY = 100;
		while (!in.eof())
		{
			in.read(buf, 4096);
			int n = in.gcount();
			out.write(buf, n);
		}
		out.close();
		in.close();

		ReleaseMutex(hMutex);

		MessageBox(ptr->hDialog, TEXT("Чтение данных из файла coding.txt завершено!"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
	}
	return 0;
}

BOOL ReadThread::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	CreateThread(NULL, 0, Read_Thread, this, 0, NULL);
	return TRUE;
}

BOOL CALLBACK ReadThread::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}
	return FALSE;
}