#include "PreCompile.h"
#include "House.h"

AHouse::AHouse()
{
	Location.X = ScreenHX;
	Location.Y = ScreenHY + 2.5;

	{

		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("004_House.png");
		SpriteRenderer->CreateAnimation("Idle", "House", 4, 4, 0, false);
		SpriteRenderer->SetComponentScale({ static_cast<float>(86 * 2), static_cast<float>(96 * 2) });
		SpriteRenderer->SetComponentLocation({ ScreenHX, Location.Y });
		SpriteRenderer->SetOrder(ERenderOrder::BUILDING);
	}

	{
		SpriteRendererWheel = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRendererWheel->SetSprite("009_House.png");
		SpriteRendererWheel->CreateAnimation("Idle_Wheel", "House", 9, 11, 0.5f, false);
		SpriteRendererWheel->SetComponentLocation({ ScreenHX, Location.Y + 10 });
		SpriteRendererWheel->SetOrder(11);
	}

	{
		SpriteRendererDoor = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRendererDoor->SetSprite("000_House.png");
		SpriteRendererDoor->CreateAnimation("Idle_Door", "House", 0, 1, 0.5f, false);
		SpriteRendererDoor->SetComponentLocation({ ScreenHX, Location.Y + 67 });
	}

	{
		MoneySpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MoneySpriteRenderer->SetSprite("022_Housebiofuelspareparts.png");
		MoneySpriteRenderer->SetComponentLocation({ ScreenHX,  ScreenHY + 227 });
		MoneySpriteRenderer->SetOrder(ERenderOrder::UI);
	}

	{
		ModelAdd("002_House.png", -112.5, 225 - 3, 7);
		ModelAdd("002_House.png", -47.5, 219 - 3, 7);
		ModelAdd("002_House.png", 70, 220 - 3, 7);
		ModelAdd("003_House.png", 15, 224 - 3, 7);
		ModelAdd("003_House.png", 104, 225 - 3, 7);
		ModelAdd("003_House.png", 95, 20 - 3, 8);
		ModelAdd("005_House.png", 80, 60 - 3, 9);
		ModelAdd("006_House.png", 95, 60 - 3, 8);
		ModelAdd("007_House.png", 0, 147.5 - 3, 7);
		ModelAdd("013_House.png", 72.5, 175 - 3, 7);
		ModelAdd("015_House.png", -76, -21 - 3, 7);
		ModelAdd("016_House.png", 87.5, 107.5 - 3, 8);
		ModelAdd("017_House.png", 80, -20 - 3, 6);
		ModelAdd("018_House.png", -80, 77 - 3, 7);
		ModelAdd("019_House.png", -76, 161 - 3, 7);
		ModelAdd("020_House.png", -88, 23 - 3, 7);
		ModelAdd("021_House.png", -90, 210 - 3, 7);
	}
}

AHouse::~AHouse()
{
}

void AHouse::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(NewPlayerState::Idle, std::bind(&AHouse::Idle, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Idle");
			//SpriteRendererWheel->ChangeAnimation("Idle_Wheel");
			//SpriteRendererDoor->ChangeAnimation("Idle_Door");
		}
	);

	FSM.ChangeState(NewPlayerState::Idle);
}

void AHouse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//FSM.Update(_DeltaTime);
}

void AHouse::Idle(float _DeltaTime)
{
}