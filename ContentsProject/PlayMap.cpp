#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCoreDebug.h>

APlayMap::APlayMap()
{
	{
		BackTopSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BackTopSpriteRenderer->SetComponentCrate(BackTopSpriteRenderer, "WindowTopBlack.png", {}, { ScreenHX, static_cast<float>(ScreenY * 0.4 - 32) }, ERenderOrder::COLMAP);
	}

	{
		BackBottomSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BackBottomSpriteRenderer->SetComponentCrate(BackBottomSpriteRenderer, "WindowBottomBlack.png", { 1, 1 }, { ScreenHX, static_cast<float>(ScreenY - 16.5) }, ERenderOrder::TITLE);
	}

	{
		BackSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BackSpriteRenderer->SetComponentCrate(BackSpriteRenderer, "GrassMap.png", { 1, 1 }, { ScreenHX, ScreenHY + 108 - 32 }, ERenderOrder::BACKGROUND);
	}
}

APlayMap::~APlayMap()
{
}

void APlayMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

	if (true == UEngineInput::GetInst().IsDown('Y'))
	{
		BackTopSpriteRenderer->SetActiveSwitch();
	}
}