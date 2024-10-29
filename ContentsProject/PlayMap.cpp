#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>

APlayMap::APlayMap()
{
	// 매번 윈도우 사이즈가 바뀌면
	// 이거 자체도 사실 좋은건 아닙니다.
	FVector2D WindowSize =  UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	SetActorScale(WindowSize.Half());
	SetActorLocation(WindowSize.Half());
}

APlayMap::~APlayMap()
{
}

