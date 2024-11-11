#include "PreCompile.h"
#include "PlayGameMode.h"
#include "TitleLogo.h"
#include "PlayMap.h"

#include "Rusty.h"
#include "House.h"

#include <EnginePlatform/EngineInput.h>

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	ARusty* Rusty = AActor::GetWorld()->GetPawn<ARusty>();

	AHouse* House = AActor::GetWorld()->SpawnActor<AHouse>();

	{
		//TitleLogo* NewActor = AActor::GetWorld()->SpawnActor<TitleLogo>();
	}

	{
		APlayMap* NewActor = AActor::GetWorld()->SpawnActor<APlayMap>();
	}
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('B'))
	{
		//SetActiveSwitch();
	}

}