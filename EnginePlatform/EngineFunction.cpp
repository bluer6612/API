#include "EngineFunction.h"
#include "EngineWindow.h"


HWND EngineFunction::GetWindowHandle()
{
    return WindowHandle;
}

void EngineFunction::SetWindowTopMost()
{
    HWND WindowHandle = GetWindowHandle();

    RECT rc1;
    ::GetWindowRect(WindowHandle, &rc1);
    SetForegroundWindow(WindowHandle);
    SetWindowPos(WindowHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

    long style = ::GetWindowLongA(WindowHandle, GWL_STYLE);
    style &= ~WS_CAPTION;
    SetWindowLongA(WindowHandle, GWL_STYLE, style);

    //SetWindowRgn(WindowHandle, hRgn, false);
}