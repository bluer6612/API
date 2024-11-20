#pragma once
#include <EngineCore/Actor.h>

enum class UICollisionGroup
{
	Cursor,
	UI,
};

// Ό³Έν :
class AUIManager : public AActor
{
public:
	// constrcuter destructer
	AUIManager();
	~AUIManager();

	// delete Function
	AUIManager(const AUIManager& _Other) = delete;
	AUIManager(AUIManager&& _Other) noexcept = delete;
	AUIManager& operator=(const AUIManager& _Other) = delete;
	AUIManager& operator=(AUIManager&& _Other) noexcept = delete;

protected:
	void BeginPlay();

	void Tick(float _DeltaTime);

	void PanelButtonTileEnter(AActor* _Actor, FIntPoint _Index);
	void PanelButtonTileEnd(AActor* _Actor, FIntPoint _Index);

private:
	class U2DCollision* CursorCollision = nullptr;

	class USpriteRenderer* SpriteRFarmInfo = nullptr;

	std::vector<std::vector<int>> Test;
};

