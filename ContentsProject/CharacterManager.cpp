#include "PreCompile.h"
#include "CharacterManager.h"
#include "TileMap.h"

#include <cmath>

ACharacterManager::ACharacterManager()
{
}

ACharacterManager::~ACharacterManager()
{
}

void ACharacterManager::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterManager::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
//
//bool Comp(UPathFindNode* first, UPathFindNode* second)
//{
//	if (first->F < second->F)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

Tile* ACharacterManager::FindTile(FVector2D _Location)
{
	Tile* CropTile = nullptr;

	SelectCropsVector.clear();
	SelectCropsLocVector.clear();
	SelectCropsLocListResult.clear();

	float Distance;
	int Index = 0;

	for (int i = 0; i < UIManager->CropsAllVector.size(); ++i)
	{
		if (true == UIManager->CropsAllVector[i]->GetWaterNeed())
		{
			SelectCropsVector[Index] = UIManager->CropsAllVector[i];
			Distance = static_cast<float>(sqrt(pow(_Location.X - UIManager->CropsAllVector[i]->GetLocation().X, 2) + pow(_Location.Y - UIManager->CropsAllVector[i]->GetLocation().Y, 2)));
			SelectCropsLocVector[Index] = { Distance, static_cast<float>(Index) };
			SelectCropsLocListResult.push_back(static_cast<int>(Distance));
			++Index;
		}
	}

	if (0 >= SelectCropsVector.size())
	{
		return CropTile;
	}

	std::list<int>::iterator StartIter = SelectCropsLocListResult.begin();
	std::list<int>::iterator EndIter = SelectCropsLocListResult.end();

	SelectCropsLocListResult.sort();

	Index = 0;
	int i = 0;
	for (; StartIter != EndIter; ++StartIter)
	{
		i = *StartIter;
		if (i == SelectCropsLocVector[Index].X)
		{
			break;
		}
		++Index;
	}

	CropTile = SelectCropsVector[i];

	return CropTile;
}

void ACharacterManager::Watering(Tile* _Tile)
{
	_Tile->SetWaterNeed(false);

	UIManager->CroppatchTile->SetCropsTileSprite(_Tile->GetLocation(), 2);
}