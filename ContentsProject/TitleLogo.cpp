#include "PreCompile.h"
#include "TitleLogo.h"
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>

TitleLogo::TitleLogo()
{
	{
		LogoSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		LogoSpriteRenderer->SetOrder(ERenderOrder::TITLE);
		LogoSpriteRenderer->SetSprite("UI_Logo.png");

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
		ButtonSpriteRenderer[0] = CreateDefaultSubObject<USpriteRenderer>();
		ButtonSpriteRenderer[0]->SetOrder(ERenderOrder::UI);
		ButtonSpriteRenderer[0]->SetSprite("UI_TitleMenuButton.png");
		ButtonSpriteRenderer[0]->SetComponentLocation({ static_cast<float>(ScreenX * 0.43),  static_cast<float>(ScreenY / 3.975) });

		ButtonSpriteRenderer[1] = CreateDefaultSubObject<USpriteRenderer>();
		ButtonSpriteRenderer[1]->SetOrder(ERenderOrder::UI);
		ButtonSpriteRenderer[1]->SetSprite("UI_TitleMenuButton.png");
		ButtonSpriteRenderer[1]->SetComponentLocation({ ScreenHX,  static_cast<float>(ScreenY / 3.975) });

		ButtonSpriteRenderer[2] = CreateDefaultSubObject<USpriteRenderer>();
		ButtonSpriteRenderer[2]->SetOrder(ERenderOrder::UI);
		ButtonSpriteRenderer[2]->SetSprite("UI_TitleMenuButton.png");
		ButtonSpriteRenderer[2]->SetComponentLocation({ static_cast<float>(ScreenX * 0.57),  static_cast<float>(ScreenY / 3.975) });
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
		ButtonSpriteRenderer[0]->SetActiveSwitch();
		ButtonSpriteRenderer[1]->SetActiveSwitch();
		ButtonSpriteRenderer[2]->SetActiveSwitch();
	}
}