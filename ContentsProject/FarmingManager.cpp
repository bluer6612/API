#include "PreCompile.h"
#include "FarmingManager.h"
#include "UIManager.h"

AFarmingManager::AFarmingManager()
{
}

AFarmingManager::~AFarmingManager()
{
}


void AFarmingManager::BeginPlay()
{
}

void AFarmingManager::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	_DeltaTime += 0.0001f;
	//AUIManager::CroppatchTile;

}