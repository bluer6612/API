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

// �𸮾󿡼��� MainPawn ���ΰ� ������ �����ϰ� �ؿ�.
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

