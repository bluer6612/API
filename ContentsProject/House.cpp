#include "PreCompile.h"
#include "House.h"

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
		ModelAdd("House", 2, 16, 16, -112.5, 225, 7);
		ModelAdd("House", 2, 16, 16, -47.5, 219, 7);
		ModelAdd("House", 2, 16, 16, 70, 220, 7);
		ModelAdd("House", 3, 16, 16, 15, 224, 7);
		ModelAdd("House", 3, 16, 16, 104, 225, 7);
		ModelAdd("House", 3, 1.f, 95, 20, 8);
		ModelAdd("House", 5, 16, 32, 80, 60, 9);
		ModelAdd("House", 6, 16, 32, 95, 60, 8);
		ModelAdd("House", 8, 64, 48, 0, 147.5, 7);
		ModelAdd("House", 13, 16, 16, 72.5, 175, 7);
		ModelAdd("House", 15, 32, 32, -76, -21, 7);
		ModelAdd("House", 16, 16, 16, 87.5, 107.5, 8);
		ModelAdd("House", 17, 16, 32, 80, -20, 6);
		ModelAdd("House", 18, 16, 16, -80, 77, 7);
		ModelAdd("House", 19, 32, 16, -76, 161, 7);
		ModelAdd("House", 20, 16, 16, -88, 23, 7);
		ModelAdd("House", 21, 16, 16, -90, 210, 7);
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