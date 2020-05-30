#include <windows.h>
#include <iostream>
bool isActivated = 0;

LRESULT CALLBACK LLKeyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    PROCESS_INFORMATION procInfo;
    if (GetAsyncKeyState(162) == -32768     // pressed Ctrl
    && GetAsyncKeyState(160) == -32768      // pressed Shift
    && GetAsyncKeyState(49) == -32767)      // pressed '1'
    {
        if (!isActivated)
        {
            STARTUPINFO startupInfo;
            ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
            std::string str("clicker.exe");
            startupInfo.cb = sizeof(STARTUPINFO);
            CreateProcess(NULL, (LPSTR)str.c_str() , NULL, NULL, 0,     // call clicker process
            NULL, NULL, NULL, &startupInfo, &procInfo);
            isActivated = 1;
        }
        else
        {
            TerminateProcess(procInfo.hProcess, NO_ERROR);      // terminate clicker process
            isActivated = 0;
        }
    }
    return 0;
}
 
int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);        // windowless application
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, LLKeyProc, GetModuleHandle(NULL), 0);     // set new hook
    if(hook)        // if hook installed successful
    {               // wait message and process it
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