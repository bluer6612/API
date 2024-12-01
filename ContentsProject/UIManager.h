#pragma once
#include <EngineCore/Actor.h>
#include "TileMap.h"
#include "MenuPanelUI.h"

enum class UICollisionGroup
{
	Cursor,
	Ground,
	Building,
	Croppatch,
	Panel,
};

static int Money = 400;
static int bio = 8;

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

	void BeginPlay();

	void Tick(float _DeltaTime);

	USpriteRenderer* GetCursorImage()
	{
		return CursorImage;
	}

	void SetMenuPanelUI(AMenuPanelUI* const _MenuPanelUI)
	{
		MenuPanelUI = _MenuPanelUI;
	}

	void TapButtonIn();
	void TapButtonOut();
	void TapButtonStay(AActor* _Actor, FTransform _Index);

	void PanelButtonTileEnter(AActor* _Actor, FTransform _Index);
	void PanelButtonTileStay(AActor* _Actor, FTransform _Index);
	void PanelButtonTileEnd(AActor* _Actor, FTransform _Index);

	ATileMap* GroundTileMap = nullptr;

	std::vector<class Tile*> CropsAllVector;
	USpriteRenderer* CroppatchTileImage[1000] = {};
	ATileMap* CroppatchTile = nullptr;

	std::vector<class Tile*> StorageTilesVector;
	std::vector<int> FarmingStats;

protected:

private:
	class U2DCollision* CursorCollision = nullptr;
	class USpriteRenderer* CursorImage = nullptr;

	class USpriteRenderer* SRFarmInfo = nullptr;
	class USpriteRenderer* SRButtonBlack = nullptr;
	class USpriteRenderer* SRTapWhite = nullptr;

	AMenuPanelUI* MenuPanelUI = nullptr;

	bool CursorOnTap = false;
	int NowSelectCrops = -1;
	int NowSelectTap = 1;
	int TapTimer = 0;

	std::vector<class U2DCollision*> PanelAllVector;
};