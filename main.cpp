#include <windows.h>
#include <iostream>
 
LRESULT CALLBACK LLKeyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(nCode == HC_ACTION)
    {
        DWORD vk = ((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
        std::cout << "key pressed : " << vk << std::endl;
        if(vk == 0x1b)
        {
            PostQuitMessage(0);
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
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