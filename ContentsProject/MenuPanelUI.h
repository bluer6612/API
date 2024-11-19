#pragma once
#include "Building.h"

class AMenuPanelUI : public ABuilding
{
public:
	AMenuPanelUI();
	~AMenuPanelUI();

	AMenuPanelUI(const AMenuPanelUI& _Other) = delete;
	AMenuPanelUI(AMenuPanelUI&& _Other) noexcept = delete;
	AMenuPanelUI& operator=(const AMenuPanelUI& _Other) = delete;
	AMenuPanelUI& operator=(AMenuPanelUI&& _Other) noexcept = delete;

	USpriteRenderer* GetSpriteRFarmInfo() const
	{
		return SpriteRFarmInfo;
	}

	class USpriteRenderer* SpriteRFarmInfo = nullptr;

protected:

private:
	class USpriteRenderer* SpriteRTap = nullptr;
	class USpriteRenderer* SpriteRResourcesBar = nullptr;
	class USpriteRenderer* SpriteRFarmSlot[CropsCount] = {};
	class USpriteRenderer* SpriteRFarmCrops[CropsCount] = {};
	class USpriteRenderer* SpriteRFarmCoin[CropsCount] = {};
};

