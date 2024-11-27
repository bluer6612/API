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
	SelectCropsLocList.clear();
	SelectCropsLocListResult.clear();

	std::vector<class Tile*>::iterator StartIter = UIManager->CropsAllVector.begin();
	std::vector<class Tile*>::iterator EndIter = UIManager->CropsAllVector.end();

	float Distance;

	for (int i = 0; i < UIManager->CropsAllVector.size(); ++i)
	{
		if (false == UIManager->CropsAllVector[i]->GetWaterNeed())
		{
			SelectCropsVector.push_back(UIManager->CropsAllVector[i]);
			Distance = static_cast<float>(sqrt(pow(_Location.X - UIManager->CropsAllVector[i]->GetLocation().X, 2) + pow(_Location.Y - UIManager->CropsAllVector[i]->GetLocation().Y, 2)));
			SelectCropsLocList.push_back({ Distance, static_cast<float>(i)});
			SelectCropsLocListResult.push_back(static_cast<int>(Distance));
		}
	}

	if (0 >= SelectCropsVector.size())
	{
		return CropTile;
	}

	SelectCropsLocListResult.sort();

	for (int i = 0; i < SelectCropsVector.size(); ++i)
	{
		SelectCropsLocList.
	}

	FVector2D Location = SelectCropsLocList.front();

	CropTile = UIManager->CroppatchTile->GetTileByLocation(SelectCropsVector[Location.Y]->GetLocation());;

	return CropTile;
}

void ACharacterManager::Watering(FVector2D _Location)
{

}