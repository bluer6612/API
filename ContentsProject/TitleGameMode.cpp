#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include "PlayMap.h"
#include "Player.h"

#include "TitleLogo.h"

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}

// 언리얼에서는 MainPawn 주인공 무조건 지정하게 해요.
void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	//TitleLogo* NewActor = GetWorld()->GetPawn<TitleLogo>();
	//NewActor->SetColImage("bg001_Col.png");
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Play");
	}

}
