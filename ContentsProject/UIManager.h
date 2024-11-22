#pragma once
#include <EngineCore/Actor.h>
#include "BuildingManager.h"
#include "Croppatch.h"

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
	friend class ACroppatch;

	AUIManager();
	~AUIManager();

	AUIManager(const AUIManager& _Other) = delete;
	AUIManager(AUIManager&& _Other) noexcept = delete;
	AUIManager& operator=(const AUIManager& _Other) = delete;
	AUIManager& operator=(AUIManager&& _Other) noexcept = delete;

	USpriteRenderer* GetCursorImage()
	{
		return CursorImage;
	}

	void PanelButtonTileEnter(AActor* _Actor, FTransform _Index);

	void SetBuildingManager(ABuildingManager* const _BuildingManager)
	{
		BuildingManager = _BuildingManager;
	}

	void SetCroppatch(ACroppatch* const _Croppatch)
	{
		Croppatch = _Croppatch;
	}

protected:
	void BeginPlay();

	void Tick(float _DeltaTime);

	void PanelButtonTileStay(AActor* _Actor, FTransform _Index);
	void PanelButtonTileEnd(AActor* _Actor, FTransform _Index);

private:
	class U2DCollision* CursorCollision = nullptr;
	class USpriteRenderer* CursorImage = nullptr;

	class USpriteRenderer* SRFarmInfo = nullptr;
	class USpriteRenderer* SRButtonBlack = nullptr;

	ABuildingManager* BuildingManager = nullptr;
	ACroppatch* Croppatch = nullptr;

	std::vector<std::vector<int>> FarmInfoIndex;
};

