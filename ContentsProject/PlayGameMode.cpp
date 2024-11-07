#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"
#include "Player.h"
#include "ANewPlayer.h"
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
					
			
				
			
	ANewPlayer* Player = GetWorld()->GetPawn<ANewPlayer>();
	Player->SetColImage("bg001_Col.png");

	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();


	int a = 0;

	{
		APlayMap* NewActor = GetWorld()->SpawnActor<APlayMap>();
	}

		
					
	}
