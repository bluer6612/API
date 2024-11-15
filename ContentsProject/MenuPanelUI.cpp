#include "PreCompile.h"
#include "MenuPanelUI.h"

AMenuPanelUI::AMenuPanelUI()
{
	Location.X = ScreenX - 256 + 22;
	Location.Y = ScreenHY + 93;

	{
		Sprite[0] = CreateDefaultSubObject<USpriteRenderer>();
		Sprite[0]->SetComponentCrate(Sprite[0], "000_MenuPanel.png", {}, { Location.X, Location.Y }, ERenderOrder::UI);
		++index;
	}

	{
		Sprite[index] = CreateDefaultSubObject<USpriteRenderer>();
		Sprite[index]->SetComponentCrate(Sprite[index], "002_MenuPanel.png", { 1, 1 }, { Location.X - 256 + 5, static_cast<float>(Location.Y - 2) }, ERenderOrder::UI);
		++index;
	}

	{
		Sprite[index] = CreateDefaultSubObject<USpriteRenderer>();
		Sprite[index]->SetComponentCrate(Sprite[index], "001_MenuPanel.png", { 1, 1 }, { Location.X, Location.Y }, ERenderOrder::UI);
		++index;
	}
	{
		Sprite[index] = CreateDefaultSubObject<USpriteRenderer>();
		Sprite[index]->SetComponentCrate(Sprite[index], "003_MenuPanel.png", {}, { Location.X + 1, (Location.Y + 126) }, ERenderOrder::UI);
		++index;
	}

}

AMenuPanelUI::~AMenuPanelUI() 
{
}

