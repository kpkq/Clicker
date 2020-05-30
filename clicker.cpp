#include "Windows.h"

int main()
{
    POINT point;
    while (1)
    {
        GetCursorPos(&point);
        mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
        Sleep(100);
    }
}