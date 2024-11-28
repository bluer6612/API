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

	bool Moving(AActor* _Actor, Tile* _Tile, float _DeltaTime);

	int Watering(Tile* _Tile);

	void SetUIManager(AUIManager* const _UIManager)
	{
		UIManager = _UIManager;
	}

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;

	AUIManager* UIManager = nullptr;
	int ActionState = 0;
	int NextAction = 0;
	std::string Direction = "Bot";

private:
	std::vector<class Tile*> SelectCropsVector;
	std::vector<FVector2D> SelectCropsLocVector;
	std::vector<FVector2D> WayDir = { {0, 1}, {0, -1}, {1, 0}, {-1, 0},  {-1, 1}, {-1, -1}, {1, 1}, {1, -1} };
};