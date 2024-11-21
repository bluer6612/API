#pragma once
#include <EngineCore/Actor.h>

enum class UICollisionGroup
{
	Cursor,
	Ground,
	Building,
	Croppatch,
	Panel,
};

// Ό³Έν :
class AUIManager : public AActor
{
public:
	AUIManager();
	~AUIManager();

	AUIManager(const AUIManager& _Other) = delete;
	AUIManager(AUIManager&& _Other) noexcept = delete;
	AUIManager& operator=(const AUIManager& _Other) = delete;
	AUIManager& operator=(AUIManager&& _Other) noexcept = delete;

protected:
	void BeginPlay();

	void Tick(float _DeltaTime);

	void PanelButtonTileEnter(AActor* _Actor, FTransform _Index);
	void PanelButtonTileStay(AActor* _Actor, FTransform _Index);
	void PanelButtonTileEnd(AActor* _Actor, FTransform _Index);

private:
	class U2DCollision* CursorCollision = nullptr;
	class USpriteRenderer* CursorImage = nullptr;

	class USpriteRenderer* SRFarmInfo = nullptr;
	class USpriteRenderer* SRButtonBlack = nullptr;

	std::vector<std::vector<int>> FarmInfoIndex;
};

