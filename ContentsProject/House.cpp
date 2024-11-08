#include "PreCompile.h"
#include "House.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"

AHouse::AHouse()
{
	{
		SetActorLocation({ static_cast<float>(ScreenX * 0.5), static_cast<float>((ScreenY * 0.3) * 0.275) });
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("House");
		SpriteRenderer->CreateAnimation("Idle", "House", 4, 4, 0);
		SpriteRenderer->SetSpriteScale(5.75f);
	}

	{
		SetActorLocation({ static_cast<float>(ScreenX * 0.5), static_cast<float>((ScreenY * 0.3) * 0.4) });
		SpriteRendererWheel = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRendererWheel->SetSprite("House");
		SpriteRendererWheel->CreateAnimation("Idle", "House", 9, 11, 0.5f);
	}
}

AHouse::~AHouse()
{
}

void AHouse::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);

	FSM.CreateState(NewPlayerState::Idle, std::bind(&AHouse::Idle, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Idle");
			SpriteRendererWheel->ChangeAnimation("Idle");
		}
	);

	FSM.ChangeState(NewPlayerState::Idle);
}

void AHouse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FSM.Update(_DeltaTime);
}

void AHouse::Idle(float _DeltaTime)
{
	return;
}