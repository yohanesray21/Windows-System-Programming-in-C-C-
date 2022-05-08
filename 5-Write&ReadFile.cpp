#include <Windows.h>
#include <iostream>
using namespace std;

int main() {


HANDLE hFile;
BOOL bFile;
char chBuffer[] = "This is the Sample program of Write & Read API";
DWORD dwNoByteToWrite = strlen(chBuffer);
DWORD dwNoByteToWritten = 0;
DWORD dwNoByteToRead = strlen(chBuffer);
DWORD dwNoByteRead= 0;

// Create File
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

bFile = WriteFile(
	hFile,
	chBuffer,
	dwNoByteToWrite,
	&dwNoByteToWritten,
	NULL
);

if (bFile == FALSE)
{
	cout << "WriteFile Failed" << GetLastError() << endl;
}
else {
	cout << "WriteFile Success" << endl;
}

//ReadFile

bFile = ReadFile(
	hFile,
	chBuffer,
	dwNoByteToRead,
	&dwNoByteRead,
	NULL
);

if (bFile == FALSE )
{
	cout << "ReadFile Failed & Error No - " << GetLastError() << endl;
}
else {
	cout << "ReadFile Success" << endl;
}

cout << "DATA READ FROM FILE -  > " << chBuffer << endl;

// Closing Handle

CloseHandle(hFile);
system("PAUSE");
return 0;
}
