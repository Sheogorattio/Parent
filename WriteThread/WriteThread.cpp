#include "WriteThread.h"
#include<fstream>

using namespace std;

WriteThread* WriteThread::ptr = NULL;

WriteThread::WriteThread()
{
	ptr = this;
}

DWORD WINAPI Write_Thread(LPARAM lp) {
	WriteThread* ptr = (WriteThread*)lp;
	char buf[4096];
	
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("{263170C8 - C514 - 4A50 - AB1D - 2B302332E98C}"));

	DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);
	if (dwAnswer == WAIT_OBJECT_0)
	{
		ofstream out("coding.txt", ios::binary | ios::out | ios::trunc);

		for (int i = 0; i < 255; i++) {
			out.write(buf, i);
			out << " ";
		}
		out.close();

		ReleaseMutex(hMutex);

		MessageBox(ptr->hDialog, TEXT("Запись данных в файл coding.txt завершена!"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
	}
	
	return 0;
}

BOOL WriteThread::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	CreateThread(NULL, NULL,(LPTHREAD_START_ROUTINE) Write_Thread, this, 0, NULL);
	return TRUE;
}

void WriteThread::Cls_OnCLose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CALLBACK WriteThread::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnCLose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}
	return FALSE;
}
