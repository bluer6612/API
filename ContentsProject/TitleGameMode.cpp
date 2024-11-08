#include "PreCompile.h"
#include "TitleGameMode.h"
#include "TitleLogo.h"
#include "PlayMap.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	//Super::BeginPlay();

	{
		TitleLogo* NewActor = GetWorld()->SpawnActor<TitleLogo>();
	}

	{
		APlayMap* NewActor = GetWorld()->SpawnActor<APlayMap>();
	}
}


void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Play");
	}

}