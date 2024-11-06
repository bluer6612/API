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

//void TitleLogo::SetColImage(std::string_view _ColImageName)
//{
//	ColImage = UImageManager::GetInst().FindImage(_ColImageName);
//}

// 언리얼에서는 MainPawn 주인공 무조건 지정하게 해요.
void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	TitleLogo* NewActor = GetWorld()->GetPawn<TitleLogo>();

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

