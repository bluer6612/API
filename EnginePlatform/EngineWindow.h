#pragma once
// Os Header
#include <Windows.h>

// std Header
#include <map>
#include <string>
#include <functional>

// user header
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineMath.h>
#include "EngineWinImage.h"

static int ScreenX = GetSystemMetrics(SM_CXSCREEN);
static int ScreenY = GetSystemMetrics(SM_CYSCREEN);

// 설명 :
class UEngineWindow
{
public:
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);

	static int WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction);
	// constrcuter destructer
	UEngineWindow();
	~UEngineWindow();

	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");
	void Open(std::string_view _TitleName = "Window");
	void SetWindowTopMost();

	inline HDC GetWindowMainDC()
	{
		return WindowImage.GetDC();
	}

	// 실력이 낮을수록 남과 공유하려고 안한다.
	// 자기만 아는걸 대명사처럼 말하고.

	inline void SetWindowTitle(std::string_view Text)
	{
		// WindowAPI의 규칙 이해하고 있느냐.
		// 전부다 에디터
		SetWindowTextA(WindowHandle, Text.data());
	}

	void SetWindowPosAndScale(FVector2D _Pos, FVector2D _Scale);
protected:

private:
	static HINSTANCE hInstance;
	static std::map<std::string, WNDCLASSEXA> WindowClasss;


	// WinApi의 기본랜더링의 핵심은
	// HDC이다. HDC는 window창에 그리기 위한 권한 핸들입니다.
	// HDC는 이미지이면서 그 이미지의 수정 권한
	// 한 윈도우한 1개의 Main HDC만 존재할수 있다.
	// 보통 이녀석을 BackBuffer라고 부릅니다.

	// 리눅스에서는 컴파일이 안되거나 실행이 안되는 코드가 된다.
	// hwnd => 위도우 창 1개
	// 윈도우에서 뭔가를 그리려는 함수의 대부분의 첫번째 인자는 hdc일것입니다.
	// HDC를 그대로 사용할리가 없죠?

	// 백버퍼에 그린걸 단 1번 windowdc에 복사붙여넣기 식으로 그릴것이다.
	// HDC BackBufferDC = nullptr;

	// 여기에 그려야만 나오는데.
	// HDC WindowMainDC = nullptr;

	UEngineWinImage* BackBufferImage = nullptr;

	// 윈도우 이미지로 랩핑되었다.
	UEngineWinImage* WindowImage = nullptr;
	HWND WindowHandle = nullptr;
};


