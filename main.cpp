#include <windows.h>
#include <iostream>
 
LRESULT CALLBACK LLKeyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (GetAsyncKeyState(162) == -32768 
    && GetAsyncKeyState(160) == -32768 
    && GetAsyncKeyState(49) == -32767)
        std::cout << "success\n";
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