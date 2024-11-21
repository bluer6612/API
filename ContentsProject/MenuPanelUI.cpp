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
		Sprite[index] = CreateDefaultSubObject<USpriteRenderer>();
		Sprite[index]->SetComponentCrate(Sprite[index], "003_MenuPanel_Font.png", {32 , 16}, { Location.X + 103, static_cast<float>((Location.Y + 130)) }, ERenderOrder::UIUP);
		++index;
	}

	{
		int Loc = 0;
		int Loc2 = 0;
		int j = 0;
		//for (size_t i = 0; i < CropsCount; ++i)
		for (size_t i = 0; i < CropsCount - 2; ++i)
		{
			//Ã¶°Å ¹öÆ°
			if (3 == i)
			{
				Loc = 0;
				Loc2 = 1;
			}
			else if (0 == (i - 3) % 4)
			{
				Loc2 = 1;
			}
			else if (42 == i)
			{
				Loc = 0;
				Loc2 = 1;
			}
			else if (43 == i)
			{
				Loc2 = 0;
			}
			else 
			{
				Loc2 = 0;
			}

			SpriteRFarmSlot[i] = CreateDefaultSubObject<USpriteRenderer>();
			SpriteRFarmSlot[i]->SetComponentCrate(SpriteRFarmSlot[i], "000_crop-seed-button.png", {}, { (Location.X - 153 + (Loc * 104)), (Location.Y - 120 + ((i / 4) + Loc2) * 46) }, ERenderOrder::UI);

			SpriteRFarmCoin[i] = CreateDefaultSubObject<USpriteRenderer>();
			SpriteRFarmCoin[i]->SetComponentCrate(SpriteRFarmCoin[i], "uiresourceicons_7.png", {}, { (Location.X - 153 + 39 + (Loc * 104)), (Location.Y - 120 + 16 + ((i / 4) + Loc2) * 46) }, ERenderOrder::UI);

			SpriteRFarmCrops[i] = CreateDefaultSubObject<USpriteRenderer>();
			if (i < 3)
			{
				SpriteRFarmCrops[i]->SetComponentCrate(SpriteRFarmCrops[i], "Crops.png", j * 11 + 1, {}, { (Location.X - 153 - 29 + (Loc * 104)), (Location.Y - 120 - 16 + ((i / 4) + Loc2) * 46) }, ERenderOrder::UI);
				SpriteRFarmCoin[i]->SetSprite("uiresourceicons_0.png");
			}
			else
			{
				SpriteRFarmCrops[i]->SetComponentCrate(SpriteRFarmCrops[i], "Crops.png", j * 11, {}, { (Location.X - 153 - 29 + (Loc * 104)), (Location.Y - 120 - 16 + ((i / 4) + Loc2) * 46) }, ERenderOrder::UI);
			}
			if (i > (24 - 2))
			{
				SpriteRFarmSlot[i]->SetActive(false);
			}

			++j;

			++Loc;
			if (4 <= Loc)
			{
				Loc = 0;
			}
		}

		//Loc = 0;
		//Loc2 = 0;
		//for (int i = CropsCount; i < CropsCount + 4; ++i)
		////for (size_t i = 44; i < 46; ++i)
		//{
		//	SpriteRFarmSlot[i] = CreateDefaultSubObject<USpriteRenderer>();
		//	SpriteRFarmSlot[i]->SetComponentCrate(SpriteRFarmSlot[i], "001_crop-seed-button.png", { 50, 44 }, { (Location.X - 179 + (3 * 104) + (Loc * 52)), (Location.Y - 120 + ((Loc2 / 5) * 53)) }, ERenderOrder::UI);;

		//	++Loc;
		//	if (45 == i)
		//	{
		//		Loc = 0;
		//		Loc2 = 45;
		//	}
		//}
	}
}

AMenuPanelUI::~AMenuPanelUI() 
{
}