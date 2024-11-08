#include "PreCompile.h"
#include "TitleLogo.h"
#include <EnginePlatform/EngineInput.h>
#include "ContentsEnum.h"

TitleLogo::TitleLogo()
{
	{
		LogoSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		LogoSpriteRenderer->SetOrder(ERenderOrder::TITLE);
		LogoSpriteRenderer->SetSprite("UI_Logo.png");

		LogoSpriteRenderer->SetSpriteScale(2.00f);
		LogoSpriteRenderer->SetComponentLocation({ ScreenX / 2,  static_cast<int>(ScreenY / 13.6) });
	}

	{
		TooltipSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		TooltipSpriteRenderer->SetOrder(ERenderOrder::UI);
		TooltipSpriteRenderer->SetSprite("UI_LogoTooltip.png");

		TooltipSpriteRenderer->SetSpriteScale(1.0f);
		TooltipSpriteRenderer->SetComponentLocation({ ScreenX / 2,  static_cast<int>(ScreenY / 5.8) });
	}

	{
		MoneySpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MoneySpriteRenderer->SetOrder(ERenderOrder::UI);
		MoneySpriteRenderer->SetSprite("UI_biofuelspareparts.png");

		MoneySpriteRenderer->SetSpriteScale(2.00f);
		MoneySpriteRenderer->SetComponentLocation({ ScreenX / 2,  static_cast<int>(ScreenY / 3.5) });
	}

	{
		ButtonSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ButtonSpriteRenderer->SetOrder(ERenderOrder::UI);
		ButtonSpriteRenderer->SetSprite("UI_TitleMenuButton.png");

		ButtonSpriteRenderer->SetSpriteScale(2.00f);
		ButtonSpriteRenderer->SetComponentLocation({ static_cast<float>(ScreenX * 0.43),  static_cast<float>(ScreenY / 3.975) });

		ButtonSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ButtonSpriteRenderer->SetOrder(ERenderOrder::UI);
		ButtonSpriteRenderer->SetSprite("UI_TitleMenuButton.png");

		ButtonSpriteRenderer->SetSpriteScale(2.00f);
		ButtonSpriteRenderer->SetComponentLocation({ static_cast<float>(ScreenX * 0.5),  static_cast<float>(ScreenY / 3.975) });

		ButtonSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ButtonSpriteRenderer->SetOrder(ERenderOrder::UI);
		ButtonSpriteRenderer->SetSprite("UI_TitleMenuButton.png");

		ButtonSpriteRenderer->SetSpriteScale(2.00f);
		ButtonSpriteRenderer->SetComponentLocation({ static_cast<float>(ScreenX * 0.57),  static_cast<float>(ScreenY / 3.975) });
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
		TooltipSpriteRenderer->SetActiveSwitch();
		MoneySpriteRenderer->SetActiveSwitch();
		ButtonSpriteRenderer->SetActiveSwitch();
	}
}