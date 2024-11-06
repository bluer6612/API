#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include "ContentsEnum.h"

TitleLogo::TitleLogo()
{
	{
		LogoSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		LogoSpriteRenderer->SetOrder(ERenderOrder::TITLE);
		LogoSpriteRenderer->SetSprite("Logo.png");

		FVector2D MapScale = LogoSpriteRenderer->SetSpriteScale(2.0f);
		LogoSpriteRenderer->SetComponentLocation(MapScale.Half());
		LogoSpriteRenderer->SetComponentLocation({ ScreenX / 2,  static_cast<int>(ScreenY / 13.6) });
	}

	{
		LogoSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		LogoSpriteRenderer->SetOrder(ERenderOrder::TITLETOOLTIP);
		LogoSpriteRenderer->SetSprite("LogoTooltip.png");

		FVector2D MapScale = LogoSpriteRenderer->SetSpriteScale(2.05f);
		LogoSpriteRenderer->SetComponentLocation(MapScale.Half());
		LogoSpriteRenderer->SetComponentLocation({ ScreenX / 2,  static_cast<int>(ScreenY / 5.675) });
	}
}

TitleLogo::~TitleLogo()
{
}



void TitleLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('B'))
	{
		LogoSpriteRenderer->SetActiveSwitch();
	}
}