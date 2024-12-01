#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCoreDebug.h>

APlayMap::APlayMap()
{
	{
		BackTopSpriteR = CreateDefaultSubObject<USpriteRenderer>();
		BackTopSpriteR->SetComponentCrate(BackTopSpriteR, "WindowTopBlack.png", {}, { ScreenHX, static_cast<float>(ScreenY * 0.4 - 32) }, ERenderOrder::COLMAP);
	}

	{
		BackBottomSpriteR = CreateDefaultSubObject<USpriteRenderer>();
		BackBottomSpriteR->SetComponentCrate(BackBottomSpriteR, "WindowBottomBlack.png", { 1, 1 }, { ScreenHX, static_cast<float>(ScreenY - 16) }, ERenderOrder::TITLE);
	}

	{
		BackSpriteR = CreateDefaultSubObject<USpriteRenderer>();
		BackSpriteR->SetComponentCrate(BackSpriteR, "GrassMap.png", { 1, 1 }, { ScreenHX, static_cast<float>(ScreenY - 148 - TaskbarY) }, ERenderOrder::BACKGROUND);
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
}