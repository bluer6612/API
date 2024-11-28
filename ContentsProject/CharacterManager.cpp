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

std::string ACharacterManager::CalDirection(FVector2D _ActorLoc, FVector2D _TileLoc)
{
	std::string _Direction = "";

	_ActorLoc;
	_TileLoc;

	if (_ActorLoc.X - _TileLoc.X >= _ActorLoc.Y - _TileLoc.Y)
	{
		if (_ActorLoc.X >= _TileLoc.X)
		{
			_Direction = "Left";
		}
		else if (_ActorLoc.X <= _TileLoc.X)
		{
			_Direction = "Right";
		}
	}
	else
	{
		if (_ActorLoc.Y >= _TileLoc.Y)
		{
			_Direction = "Top";
		}
		else if (_ActorLoc.Y <= _TileLoc.Y)
		{
			_Direction = "Bot";
		}
	}

	return _Direction;
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

	if (1 < SelectCropsLocListResult.size())
	{
		SelectCropsLocListResult.sort();
	}


	int StartIter = SelectCropsLocListResult.front();

	Index = 0;
	for (int i = 0; i < SelectCropsLocVector.size(); ++i)
	{
		int a = StartIter;
		int b = static_cast<int>(SelectCropsLocVector[Index].X);
		int c = 0;
		if (StartIter == static_cast<int>(SelectCropsLocVector[Index].X))
		{
			int d = static_cast<int>(SelectCropsLocVector[Index].Y);
			int g = 0;
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
	FVector2D Vector = FVector2D::LEFT;

	Vector.Normalize();

	_Actor->AddActorLocation(Vector * _DeltaTime * 30.f);

	for (size_t i = 0; i < WayDir.size(); i++)
	{
		if (UIManager->CroppatchTile->GetTileByLocation(_Actor->GetActorLocation()) == UIManager->CroppatchTile->GetTileByLocation(_Tile->GetLocation() + (WayDir[i] * 38)))
		{
			return true;
		}
		
	}

	return false;


	//FVector2D Vector = FVector2D::LEFT;

	//if (true == UEngineInput::GetInst().IsPress('D'))
	//{
	//	Vector += FVector2D::RIGHT;
	//}
	//if (true == UEngineInput::GetInst().IsPress('A'))
	//{
	//	Vector += FVector2D::LEFT;
	//}
	//if (true == UEngineInput::GetInst().IsPress('S'))
	//{
	//	Vector += FVector2D::DOWN;
	//}
	//if (true == UEngineInput::GetInst().IsPress('W'))
	//{
	//	Vector += FVector2D::UP;
	////}

	//Vector.Normalize();

	//if (true == IsMove)
	//{
	//	AddActorLocation(Vector * _DeltaTime * Speed);
	//}

	//if (false == UEngineInput::GetInst().IsPress('A') &&
	//	false == UEngineInput::GetInst().IsPress('D') &&
	//	false == UEngineInput::GetInst().IsPress('W') &&
	//	false == UEngineInput::GetInst().IsPress('S'))
	//{
	//	FSM.ChangeState(NewPlayerState::Idle);
	//	return;
	//}
}

void ACharacterManager::Watering(Tile* _Tile)
{
	_Tile->SetWaterNeed(false);

	UIManager->CroppatchTile->SetCropsTileSprite(_Tile->GetLocation(), 2);
}