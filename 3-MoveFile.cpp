#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	
	BOOL bFile;
	
	bFile = MoveFile(
		L"E:\\Visual Studio - Practice\\MoveFile\\helloNew.txt",
		L"E:\\Visual Studio - Practice\\hello.txt"
		);

	if (bFile = FALSE) {
		
		cout << "MoveFile Failed & Error No - " << GetLastError() << endl;
	}
	else {
		cout << "Move File Successs" << endl;
	}

	system("PAUSE");
	return 0;
}