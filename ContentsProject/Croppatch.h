#pragma once
#include "BuildingManager.h"

// Ό³Έν :
class ACroppatch : public ABuildingManager
{
public:
	ACroppatch();
	~ACroppatch();

	ACroppatch(const ACroppatch& _Other) = delete;
	ACroppatch(ACroppatch&& _Other) noexcept = delete;
	ACroppatch& operator=(const ACroppatch& _Other) = delete;
	ACroppatch& operator=(ACroppatch&& _Other) noexcept = delete;

	void ClickEnter(AActor* _Actor, FTransform _Index);

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	USpriteRenderer* CroppatchTileImage[16] = {};
};