#pragma once
#include "TileMap.h"
#include "MenuPanelUI.h"
#include "UIManager.h"

// Ό³Έν :
class AFarmingManager : public AActor
{
public:
	AFarmingManager();
	~AFarmingManager();

	AFarmingManager(const AFarmingManager& _Other) = delete;
	AFarmingManager(AFarmingManager&& _Other) noexcept = delete;
	AFarmingManager& operator=(const AFarmingManager& _Other) = delete;
	AFarmingManager& operator=(AFarmingManager&& _Other) noexcept = delete;

	void SetUIManager(AUIManager* const _UIManager)
	{
		UIManager = _UIManager;
	}

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;

private:
	AUIManager* UIManager = nullptr;

	float GrowTime = 0;
};