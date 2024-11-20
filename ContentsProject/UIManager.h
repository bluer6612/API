#pragma once
#include <EngineCore/Actor.h>

enum class UICollisionGroup
{
	Cursor,
	UI,
};


// ���� :
class AUIManager : public AActor
{
public:
	class FarmInfo
	{
		FIntPoint FPIndex;
		int IntIndex = 0;
	};
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

	FarmInfo FarmInfoIndex;

	std::vector<std::vector<int>> Test;
};

