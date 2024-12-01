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

	std::string CalDirection(std::string _Direction, FVector2D _ActorLoc, FVector2D _TileLoc);

	Tile* FindCropTile(FVector2D _Location, int ActionState);

	bool Moving(AActor* _Actor, Tile* _Tile, float _DeltaTime);

	void Watering(Tile* _Tile);

	void Havesting(Tile* _Tile, USpriteRenderer* _SubActor);

	void CarryToStorage(Tile* _Tile);

	void SetUIManager(AUIManager* const _UIManager)
	{
		UIManager = _UIManager;
	}

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;

	AUIManager* UIManager = nullptr;
	int ActionState = 0;
	bool NextActionBool = false;
	std::string Direction = "Bot";

private:
	std::vector<class Tile*> SelectCropsVector;
	std::vector<FVector2D> SelectCropsLocVector;
	std::vector<FVector2D> WayDir = { {0, 1}, {0, -1}, {1, 0}, {-1, 0},  {-1, 1}, {-1, -1}, {1, 1}, {1, -1} };
};