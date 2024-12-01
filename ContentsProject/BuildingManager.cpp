#include "PreCompile.h"
#include "BuildingManager.h"

ABuildingManager::ABuildingManager()
{
}

ABuildingManager::~ABuildingManager()
{
}

void ABuildingManager::BeginPlay()
{
	Super::BeginPlay();
}

void ABuildingManager::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ABuildingManager::ModelAdd(std::string_view _Name, double _X, double _Y, int _Order)
{
	Model[index] = CreateDefaultSubObject<USpriteRenderer>();
	Model[index]->SetSprite(_Name);
	Model[index]->SetSpriteScale();
	Model[index]->SetComponentLocation({ static_cast<float>(Location.X + _X), static_cast<float>(Location.Y + _Y) });
	Model[index]->SetOrder(_Order);
	++index;
}