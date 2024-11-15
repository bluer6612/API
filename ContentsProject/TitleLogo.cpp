#include "PreCompile.h"
#include "TitleLogo.h"
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>

TitleLogo::TitleLogo()
{
	Location.X = ScreenHX;
	Location.Y = ScreenHY;
	{
		LogoSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		LogoSpriteRenderer->SetComponentCrate(LogoSpriteRenderer, "UI_Logo.png", { }, { ScreenHX,  static_cast<float>(Location.Y - 10) }, ERenderOrder::TITLE);
	}

	{
		TooltipSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		TooltipSpriteRenderer->SetComponentCrate(TooltipSpriteRenderer, "UI_LogoTooltip.png", { 1, 1 }, { ScreenHX,  static_cast<float>(Location.Y + 99) }, ERenderOrder::UI);
	}

	{
		ButtonSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ButtonSpriteRenderer->SetComponentCrate(ButtonSpriteRenderer, "UI_TitleMenuButton.png", { 1, 1 }, { ScreenHX, Location.Y + 230 - 41 }, ERenderOrder::UI);
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
		ButtonSpriteRenderer->SetActiveSwitch();
	}
}