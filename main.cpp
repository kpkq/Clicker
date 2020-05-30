#include <windows.h>
#include <iostream>
bool isActivated = 0;

LRESULT CALLBACK LLKeyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    PROCESS_INFORMATION procInfo;
    if (GetAsyncKeyState(162) == -32768 
    && GetAsyncKeyState(160) == -32768 
    && GetAsyncKeyState(49) == -32767)
    {
        if (!isActivated)
        {
            STARTUPINFO startupInfo;
            ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
            std::string str("clicker.exe");
            startupInfo.cb = sizeof(STARTUPINFO);
            CreateProcess(NULL, (LPSTR)str.c_str() , NULL, NULL, 0, 
            NULL, NULL, NULL, &startupInfo, &procInfo);
            isActivated = 1;
        }
        else
        {
            TerminateProcess(procInfo.hProcess, NO_ERROR);
            isActivated = 0;
        }
    }
    return 0;
}
 
int main()
{
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, LLKeyProc, GetModuleHandle(NULL), 0);
    if(hook)
    {
        while(WaitMessage())
        {
            MSG msg = {0};
            while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                if(msg.message == WM_QUIT)
                {
                    UnhookWindowsHookEx(hook);
                    return 0;
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
    return 0;
}