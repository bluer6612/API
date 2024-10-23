#pragma once
#include "EngineWindow.h"
#include <windef.h>

class EngineFunction : UEngineWindow
{
public:
	void SetWindowTopMost();

	HWND GetWindowHandle();
};

