#include "PreCompile.h"
#include "MenuPanelUI.h"

AMenuPanelUI::AMenuPanelUI()
{
	Location.X = ScreenX - 256 + 22;
	Location.Y = ScreenHY + 93;

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("000_MenuPanel.png");
		SpriteRenderer->SetComponentScaleOrigin();
		SpriteRenderer->SetComponentLocation({ Location.X, Location.Y });
	}

	{
		SpriteRendererTap = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRendererTap->SetSprite("001_MenuPanel.png");
		SpriteRendererTap->SetComponentScale({ static_cast<float>(94), static_cast<float>(296) });
		SpriteRendererTap->SetComponentLocation({ Location.X - 256 + 5, Location.Y - 2 });
	}
}

AMenuPanelUI::~AMenuPanelUI() 
{
}

