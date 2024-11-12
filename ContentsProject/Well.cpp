#include "PreCompile.h"
#include "Well.h"

AWell::AWell()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Well");
		SpriteRenderer->CreateAnimation("Idle", "Well", 0, 2, 2.0f);
		SpriteRenderer->SetComponentScale({ static_cast<float>(42 * 2), static_cast<float>(36 * 2) });
		SpriteRenderer->SetComponentLocation({ static_cast<float>(ScreenX * 0.5), static_cast<float>((ScreenY * 0.3) * 0.275 + 160) });
		SpriteRenderer->SetOrder(10);
	}
}

AWell::~AWell()
{
}


void AWell::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);

	FSM.CreateState(NewPlayerState::Idle, std::bind(&AWell::Idle, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Idle");
		}
	);

	FSM.ChangeState(NewPlayerState::Idle);
}

void AWell::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FSM.Update(_DeltaTime);
}

void AWell::Idle(float _DeltaTime)
{
	return;
}