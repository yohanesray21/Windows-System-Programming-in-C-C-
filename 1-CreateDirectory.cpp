#include<Windows.h>
#include<iostream>
using namespace std;

int main() {

	BOOL bDir;
	bDir = CreateDirectory(
		L"E:\\Visual Studio - Practice\\Dir1",
		NULL
	);

	if (bDir == FALSE) {
		cout << "CreateDirectory Failed & Error No - " << GetLastError() << endl;
	}
	else {
		cout << "CreateDirectory Success" << endl;
	}

	getchar();

	bDir = RemoveDirectory(L"E:\\Visual Studio - Practice\\Dir1");

	if (bDir == FALSE) {
		cout << "RemoveDirectory Failed & Error No - " << GetLastError() << endl;
	}
	else {
		cout << "RemoveDirectory Success" << endl;
	}

	system("PAUSE");

	return 0;
}