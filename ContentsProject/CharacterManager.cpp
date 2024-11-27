#include "PreCompile.h"
#include "CharacterManager.h"

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

	std::vector<class Tile*>::iterator StartIter = UIManager->CropsAllVector.begin();
	std::vector<class Tile*>::iterator EndIter = UIManager->CropsAllVector.end();

	for (int i = 0; i < UIManager->CropsAllVector.size(); ++i)
	{
		UIManager->CropsAllVector[i]->GetWaterNeed();
	}

	return CropTile;
}

void ACharacterManager::Watering(FVector2D _Location)
{

}