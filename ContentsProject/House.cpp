#include "PreCompile.h"
#include "House.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"

int index = 0;
USpriteRenderer* Model[10] = { };

AHouse::AHouse()
{

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("House");
		SpriteRenderer->CreateAnimation("Idle", "House", 4, 4, 0);
		SpriteRenderer->SetComponentScale({ static_cast<float>(86 * 2), static_cast<float>(96 * 2) });
		SpriteRenderer->SetComponentLocation({ static_cast<float>(ScreenX * 0.5), static_cast<float>((ScreenY * 0.3) * 0.275 + 2.5) });
		SpriteRenderer->SetOrder(10);
	}

	{
		SpriteRendererWheel = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRendererWheel->SetSprite("House");
		SpriteRendererWheel->CreateAnimation("Idle", "House", 9, 11, 0.5f);
		SpriteRendererWheel->SetComponentLocation({ static_cast<float>(ScreenX * 0.5), static_cast<float>((ScreenY * 0.3) * 0.275 + 10) });
		SpriteRendererWheel->SetOrder(11);
	}

	{
		SpriteRendererDoor = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRendererDoor->SetSprite("House");
		SpriteRendererDoor->CreateAnimation("Idle", "House", 0, 1, 0.5f);
		SpriteRendererDoor->SetComponentLocation({ static_cast<float>(ScreenX * 0.5), static_cast<float>((ScreenY * 0.3) * 0.275 + 67) });
	}

	{
		Model[index] = CreateDefaultSubObject<USpriteRenderer>();
		Model[index]->SetSprite("House");
		Model[index]->CreateAnimation("Idle", "House", 5, 5, 0);
		Model[index]->SetComponentScale({ static_cast<float>(16 * 2), static_cast<float>(32 * 2) });
		Model[index]->SetComponentLocation({ static_cast<float>(ScreenX * 0.5 + 80), static_cast<float>((ScreenY * 0.3) * 0.275 + 60) });
		Model[index]->SetOrder(9);
		++index;
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
			SpriteRendererDoor->ChangeAnimation("Idle");
			for (size_t i = 0; i < index; i++)
			{
				Model[i]->ChangeAnimation("Idle");
			}
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