#include "PreCompile.h"
#include <ContentsProject/MainContentsCore.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineTimer.h>
#include <EngineBase/EngineRandom.h>

#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "ContentsProject.lib")


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

    {
        APPBARDATA appBarData;
        memset(&appBarData, 0, sizeof(appBarData));
        appBarData.hWnd = FindWindowA(("Shell_TrayWnd"), NULL);
        appBarData.cbSize = sizeof(appBarData);
        appBarData.lParam |= ABS_ALWAYSONTOP;
        //appBarData.lParam |= ABS_AUTOHIDE;
        //appBarData.lParam |= ABS_ALWAYSONTOP;
        //appBarData.lParam |= ABS_AUTOHIDE | ABS_ALWAYSONTOP;
        ::SHAppBarMessage(ABM_SETSTATE, &appBarData);
    }


	MainContentsCore User;
	return UEngineAPICore::EngineStart(hInstance, &User);
}