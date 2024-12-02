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

std::string ACharacterManager::CalDirection(std::string _Direction, FVector2D _ActorLoc, FVector2D _TileLoc)
{
	std::string TargetDirection = _Direction;

	if (_ActorLoc.X >= _TileLoc.X && _ActorLoc.X - _TileLoc.X > 10.f)
	{
		TargetDirection = "Left";
	}
	else if (_ActorLoc.X <= _TileLoc.X && _TileLoc.X - _ActorLoc.X > 10.f)
	{
		TargetDirection = "Right";
	}
	else if (_ActorLoc.Y >= _TileLoc.Y && _ActorLoc.Y - _TileLoc.Y > 10.f)
	{
		TargetDirection = "Top";
	}
	else if (_ActorLoc.Y <= _TileLoc.Y && _TileLoc.Y - _ActorLoc.Y > 10.f)
	{
		TargetDirection = "Bot";
	}

	return TargetDirection;
}

Tile* ACharacterManager::FindCropTile(FVector2D _Location, int _ActionState)
{
	Tile* CropTile = nullptr;
	std::list<int> SelectCropsLocListResult;

	if (0 >= UIManager->CropsAllVector.size())
	{
		return nullptr;
	}

	SelectTilesVector.clear();
	SelectTilesLocVector.clear();

	SelectTilesVector.resize(UIManager->CropsAllVector.size());
	SelectTilesLocVector.resize(UIManager->CropsAllVector.size());

	int Index = 0;
	float Distance = 0;
	bool FindBool = false;

	for (int i = 0; i < UIManager->CropsAllVector.size(); ++i)
	{
		CropTile = UIManager->CropsAllVector[i];

		if (5 <= CropTile->GetProgress())
		{
			FindBool = true;
		}
		else if (true == CropTile->GetWaterNeed())
		{
			FindBool = true;
		}

		if (true == FindBool)
		{
			FindBool = false;
			Distance = static_cast<float>(sqrtf(pow(_Location.X - CropTile->GetLocation().X, 2) + pow(_Location.Y - CropTile->GetLocation().Y, 2)));

			SelectTilesVector[Index] = CropTile;
			SelectTilesLocVector[Index] = { Distance, static_cast<float>(Index) };
			SelectCropsLocListResult.push_back(static_cast<int>(Distance));

			++Index;
		}
	}

	if (0 == SelectCropsLocListResult.size())
	{
		return nullptr;
	}

	SelectCropsLocListResult.sort();

	int StartIter = SelectCropsLocListResult.front();

	Index = 0;
	for (int i = 0; i < SelectTilesLocVector.size(); ++i)
	{
		if (StartIter == static_cast<int>(SelectTilesLocVector[Index].X))
		{
			break;
		}

		++Index;
	}

	CropTile = SelectTilesVector[static_cast<int>(SelectTilesLocVector[Index].Y)];

	SelectCropsLocListResult.clear();

	return CropTile;
}

Tile* ACharacterManager::FindStorage(FVector2D _Location, int _ActionState)
{
	Tile* StorageTile = nullptr;
	std::list<int> SelectStorageLocListResult;
	std::vector<class Tile*> TargetTilesVector;

	SelectTilesVector.clear();
	SelectTilesLocVector.clear();

	if (3 == _ActionState)
	{
		TargetTilesVector = UIManager->StorageTilesVector;
	}
	else if (6 == _ActionState)
	{
		TargetTilesVector = UIManager->WellTilesVector;
	}

	SelectTilesVector.resize(TargetTilesVector.size());
	SelectTilesLocVector.resize(TargetTilesVector.size());

	int Index = 0;
	float Distance = 0;

	for (int i = 0; i < TargetTilesVector.size(); ++i)
	{
		StorageTile = TargetTilesVector[i];
		Distance = static_cast<float>(sqrtf(pow(_Location.X - StorageTile->GetLocation().X, 2) + pow(_Location.Y - StorageTile->GetLocation().Y, 2)));

		SelectTilesVector[Index] = StorageTile;
		SelectTilesLocVector[Index] = { Distance, static_cast<float>(Index) };
		SelectStorageLocListResult.push_back(static_cast<int>(Distance));

		++Index;
	}

	if (0 == SelectStorageLocListResult.size())
	{
		return nullptr;
	}

	SelectStorageLocListResult.sort();

	int StartIter = SelectStorageLocListResult.front();

	Index = 0;
	for (int i = 0; i < SelectTilesLocVector.size(); ++i)
	{
		if (StartIter == static_cast<int>(SelectTilesLocVector[Index].X))
		{
			break;
		}

		++Index;
	}

	StorageTile = SelectTilesVector[static_cast<int>(SelectTilesLocVector[Index].Y)];

	SelectStorageLocListResult.clear();

	return StorageTile;
}

bool ACharacterManager::Moving(AActor* _Actor, Tile* _Tile, float _DeltaTime, int _ActionState)
{
	FVector2D Vector = FVector2D::ZERO;

	FVector2D _ActorLoc = _Actor->GetActorLocation();
	FVector2D _TileLoc = _Tile->GetLocation();

	if (_ActorLoc.X >= _TileLoc.X && _ActorLoc.X - _TileLoc.X > 1.f)
	{
		Vector += FVector2D::LEFT;
	}
	else if (_ActorLoc.X <= _TileLoc.X && _TileLoc.X - _ActorLoc.X > 1.f)
	{
		Vector += FVector2D::RIGHT;
	}
	else if (_ActorLoc.Y >= _TileLoc.Y && _ActorLoc.Y - _TileLoc.Y > 1.f)
	{
		Vector += FVector2D::UP;
	}
	else if (_ActorLoc.Y <= _TileLoc.Y && _TileLoc.Y - _ActorLoc.Y > 1.f)
	{
		Vector += FVector2D::DOWN;
	}

	Vector.Normalize();

	_Actor->AddActorLocation(Vector * _DeltaTime * 30.f);

	for (size_t i = 0; i < WayDir.size(); i++)
	{
		if (3 == _ActionState && UIManager->GroundTileMap->GetTileByLocation(_Actor->GetActorLocation()) == UIManager->GroundTileMap->GetTileByLocation(_Tile->GetLocation() + (WayDir[i] * 5)))
		{
			return true;
		}
		else if (6 == _ActionState && UIManager->GroundTileMap->GetTileByLocation(_Actor->GetActorLocation()) == UIManager->GroundTileMap->GetTileByLocation(_Tile->GetLocation() + (WayDir[i] * 5)))
		{
			return true;
		}
		else if (4 == _ActionState && UIManager->CroppatchTile->GetTileByLocation(_Actor->GetActorLocation()) == UIManager->CroppatchTile->GetTileByLocation(_Tile->GetLocation() + (WayDir[i] * 5)))
		{
			return true;
		}
		else if (5 == _ActionState && UIManager->CroppatchTile->GetTileByLocation(_Actor->GetActorLocation()) == UIManager->CroppatchTile->GetTileByLocation(_Tile->GetLocation() + (WayDir[i] * 5)))
		{
			return true;
		}
		
	}

	return false;
}

void ACharacterManager::Watering(Tile* _Tile)
{
	_Tile->SetWaterNeed(false);

	UIManager->CroppatchTile->SetCropsTileSprite(_Tile->GetLocation(), 2);
}

void ACharacterManager::Havesting(Tile* _Tile, USpriteRenderer* _SubActor)
{
	int CropIndex = _Tile->GetCropsIndex();
	USpriteRenderer* _TileImage = UIManager->CroppatchTileImage[_Tile->GetCropTileIndex()];

	UIManager->CropsCountText[CropIndex]->SetValue(++UIManager->CropsCountText[CropIndex]->ValueData);
	Money += CropsSellMoney[CropIndex];
	UIManager->ResourcesText[0]->SetValue(Money);
	UIManager->ResourcesText[2]->SetValue(Money);

	UIManager->CroppatchTile->SetCropsTileSprite(_Tile->GetLocation(), 0);

	_SubActor->SetCount(CropIndex);
	_SubActor->SetSprite("Crops.png", (1 + 11 * CropIndex));
	_SubActor->SetActive(true);

	_Tile->AddGrow();

	if (CropsNeedRegrow[CropIndex] >= _Tile->GetGrow())
	{
		_Tile->CropsReset(0, -1);

		_TileImage->SetActive(false);

		UIManager->CropsAllVector.erase(remove(UIManager->CropsAllVector.begin(), UIManager->CropsAllVector.end(), _Tile), UIManager->CropsAllVector.end());
	}
	else
	{
		_Tile->SetTime(0);
		_Tile->SetProgress(0);
		_Tile->SetWater(0);
		_Tile->SetWaterNeed(true);

		_TileImage->SetSprite("Crops.png", (3 + _Tile->GetProgress()) + 11 * CropIndex);
	}
}

void ACharacterManager::CarryToStorage(Tile* _Tile, USpriteRenderer* _SubActor)
{
	++(UIManager->FarmingStats[_SubActor->GetCount()]);
	_SubActor->SetCount(0);
	_SubActor->SetActive(false);
}