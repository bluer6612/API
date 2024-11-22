#pragma once
#include "Building.h"
#include "UIManager.h"
#include "TileMap.h"

// Ό³Έν :
class ACroppatch : public ABuilding
{
public:
	friend class AUIManager;

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
	ATileMap* CroppatchTile = nullptr;
	USpriteRenderer* CroppatchTileImage[16] = {};
};

