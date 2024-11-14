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
		BackTopSpriteRenderer->SetOrder(ERenderOrder::COLMAP);
		BackTopSpriteRenderer->SetSprite("WindowTopBlack.png");

		FVector2D MapScale = BackTopSpriteRenderer->SetSpriteScale(1.0f);
		BackTopSpriteRenderer->SetComponentLocation({ ScreenHX, static_cast<float>(ScreenY * 0.4 - 32) });
	}

	{
		BackBottomSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BackBottomSpriteRenderer->SetOrder(ERenderOrder::TITLE);
		BackBottomSpriteRenderer->SetSprite("WindowBottomBlack.png");

		FVector2D MapScale = BackBottomSpriteRenderer->SetSpriteScale(1.0f);
		BackBottomSpriteRenderer->SetComponentLocation({ ScreenHX, static_cast<float>(ScreenY - 16.5) });
	}

	{
		BackSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BackSpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		BackSpriteRenderer->SetSprite("GrassMap.png");

		FVector2D MapScale = BackSpriteRenderer->SetSpriteScale(1.0f);
		BackSpriteRenderer->SetComponentLocation({ ScreenHX, ScreenHY + 108 - 32 });
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