#pragma once
#include "UIManager.h"

// Ό³Έν :
class ACharacterManager : public AActor
{
public:
	ACharacterManager();
	~ACharacterManager();

	ACharacterManager(const ACharacterManager& _Other) = delete;
	ACharacterManager(ACharacterManager&& _Other) noexcept = delete;
	ACharacterManager& operator=(const ACharacterManager& _Other) = delete;
	ACharacterManager& operator=(ACharacterManager&& _Other) noexcept = delete;

	Tile* FindTile(FVector2D _Location);

	void Watering(Tile* _Tile);

	void SetUIManager(AUIManager* const _UIManager)
	{
		UIManager = _UIManager;
	}

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;
	AUIManager* UIManager = nullptr;

private:

	std::vector<class Tile*> SelectCropsVector;
	std::vector<FVector2D> SelectCropsLocVector;
	std::list<int> SelectCropsLocListResult;
};