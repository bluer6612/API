#include "PreCompile.h"
#include "House.h"

AHouse::AHouse()
{
	Location.X = static_cast<float>(ScreenX * 0.5);
	Location.Y = static_cast<float>(ScreenY * 0.3 * 0.275) + 2.5;

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("004_House.png");
		SpriteRenderer->SetComponentScale({ static_cast<float>(86 * 2), static_cast<float>(96 * 2) });
		SpriteRenderer->SetComponentLocation({ Location.X, Location.Y });
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
		ModelAdd("002_House.png", 16, 16, -112.5, 225 - 2, 7);
		ModelAdd("002_House.png", 16, 16, -47.5, 219 - 2, 7);
		ModelAdd("002_House.png", 16, 16, 70, 220 - 2, 7);
		ModelAdd("003_House.png", 16, 16, 15, 224 - 2, 7);
		ModelAdd("003_House.png", 16, 16, 104, 225 - 2, 7);
		ModelAdd("003_House.png", 16, 16, 95, 20 - 2, 8);
		ModelAdd("005_House.png", 16, 32, 80, 60 - 2, 9);
		ModelAdd("006_House.png", 16, 32, 95, 60 - 2, 8);
		ModelAdd("007_House.png", 64, 48, 0, 147.5 - 2, 7);
		ModelAdd("013_House.png", 16, 16, 72.5, 175 - 2, 7);
		ModelAdd("015_House.png", 32, 32, -76, -21 - 2, 7);
		ModelAdd("016_House.png", 16, 16, 87.5, 107.5 - 2, 8);
		ModelAdd("017_House.png", 16, 32, 80, -20 - 2, 6);
		ModelAdd("018_House.png", 16, 16, -80, 77 - 2, 7);
		ModelAdd("019_House.png", 32, 16, -76, 161 - 2, 7);
		ModelAdd("020_House.png", 16, 16, -88, 23 - 2, 7);
		ModelAdd("021_House.png", 16, 16, -90, 210 - 2, 7);
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
			SpriteRendererWheel->ChangeAnimation("Idle");
			SpriteRendererDoor->ChangeAnimation("Idle");
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