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
		return CropTile;
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
		if (5 <= UIManager->CropsAllVector[i]->GetProgress())
		{
			FindBool = true;
		}
		else if (true == UIManager->CropsAllVector[i]->GetWaterNeed())
		{
			FindBool = true;
		}

		if (true == FindBool)
		{
			FindBool = false;
			Distance = static_cast<float>(sqrtf(pow(_Location.X - UIManager->CropsAllVector[i]->GetLocation().X, 2) + pow(_Location.Y - UIManager->CropsAllVector[i]->GetLocation().Y, 2)));

			SelectTilesVector[Index] = UIManager->CropsAllVector[i];
			SelectTilesLocVector[Index] = { Distance, static_cast<float>(Index) };
			SelectCropsLocListResult.push_back(static_cast<int>(Distance));

			++Index;
		}
	}

	if (0 == SelectCropsLocListResult.size())
	{
		return CropTile;
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

	SelectTilesVector.clear();
	SelectTilesLocVector.clear();

	SelectTilesVector.resize(UIManager->CropsAllVector.size());
	SelectTilesLocVector.resize(UIManager->CropsAllVector.size());

	int Index = 0;
	float Distance = 0;
	bool FindBool = false;

	for (int i = 0; i < UIManager->CropsAllVector.size(); ++i)
	{
		if (5 <= UIManager->CropsAllVector[i]->GetProgress())
		{
			FindBool = true;
		}
		else if (true == UIManager->CropsAllVector[i]->GetWaterNeed())
		{
			FindBool = true;
		}

		if (true == FindBool)
		{
			FindBool = false;
			Distance = static_cast<float>(sqrtf(pow(_Location.X - UIManager->CropsAllVector[i]->GetLocation().X, 2) + pow(_Location.Y - UIManager->CropsAllVector[i]->GetLocation().Y, 2)));

			SelectTilesVector[Index] = UIManager->CropsAllVector[i];
			SelectTilesLocVector[Index] = { Distance, static_cast<float>(Index) };
			SelectStorageLocListResult.push_back(static_cast<int>(Distance));

			++Index;
		}
	}

	if (0 == SelectStorageLocListResult.size())
	{
		return StorageTile;
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

bool ACharacterManager::Moving(AActor* _Actor, Tile* _Tile, float _DeltaTime)
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

	_Actor->AddActorLocation(Vector * _DeltaTime * 25.f);

	for (size_t i = 0; i < WayDir.size(); i++)
	{
		if (UIManager->CroppatchTile->GetTileByLocation(_Actor->GetActorLocation()) == UIManager->CroppatchTile->GetTileByLocation(_Tile->GetLocation() + (WayDir[i] * 5)))
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
	Money += CropsSellMoney[_Tile->GetCropsIndex()];

	_Tile->AddGrow();
	_Tile->SetProgress(0);
	_Tile->SetWater(0);
	_Tile->SetWaterNeed(true);

	UIManager->CroppatchTile->SetCropsTileSprite(_Tile->GetLocation(), 0);

	UIManager->CroppatchTileImage[_Tile->GetCropTileIndex()]->SetSprite("Crops.png", (3 + _Tile->GetProgress()) + 11 * _Tile->GetCropsIndex());
	_SubActor->SetSprite("Crops.png", (1 + 11 * _Tile->GetCropsIndex()));
	_SubActor->SetActive(true);
}

void ACharacterManager::CarryToStorage(Tile* _Tile)
{
	_Tile->SetWaterNeed(false);

	UIManager->CroppatchTile->SetCropsTileSprite(_Tile->GetLocation(), 2);
}