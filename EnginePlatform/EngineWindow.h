#pragma once
#include <Windows.h>

#include <map>
#include <string>
#include <functional>

#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineMath.h>
#include "EngineWinImage.h"


static int ScreenX = GetSystemMetrics(SM_CXSCREEN);
static int ScreenY = GetSystemMetrics(SM_CYSCREEN);
static float ScreenHX = ScreenX * 0.5;
static float ScreenHY = ScreenY - 243 - 36;

class UEngineWindow
{
public:
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);

	static int WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction);
	
	UEngineWindow();
	~UEngineWindow();

	
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");
	void Open(std::string_view _TitleName = "Window");

	inline FVector2D GetWindowSize() const
	{
		return WindowSize;
	}

	inline UEngineWinImage* GetWindowImage() const
	{
		return WindowImage;
	}

	inline UEngineWinImage* GetBackBuffer() const
	{
		return BackBufferImage;
	}

	inline void SetWindowTitle(std::string_view Text)  const
	{			
		SetWindowTextA(WindowHandle, Text.data());
	}

	void SetWindowPosAndScale(FVector2D _Pos, FVector2D _Scale);

	FVector2D GetMousePos();

	void SetWindowAlpha();

protected:

private:
	static HINSTANCE hInstance;
	static std::map<std::string, WNDCLASSEXA> WindowClasss;
		
	FVector2D WindowSize;

	UEngineWinImage* BackBufferImage = nullptr;

	UEngineWinImage* WindowImage = nullptr;

	HWND WindowHandle = nullptr;
};


