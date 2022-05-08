#include<Windows.h>
#include<iostream>
using namespace std;

int main() {
	BOOL bHfile;
	bHfile = CreateHardLink(
		L"E:\\Visual Studio - Practice\\Hardlink.txt",
		L"E:\\Visual Studio - Practice\\TestFile.txt",
		NULL
		);

	if (bHfile == FALSE)
	{
		cout << "CreateHardLink Failed & Error No - " << GetLastError() << endl;
	}
	else {
		cout << "CreateHardLink Success" << endl;
	}

	system("PAUSE");
	return 0;
}