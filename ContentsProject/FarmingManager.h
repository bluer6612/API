#pragma once
#include <EngineCore/GlobalVariable.h>
#include "TileMap.h"
#include "MenuPanelUI.h"

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

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;

private:
};