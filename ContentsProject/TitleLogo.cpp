#include "PreCompile.h"
#include "TitleLogo.h"
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>

TitleLogo::TitleLogo()
{
	Location.X = ScreenHX;
	Location.Y = ScreenHY;
	{
		LogoSpriteR = CreateDefaultSubObject<USpriteRenderer>();
		LogoSpriteR->SetComponentCrate(LogoSpriteR, "UI_Logo.png", { }, { ScreenHX,  static_cast<float>(Location.Y - 10) }, ERenderOrder::TITLE);
	}

	{
		TooltipSpriteR = CreateDefaultSubObject<USpriteRenderer>();
		TooltipSpriteR->SetComponentCrate(TooltipSpriteR, "UI_LogoTooltip.png", { 1, 1 }, { ScreenHX,  static_cast<float>(Location.Y + 99) }, ERenderOrder::UI);
	}

	{
		ButtonSpriteR = CreateDefaultSubObject<USpriteRenderer>();
		ButtonSpriteR->SetComponentCrate(ButtonSpriteR, "UI_TitleMenuButton.png", { 1, 1 }, { ScreenHX, Location.Y + 230 - 41 }, ERenderOrder::UI);
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
		LogoSpriteR->SetActiveSwitch();
		TooltipSpriteR->SetActiveSwitch();
		ButtonSpriteR->SetActiveSwitch();
	}
}