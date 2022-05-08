#include<Windows.h>
#include<iostream>
using namespace std;

int main() {
	LONG lReg;
	HKEY hKey;
	DWORD dwData = 1234;

	lReg = RegCreateKeyEx(
		HKEY_LOCAL_MACHINE,
		L"Software\\Test\\Product\\SmartId",
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS | KEY_WOW64_64KEY,
		NULL,
		&hKey,
		NULL
	);

	if (lReg != ERROR_SUCCESS)
	{
		cout << "RegCreateKeyEx Failed & Error No - " << GetLastError() << endl;
	}
	else {
		cout << "Registry Creation success" << endl;
	}

	//Set Registry Value
	lReg = RegSetValueEx(
		hKey,
		L"VALUE",
		NULL,
		REG_DWORD,
		(LPBYTE)&dwData,
		sizeof(dwData)
	);

	if (lReg != ERROR_SUCCESS)
	{
		cout << "RegSetValueEx Failed & Error No - " << GetLastError() << endl;
	}
	else {
		cout << "Registry  Set Value success" << endl;
	}

	RegCloseKey(hKey);

	system("PAUSE");
	return 0;
}