#pragma once
// Os Header
#include <Windows.h>

// std Header
#include <map>
#include <string>
#include <functional>

// user header
#include <EngineBase/EngineDelegate.h>


// 정신 잘 붙

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

	inline HDC GetBackBuffer()
	{
		return BackBuffer;
	}



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
	HDC BackBuffer = nullptr;
	HWND WindowHandle = nullptr;
};


