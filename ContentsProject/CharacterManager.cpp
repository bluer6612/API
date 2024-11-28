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

	if (1 < SelectCropsLocListResult.size())
	{
		SelectCropsLocListResult.sort();
	}

	Index = 0;

	int i = 0;
	std::list<int>::iterator StartIter = SelectCropsLocListResult.begin();
	std::list<int>::iterator EndIter = SelectCropsLocListResult.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		i = *StartIter;
		int a = static_cast<int>(SelectCropsLocVector[Index].X);
		if (i == static_cast<int>(SelectCropsLocVector[Index].X))
		{
			break;
		}

		++Index;
	}

	SelectCropsLocListResult.clear();

	CropTile = SelectCropsVector[Index];

	return CropTile;
}

bool ACharacterManager::Moving(AActor* _Actor, Tile* _Tile, float _DeltaTime)
{
	FVector2D Vector = FVector2D::LEFT;

	Vector.Normalize();

	_Actor->AddActorLocation(Vector * _DeltaTime * 30.f);

	for (size_t i = 0; i < WayDir.size(); i++)
	{
		if (UIManager->CroppatchTile->GetTileByLocation(_Actor->GetActorLocation()) == UIManager->CroppatchTile->GetTileByLocation(_Tile->GetLocation() + (WayDir[i] * 34)))
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