#pragma once
//#include "BuildingManager.h"
#include <EngineCore/Actor.h>
#include <EngineCore/GlobalVariable.h>

class AMenuPanelUI : public AActor
{
public:
	AMenuPanelUI();
	~AMenuPanelUI();

	AMenuPanelUI(const AMenuPanelUI& _Other) = delete;
	AMenuPanelUI(AMenuPanelUI&& _Other) noexcept = delete;
	AMenuPanelUI& operator=(const AMenuPanelUI& _Other) = delete;
	AMenuPanelUI& operator=(AMenuPanelUI&& _Other) noexcept = delete;

	USpriteRenderer* GetSprite(int _index) const
	{
		return Sprite[_index];
	}

	class USpriteRenderer* SpriteRFarmCoin[CropsCount] = {};

protected:

private:
	FVector2D Location;
	int index = 0;

	class USpriteRenderer* SpriteRTap = nullptr;
	class USpriteRenderer* SpriteRResourcesBar = nullptr;
	class USpriteRenderer* SpriteRFarmSlot[CropsCount] = {};
	class USpriteRenderer* SpriteRFarmCrops[CropsCount] = {};
	class USpriteRenderer* Sprite[10] = {};
};