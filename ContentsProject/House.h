#pragma once
#include "BuildingManager.h"

class AHouse : public ABuildingManager
{
public:
	AHouse();
	~AHouse();
	
	AHouse(const AHouse& _Other) = delete;
	AHouse(AHouse&& _Other) noexcept = delete;
	AHouse& operator=(const AHouse& _Other) = delete;
	AHouse& operator=(AHouse&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);

protected:

private:
	class USpriteRenderer* SpriteRWheel = nullptr;
	class USpriteRenderer* SpriteRDoor = nullptr;
	class USpriteRenderer* MoneySpriteR = nullptr;;
};