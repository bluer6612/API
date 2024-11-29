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

Tile* ACharacterManager::FindTile(FVector2D _Location)
{
	Tile* CropTile = nullptr;
	std::list<int> SelectCropsLocListResult;

	if (0 >= UIManager->CropsAllVector.size())
	{
		return CropTile;
	}

	SelectCropsVector.clear();
	SelectCropsLocVector.clear();

	SelectCropsVector.resize(UIManager->CropsAllVector.size());
	SelectCropsLocVector.resize(UIManager->CropsAllVector.size());

	float Distance;
	int Index = 0;

	for (int i = 0; i < UIManager->CropsAllVector.size(); ++i)
	{
		if (true == UIManager->CropsAllVector[i]->GetWaterNeed())
		{
			SelectCropsVector[Index] = UIManager->CropsAllVector[i];
			Distance = static_cast<float>(sqrtf(pow(_Location.X - UIManager->CropsAllVector[i]->GetLocation().X, 2) + pow(_Location.Y - UIManager->CropsAllVector[i]->GetLocation().Y, 2)));
			SelectCropsLocVector[Index] = { Distance, static_cast<float>(Index) };
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
	for (int i = 0; i < SelectCropsLocVector.size(); ++i)
	{
		if (StartIter == static_cast<int>(SelectCropsLocVector[Index].X))
		{
			break;
		}

		++Index;
	}

	CropTile = SelectCropsVector[static_cast<int>(SelectCropsLocVector[Index].Y)];

	SelectCropsLocListResult.clear();

	return CropTile;
}

bool ACharacterManager::Moving(AActor* _Actor, Tile* _Tile, float _DeltaTime)
{
	FVector2D Vector = FVector2D::ZERO;

	FVector2D _ActorLoc = _Actor->GetActorLocation();
	FVector2D _TileLoc = _Tile->GetLocation();

	if (_ActorLoc.X >= _TileLoc.X && _ActorLoc.X - _TileLoc.X > 3.f)
	{
		Vector += FVector2D::LEFT;
	}
	else if (_ActorLoc.X <= _TileLoc.X && _TileLoc.X - _ActorLoc.X > 3.f)
	{
		Vector += FVector2D::RIGHT;
	}
	else if (_ActorLoc.Y >= _TileLoc.Y && _ActorLoc.Y - _TileLoc.Y > 3.f)
	{
		Vector += FVector2D::UP;
	}
	else if (_ActorLoc.Y <= _TileLoc.Y && _TileLoc.Y - _ActorLoc.Y > 3.f)
	{
		Vector += FVector2D::DOWN;
	}

	Vector.Normalize();

	_Actor->AddActorLocation(Vector * _DeltaTime * 25.f);

	for (size_t i = 0; i < WayDir.size(); i++)
	{
		if (UIManager->CroppatchTile->GetTileByLocation(_Actor->GetActorLocation()) == UIManager->CroppatchTile->GetTileByLocation(_Tile->GetLocation() + (WayDir[i] * 1)))
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