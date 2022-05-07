#include <Windows.h>
#include <iostream>
using namespace std;

int main() {


HANDLE hFile;

hFile = CreateFile(
	L"E:\\Visual Studio - Practice\\TestFile.txt",
	GENERIC_READ | GENERIC_WRITE,
	FILE_SHARE_READ,
	NULL,
	CREATE_NEW,
	FILE_ATTRIBUTE_NORMAL,
	NULL
);

if (hFile == INVALID_HANDLE_VALUE)
{
	cout << "CreateFile Failed & Error No" << GetLastError() << endl;

}
else {
	cout << "CreateFile Success" << endl;
}

CloseHandle(hFile);
system("PAUSE");
return 0;
}
