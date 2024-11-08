#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"
#include "Player.h"
#include "Rusty.h"
#include "Score.h"
#include <EngineCore/EngineAPICore.h>

#include "ContentsEnum.h"

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	ARusty* Rusty = GetWorld()->GetPawn<ARusty>();

	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();


	int a = 0;

	{
		APlayMap* NewActor = GetWorld()->SpawnActor<APlayMap>();
	}

		
					
	}
