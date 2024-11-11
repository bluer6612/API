#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCoreDebug.h>

APlayMap::APlayMap()
{
	{
		BackSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BackSpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		BackSpriteRenderer->SetSprite("GrassMap.png");

		FVector2D MapScale = BackSpriteRenderer->SetSpriteScale(1.0f);
		BackSpriteRenderer->SetComponentLocation(MapScale.Half());
	}

	{
		BackTopSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BackTopSpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		BackTopSpriteRenderer->SetSprite("WindowTopBlack.png");

		FVector2D MapScale = BackTopSpriteRenderer->SetSpriteScale(1.0f);
		BackTopSpriteRenderer->SetComponentLocation({ ScreenX, -30 });
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