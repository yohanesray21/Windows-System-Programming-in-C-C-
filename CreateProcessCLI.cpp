#include<Windows.h>
#include<iostream>
#include <string>
#include <vector>
using namespace std;

int namedPipeServer()
{

    cout << "\t\t....NAMED PIPE SERVER...." << endl;
    //Named Pipe Local Variable
    HANDLE hCreateNamedPipe = INVALID_HANDLE_VALUE;
    char   szInputBuffer[1023] = { 0 };
    char   szOutputBuffer[1023] = { 0 };
    DWORD  dwszInputBuffer = sizeof(szInputBuffer);
    DWORD  dwszOutputBuffer = sizeof(szOutputBuffer);

    //ConnectNamedpipe Local Variable
    BOOL bConnectNamedPipe = FALSE;

    //WriteFile Local Variable
    BOOL  bWritefile = FALSE;
    char  szWriteFileBuffer[2048] = "Hello From NamedPipe Server!!";
    DWORD dwWriteBufferSize = sizeof(szWriteFileBuffer);
    DWORD dwNoBytesWrite = 0;

    //ReadFile Local Variable
    BOOL  bReadfile = FALSE;
    char  szReadFileBuffer[2048] = { 0 };
    std::string myString;
    myString.resize(1023);
    DWORD dwReadBufferSize = sizeof(szWriteFileBuffer);
    DWORD dwNoBytesRead = 0;

    uint32_t counter = 1;

    while (true)
    {
        //STEP-1 Create the Named Pipe 
        hCreateNamedPipe = CreateNamedPipe(
            L"\\\\.\\pipe\\LogAPI",//Pipe Name
            PIPE_ACCESS_DUPLEX,//Open Mode
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES,//Max Instances
            dwszOutputBuffer,//Output Buffer
            dwszInputBuffer,//Input Buffer
            0, //Default Time Out
            NULL); //Security Attributes

        if (hCreateNamedPipe == INVALID_HANDLE_VALUE)
        {
            cout << "NamedPipe Creation Failed " << endl;

            cout << "Error No - " << GetLastError() << endl;
        }
        cout << "NamedPipe Creation Success" << endl;

        //STEP-2 Connect the Named Pipe
        if (ConnectNamedPipe(hCreateNamedPipe, NULL) != false) {
            cout << "Connection Success" << endl;

            //std::vector<std::string> logVec;
            std::string logVec;

            while (true) {
                bReadfile = ReadFile(
                    hCreateNamedPipe,//Named Pipe Handle
                    szReadFileBuffer,//Read Buffer
                    dwReadBufferSize,//Read Buffer Size
                    &dwNoBytesRead,//No.of bytes Read from
                    NULL);//Overlapped Parameters
                if (bReadfile == FALSE)
                {
                    cout << "ReadFile Failed = " << GetLastError() << endl;
                    break;
                }
                else {
                    //cout << "ReadFile Success" << endl;
                }

                //cout << " DATA READING FROM CLIENT -> " << szReadFileBuffer << endl;
                /*std::string checkWriteFile{ "WriteFile" };
                std::string checkCreateFile{ "CreateFile" };
                std::string checkCreateFileW{ "CreateFileW" };
                std::string checkCreateProcess{ "CreateProcess" };
                std::string checkCreateProcessW{ "CreateProcessW" };
                std::string test{ szReadFileBuffer };

                if (test.find(checkWriteFile ) != std::string::npos) {
                    std::cout << "test :" << test << "\r\n";
                    logVec.append(test);
                    logVec.append("\r\n");
                }
                if (test.find(checkCreateFile) != std::string::npos) {
                    std::cout << "test :" << test << "\r\n";
                    logVec.append(test);
                    logVec.append("\r\n");
                }
                if (test.find(checkCreateFileW) != std::string::npos) {
                    std::cout << "test :" << test << "\r\n";
                    logVec.append(test);
                    logVec.append("\r\n");
                }
                if (test.find(checkCreateProcess) != std::string::npos) {
                    std::cout << "test :" << test << "\r\n";
                    logVec.append(test);
                    logVec.append("\r\n");
                }
                if (test.find(checkCreateProcessW) != std::string::npos) {
                    std::cout << "test :" << test << "\r\n";
                    logVec.append(test);
                    logVec.append("\r\n");
                }*/
                std::string test{ szReadFileBuffer };
                cout << test << " \r\n";
                logVec.append(test);
                logVec.append("\r\n");

            }

            // STEP-6 Disconnect the Named Pipe 
            DisconnectNamedPipe(hCreateNamedPipe);//Named Pipe Handle

            std::string nama_file{ "logApp-" };
            nama_file.append(std::to_string(counter));
            nama_file.append(".txt");
            std::wstring namaFileW{ nama_file.begin(),nama_file.end() };
            HANDLE nHandle = CreateFile(namaFileW.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL); // Create file
            if (nHandle == INVALID_HANDLE_VALUE)
            {
                std::cout << "Create File failed with error :" << GetLastError() << " \r\n";
            }
            else {
                DWORD dwBytes = logVec.length();
                LPDWORD apaan = 0;
                //LPDWORD apaan2 = 0;
                auto bWrite = WriteFile(nHandle, logVec.data(), dwBytes, apaan, NULL); // Write to File
                if (bWrite == false) {
                    std::cout << "Write fails with error :" << GetLastError() << "\r\n";
                }
                counter++;
            }
            cout << "Connection ended" << endl;
            // STEP-7 CloseHandle 
            CloseHandle(hCreateNamedPipe);
        }
        else {
            std::cout << "connection fail\r\n";
        }
    }


    //system("PAUSE");
    return 0;
}

int wmain(int argc, wchar_t* argv[])
{
    //Local Variable
    HANDLE hProcess;
    HANDLE hThread;
    
    //TCHAR commandLine[1000];

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD dwProcessID;
    DWORD dwThreadID;
    BOOL bProcess;
    //Fills block of structure memory with zero
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    //STEP-1 Create Process Function

    std::wstring commandline_args = L"\"C:\\Program Files\\Sandboxie-Plus\\Start.exe\" ";
    if (argc < 2) {
        std::wcout << L"Please specify programm path \r\n usage : " << argv[0] << L" [app path]\r\n";
        return 1;

    }

    auto app_name{ std::wstring(argv[1]) };
    commandline_args.append(app_name);
    std::wcout << L"Create process : " << commandline_args << "...\r\n";

    bProcess = CreateProcess(
        NULL,//App Name 
        &commandline_args[0],//Command Line
        NULL,//Not Inheritable Process Handle
        NULL,//Not Inheritable Thread Handle
        FALSE,//Handle Inheritance FALSE
        0, //No Creation Flag
        NULL,// Parent's Environment Block
        NULL,//Parent's Process Directory
        &si,//STARTUPINFO Structure
        &pi);//PROCESS_INFORMATION Structure
   //STEP-2 Check Process has created or not.

    if (bProcess == TRUE) {
        cout << "Create Process Success" << endl;
        //STEP-3 Print Process ID and Thread ID
        cout << "Process ID - " << pi.dwProcessId << endl;
        cout << "Thread ID - " << pi.dwThreadId << endl;
        cout << "Process ID - " << GetProcessId(pi.hProcess) << endl;
        cout << "Thread ID - " << GetThreadId(pi.hThread) << endl;

        namedPipeServer();
    } else if (bProcess == FALSE)
    {
        cout << "Create Process Failed" << endl;
        cout << "Error No - " << GetLastError() << endl;
    }
    

    

    //STEP-4 Wait until child process Exit
    WaitForSingleObject(pi.hProcess, INFINITE);
    //STEP-5 Close the open Handle for Process and its Primary Thread
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    system("PAUSE");

    return 0;
}