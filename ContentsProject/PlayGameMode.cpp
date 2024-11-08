#include "PreCompile.h"
#include "PlayGameMode.h"

#include "Rusty.h"
#include "PlayMap.h"

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

	{
		TitleLogo* NewActor = AActor::GetWorld()->SpawnActor<TitleLogo>();
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