#include <windows.h>
#include <iostream>
using namespace std;

int main() {
	BOOL bFile;
	
	bFile = CopyFile(
		L"E:\\Visual Studio - Practice\\hello.txt",
		L"E:\\Visual Studio - Practice\\helloNew.txt",
		TRUE
	);

	if (bFile == FALSE)
	{
		cout << "CopyFile Failed & Error No - " << GetLastError() << endl;
	}
	else {
		cout << "CopyFile Success" << endl;
	};

	system("PAUSE");
	return 0;
}