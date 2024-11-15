#include "PreCompile.h"
#include "MenuPanelUI.h"

AMenuPanelUI::AMenuPanelUI()
{
	Location.X = ScreenX - 256 + 22;
	Location.Y = ScreenHY + 93;

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetComponentCrate(SpriteRenderer, "000_MenuPanel.png", {}, { Location.X, Location.Y }, ERenderOrder::BUILDING);
	}

	{
		SpriteRendererTap = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRendererTap->SetComponentCrate(SpriteRendererTap, "001_MenuPanel.png", {94, 296}, { Location.X - 256 + 5, Location.Y - 2 }, ERenderOrder::BUILDING);
	}

	{
		SpriteRendererResourcesBar = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRendererResourcesBar->SetComponentCrate(SpriteRendererResourcesBar, "002_MenuPanel.png", {}, { Location.X, (Location.Y - 2) }, ERenderOrder::BUILDING);
	}
}

AMenuPanelUI::~AMenuPanelUI() 
{
}

