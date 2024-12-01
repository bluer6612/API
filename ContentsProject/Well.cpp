#include "PreCompile.h"
#include "Well.h"

AWell::AWell()
{
	Location.X = ScreenHX;
	Location.Y = ScreenHY + 159;

	{
		SpriteR = CreateDefaultSubObject<USpriteRenderer>();
		SpriteR->SetComponentCrate(SpriteR, "000_welltype.png", {}, Location, ERenderOrder::BUILDING);
		SpriteR->CreateAnimation("Idle", "Well", 0, 2, 2.0f);
	}
}

AWell::~AWell()
{
}


void AWell::BeginPlay()
{
	Super::BeginPlay();

	Location.X = ScreenHX;
	Location.Y = ScreenHY + 159;
	UIManager->WellTilesVector.push_back(UIManager->GroundTileMap->GetTileByLocation(Location));
	UIManager->GroundTileMap->GetTileByLocation(Location)->SetLocation(Location);

	FSM.CreateState(NewPlayerState::Idle, std::bind(&AWell::Idle, this, std::placeholders::_1),
		[this]()
		{
			SpriteR->ChangeAnimation("Idle");
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