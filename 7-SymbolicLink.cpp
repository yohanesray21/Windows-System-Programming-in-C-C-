#include<Windows.h>
#include<iostream>
using namespace std;

int main() {
	BOOL bHfile;

	bHfile = CreateSymbolicLink(
		L"E:\\Visual Studio - Practice\\SymbolicLink.txt",
		L"E:\\Visual Studio - Practice\\SoftLink.txt",
		0
	);

	if (bHfile == FALSE)
	{
		cout << "CreateSymbolicLink & Error No - " << GetLastError() << endl;
	}
	else {
		cout << "CreateSymbolicLink Success" << endl;
	}

	system("PAUSE");
	return 0;
}