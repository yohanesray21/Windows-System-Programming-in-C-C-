#include<Windows.h>
#include<iostream>
using namespace std;

int main() {
	HANDLE hProcess = NULL;
	HANDLE hThread = NULL;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD dwProccessId = 0;
	DWORD dwThreadId = 0;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	BOOL bCreateProcess = NULL;
	bCreateProcess = CreateProcess(
		L"C:\\Windows\\system32\\notepad.exe",
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi
	);

	if (bCreateProcess == FALSE) {
		cout << "Create Process Failed & Error No - " << GetLastError() << endl;
	}
	else {
		cout << "CreateProcess Success" << endl;
	}

	cout << "Process ID -> " << pi.dwProcessId;
	cout << "\nThread ID -> " << pi.dwThreadId;
	cout << "\nGetProcessID -> " << GetProcessId(pi.hProcess);
	cout << "\nGetThreadID -> " << GetThreadId(pi.hThread);

	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);


	system("PAUSE");
	return 0;

}
