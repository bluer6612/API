#include "PreCompile.h"
#include "HaikuHouse.h"

AHaikuHouse::AHaikuHouse()
{
	FVector2D Location = { static_cast<float>(ScreenX * 0.5 + 220), static_cast<float>((ScreenY - 243)) };

	{
		SpriteR = CreateDefaultSubObject<USpriteRenderer>();
		SpriteR->SetComponentCrate(SpriteR, "haikus-house-pieces_3.png", {}, Location, ERenderOrder::BUILDINGUP);
	}
	{
		Model[0] = CreateDefaultSubObject<USpriteRenderer>();
		Model[0]->SetComponentCrate(Model[0], "haikus-house-pieces_2.png", {}, { Location.X - 50, Location.Y }, ERenderOrder::BUILDING);
	}
	{
		Model[1] = CreateDefaultSubObject<USpriteRenderer>();
		Model[1]->SetComponentCrate(Model[1], "haikus-house-pieces_4.png", {}, { Location.X, Location.Y + 50 }, ERenderOrder::BUILDING);
	}
	{
		Model[2] = CreateDefaultSubObject<USpriteRenderer>();
		Model[2]->SetComponentCrate(Model[2], "haikus-house-pieces_1.png", {}, { Location.X - 50, Location.Y + 50 }, ERenderOrder::BUILDINGDOWN);
	}
}

AHaikuHouse::~AHaikuHouse()
{
}

void AHaikuHouse::BeginPlay()
{
	Super::BeginPlay();
}

void AHaikuHouse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//FSM.Update(_DeltaTime);
}

void AHaikuHouse::Idle(float _DeltaTime)
{
}