#include "PreCompile.h"
#include "MenuPanelUI.h"

AMenuPanelUI::AMenuPanelUI()
{
	Location.X = ScreenX - 256 + 22;
	Location.Y = ScreenHY + 93;

	{
		Sprite[index] = CreateDefaultSubObject<USpriteRenderer>();
		Sprite[index]->SetComponentCrate(Sprite[index], "000_MenuPanel.png", {}, { Location.X, Location.Y }, ERenderOrder::UI);
		++index;
	}

	{
		Sprite[index] = CreateDefaultSubObject<USpriteRenderer>();
		Sprite[index]->SetComponentCrate(Sprite[index], "001_MenuPanel.png", { 1, 1 }, { Location.X - 256 + 5, static_cast<float>(Location.Y - 2) }, ERenderOrder::UI);
		++index;
	}

	{
		Sprite[index] = CreateDefaultSubObject<USpriteRenderer>();
		Sprite[index]->SetComponentCrate(Sprite[index], "002_MenuPanel.png", { 1, 1 }, { Location.X + 1, Location.Y - 1 }, ERenderOrder::UI);
		++index;
	}

	{
		Sprite[index] = CreateDefaultSubObject<USpriteRenderer>();
		Sprite[index]->SetComponentCrate(Sprite[index], "003_MenuPanel.png", {}, { Location.X + 1, (Location.Y + 126) }, ERenderOrder::UIUP);
		++index;
	}

	{
		int Loc = 0;
		for (size_t i = 0; i < 44; ++i)
		{
			SpriteRFarmSlot[i] = CreateDefaultSubObject<USpriteRenderer>();
			SpriteRFarmSlot[i]->SetComponentCrate(SpriteRFarmSlot[i], "000_crop-seed-button.png", {}, { (Location.X - 153 + (Loc * 104)), (Location.Y - 120 + ((Loc / 4) + (i / 4)) * 46)  }, ERenderOrder::UI);

			if (i > 24 - 1)
			{
				SpriteRFarmSlot[i]->SetActive(false);
			}

			++Loc;
			if (4 <= Loc)
			{
				Loc = 0;
			}
		}
	}
}

AMenuPanelUI::~AMenuPanelUI() 
{
}

