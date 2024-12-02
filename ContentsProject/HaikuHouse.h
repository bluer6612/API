#pragma once
#include "BuildingManager.h"

// Ό³Έν :
class AHaikuHouse : public ABuildingManager
{
public:
	// constrcuter destructer
	AHaikuHouse();
	~AHaikuHouse();

	// delete Function
	AHaikuHouse(const AHaikuHouse& _Other) = delete;
	AHaikuHouse(AHaikuHouse&& _Other) noexcept = delete;
	AHaikuHouse& operator=(const AHaikuHouse& _Other) = delete;
	AHaikuHouse& operator=(AHaikuHouse&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);

protected:

private:

};

