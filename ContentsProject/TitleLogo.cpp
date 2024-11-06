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
		LogoSpriteRenderer->SetSprite("UI_Logo2.png");

		FVector2D MapScale = LogoSpriteRenderer->SetSpriteScale(1.00f);
		LogoSpriteRenderer->SetComponentLocation({ ScreenX / 2,  static_cast<int>(ScreenY / 13.6) });
	}

	{
		TooltipSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		TooltipSpriteRenderer->SetOrder(ERenderOrder::UI);
		TooltipSpriteRenderer->SetSprite("UI_LogoTooltip2.png");

		FVector2D MapScale = TooltipSpriteRenderer->SetSpriteScale(1.00f);
		TooltipSpriteRenderer->SetComponentLocation({ ScreenX / 2,  static_cast<int>(ScreenY / 5.675) });
	}

	{
		MoneySpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MoneySpriteRenderer->SetOrder(ERenderOrder::UI);
		MoneySpriteRenderer->SetSprite("UI_biofuelspareparts.png");

		FVector2D MapScale = MoneySpriteRenderer->SetSpriteScale(1.00f);
		MoneySpriteRenderer->SetComponentLocation({ ScreenX / 2,  static_cast<int>(ScreenY / 2.675) });
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