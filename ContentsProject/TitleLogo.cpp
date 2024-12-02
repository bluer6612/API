#include "PreCompile.h"
#include "TitleLogo.h"
#include "ContentsEnum.h"
#include "UIManager.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/2DCollision.h>

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

		FVector2D StartPos = { ScreenHX - 134, Location.Y + 230 - 41 };
		for (int i = 0; i < 3; ++i)
		{
			U2DCollision* Collision = CreateDefaultSubObject<U2DCollision>();
			Collision->SetCollisionGroup(UICollisionGroup::Panel);
			Collision->SetCollisionType(ECollisionType::Rect);
			Collision->SetComponentLocation(StartPos);
			Collision->SetComponentScale({ 124, 56 });

			Collision->SetCollisionEnter(std::bind(&TitleLogo::TitleButtonEnter, this, std::placeholders::_1, FVector2D(i, 0)));
			Collision->SetCollisionStay(std::bind(&TitleLogo::TitleButtonStay, this, std::placeholders::_1, FVector2D(i, 0)));

			StartPos.X += 134;
		}
	}

	{
		ButtonBorderSpriteR = CreateDefaultSubObject<USpriteRenderer>();
		ButtonBorderSpriteR->SetComponentCrate(ButtonBorderSpriteR, "UI_TitleMenuButtonBorder.png", { }, { ScreenHX, Location.Y + 230 - 41 }, ERenderOrder::UIUP);
	}
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::TitleButtonEnter(AActor * _Actor, FVector2D _Index)
{
	ButtonBorderSpriteR->SetComponentLocation({ ScreenHX - 134 + (_Index.X * 134), Location.Y + 230 - 41 });
}

void TitleLogo::TitleButtonStay(AActor* _Actor, FVector2D _Index)
{
	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		LogoSpriteR->SetActiveSwitch();
		TooltipSpriteR->SetActiveSwitch();
		ButtonSpriteR->SetActiveSwitch();
		ButtonBorderSpriteR->SetActiveSwitch();

		this->Destroy();
	}
}

void TitleLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}