#include "PreCompile.h"
#include "CharacterManager.h"
#include "TileMap.h"

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

	std::vector<class Tile*>::iterator StartIter = UIManager->CropsAllVector.begin();
	std::vector<class Tile*>::iterator EndIter = UIManager->CropsAllVector.end();

	for (int i = 0; i < UIManager->CropsAllVector.size(); ++i)
	{
		if (false == UIManager->CropsAllVector[i]->GetWaterNeed())
		{
			SelectCropsVector.push_back(UIManager->CropsAllVector[i]);
			SelectCropsLocList.push_back({ {_Location.X - UIManager->CropsAllVector[i]->GetLocation().X, _Location.Y + UIManager->CropsAllVector[i]->GetLocation().Y}, {i , 0}} );
		}
	}

	if (0 >= SelectCropsVector.size())
	{
		return CropTile;
	}

	//SelectCropsLocList.sort();

	FTransform Loc = SelectCropsLocList.front();

	CropTile = UIManager->CroppatchTile->GetTileByLocation(SelectCropsVector[Loc.Location.X]->GetLocation());;

	return CropTile;
}

void ACharacterManager::Watering(FVector2D _Location)
{

}