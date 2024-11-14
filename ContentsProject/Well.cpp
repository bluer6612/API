#include "PreCompile.h"
#include "Well.h"

AWell::AWell()
{
	Location.X = ScreenHX;
	Location.Y = ScreenHY + 159;

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Well");
		SpriteRenderer->CreateAnimation("Idle", "Well", 0, 2, 2.0f);
		SpriteRenderer->SetComponentScaleOrigin();
		SpriteRenderer->SetComponentLocation({ Location.X, Location.Y });
		SpriteRenderer->SetOrder(ERenderOrder::BUILDING);
	}
}

AWell::~AWell()
{
}


void AWell::BeginPlay()
{
	Super::BeginPlay();

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

	//FSM.Update(_DeltaTime);
}

void AWell::Idle(float _DeltaTime)
{
}