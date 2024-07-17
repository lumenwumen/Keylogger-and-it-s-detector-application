#include <Windows.h>
#include <iostream>
#include <string>
#include <TlHelp32.h>

bool IsKeyloggerRunning()
{
    bool keyloggerRunning = false;
    DWORD processID;
    const char *targetProcessName = "keylogger.exe";  
     
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &processEntry))
    {
        do
        {
            // Compare the process name with the target keylogger process name
            if (_stricmp(processEntry.szExeFile, targetProcessName) == 0)
            {
                keyloggerRunning = true;
                processID = processEntry.th32ProcessID;
                break;
            }
        } while (Process32Next(snapshot, &processEntry));
    }

    CloseHandle(snapshot);

    if (keyloggerRunning)
    {
        std::cout << "Keylogger process found with Process ID: " << processID << std::endl;
    }
    else
    {
        std::cout << "Keylogger process not found." << std::endl;
    }

    return keyloggerRunning;
}

int main()
{
    bool isRunning = IsKeyloggerRunning();

    if (isRunning)
    {
        std::cout << "A keylogger-like process is running on the system." << std::endl;
    }
    else
    {
        std::cout << "No keylogger-like process detected." << std::endl;
    }


    return 0;
}
