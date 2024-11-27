#pragma once
#include "Building.h"
#include "UIManager.h"

// Ό³Έν :
class ABuildingManager : public ABuilding
{
public:
	ABuildingManager();
	~ABuildingManager();

	ABuildingManager(const ABuildingManager& _Other) = delete;
	ABuildingManager(ABuildingManager&& _Other) noexcept = delete;
	ABuildingManager& operator=(const ABuildingManager& _Other) = delete;
	ABuildingManager& operator=(ABuildingManager&& _Other) noexcept = delete;

	void SetUIManager(AUIManager* const _UIManager)
	{
		UIManager = _UIManager;
	}

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;

private:
	AUIManager* UIManager = nullptr;

	std::vector<std::vector<ABuilding*>> Buildinglist;
};