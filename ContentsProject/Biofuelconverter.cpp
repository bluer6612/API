#include "PreCompile.h"
#include "Biofuelconverter.h"

ABiofuelconverter::ABiofuelconverter()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Biofuelconverter");
		SpriteRenderer->CreateAnimation("Idle", "Biofuelconverter", 0, 0, 1.0f);
		SpriteRenderer->SetComponentScale({ static_cast<float>(55 * 2), static_cast<float>(57 * 2) });
		SpriteRenderer->SetComponentLocation({ static_cast<float>(ScreenX * 0.5 - 197), static_cast<float>((ScreenY * 0.3) * 0.275) });
		SpriteRenderer->SetOrder(10);
	}

	{
		ModelAdd("Biofuelconverter", 1, 25, 25, -197, 0, 12);
		ModelAdd("Biofuelconverter", 2, 15, 15, -197, 25, 11);
		ModelAdd("Biofuelconverter", 2, 15, 15, -197, 75, 11);
		ModelAdd("Biofuelconverter", 2, 15, 15, -197, -25, 11);
	}
}

ABiofuelconverter::~ABiofuelconverter()
{
}


void ABiofuelconverter::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);

	FSM.CreateState(NewPlayerState::Idle, std::bind(&ABiofuelconverter::Idle, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Idle");
		}
	);

	FSM.ChangeState(NewPlayerState::Idle);
}

void ABiofuelconverter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FSM.Update(_DeltaTime);
}

void ABiofuelconverter::Idle(float _DeltaTime)
{
	return;
}