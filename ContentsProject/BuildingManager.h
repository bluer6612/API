#pragma once
#include "Building.h"

// Ό³Έν :
class ABuildingManager : public AActor
{
public:
	// constrcuter destructer
	ABuildingManager();
	~ABuildingManager();

	// delete Function
	ABuildingManager(const ABuildingManager& _Other) = delete;
	ABuildingManager(ABuildingManager&& _Other) noexcept = delete;
	ABuildingManager& operator=(const ABuildingManager& _Other) = delete;
	ABuildingManager& operator=(ABuildingManager&& _Other) noexcept = delete;

protected:

private:
	std::vector<std::vector<ABuilding*>> Buildinglist;
};