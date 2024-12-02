#include "PreCompile.h"
#include "Haiku.h"

#include "ContentsEnum.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

AHaiku::AHaiku()
{
	SetActorLocation({ static_cast<float>(ScreenX * 0.5 + 220), static_cast<float>((ScreenY - 243) + 76) });

	{
		SpriteR = CreateDefaultSubObject<USpriteRenderer>();
		SpriteR->SetSprite("Haiku");
		SpriteR->SetSpriteScale(1.75f);
		SpriteR->SetOrder(ERenderOrder::PLAYER);

		SpriteR->CreateAnimation("Idle_Bot", "Haiku", 48, 49, 0.6f);
		SpriteR->CreateAnimation("Idle_Top", "Haiku", 50, 51, 0.6f);
		SpriteR->CreateAnimation("Idle_Right", "Haiku", 52, 53, 0.6f);
		SpriteR->CreateAnimation("Idle_Left", "Haiku", 54, 55, 0.6f);
		SpriteR->CreateAnimation("Run_Bot", "Haiku", 0, 5, 0.2f);
		SpriteR->CreateAnimation("Run_Top", "Haiku", 6, 11, 0.2f);
		SpriteR->CreateAnimation("Run_Right", "Haiku", 12, 17, 0.2f);
		SpriteR->CreateAnimation("Run_Left", "Haiku", 18, 23, 0.2f);
		SpriteR->CreateAnimation("Water_Bot", "Haiku", 24, 27, 0.5f);
		SpriteR->CreateAnimation("Water_Top", "Haiku", 28, 31, 0.5f);
		SpriteR->CreateAnimation("Water_Right", "Haiku", 32, 35, 0.5f);
		SpriteR->CreateAnimation("Water_Left", "Haiku", 36, 39, 0.5f);
		SpriteR->CreateAnimation("WaterGet_Bot", "Haiku", 40, 40, 0.75f);
		SpriteR->CreateAnimation("WaterGet_Top", "Haiku", 44, 44, 0.75f);
		SpriteR->CreateAnimation("WaterGet_Right", "Haiku", 48, 48, 0.75f);
		SpriteR->CreateAnimation("WaterGet_Left", "Haiku", 52, 52, 0.75f);
		SpriteR->CreateAnimation("Harvest_Bot", "Haiku", 40, 41, 0.5f);
		SpriteR->CreateAnimation("Harvest_Top", "Haiku", 42, 43, 0.5f);
		SpriteR->CreateAnimation("Harvest_Right", "Haiku", 44, 45, 0.5f);
		SpriteR->CreateAnimation("Harvest_Left", "Haiku", 46, 47, 0.5f);
		SpriteR->CreateAnimation("HarvestCarry_Bot", "Haiku", 65, 70, 0.2f);
		SpriteR->CreateAnimation("HarvestCarry_Top", "Haiku", 71, 76, 0.2f);
		SpriteR->CreateAnimation("HarvestCarry_Right", "Haiku", 77, 82, 0.2f);
		SpriteR->CreateAnimation("HarvestCarry_Left", "Haiku", 83, 88, 0.2f);

		SpriteRSub = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRSub->SetSprite("EmptyTile.png");
		SpriteRSub->SetComponentScale({ 32, 64 });
		SpriteRSub->SetOrder(ERenderOrder::BUILDINGUP);
		SpriteRSub->SetPivotValue({ 0.5f, 1.25f });
		SpriteRSub->SetActive(false);
	}
}

AHaiku::~AHaiku()
{
}

void AHaiku::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);

	FSM.CreateState(NewPlayerState::Idle, std::bind(&AHaiku::Idle, this, std::placeholders::_1),
		[this]()
		{
			SpriteR->ChangeAnimation("Idle_" + Direction);
		}
	);

	FSM.CreateState(NewPlayerState::Move, std::bind(&AHaiku::Move, this, std::placeholders::_1),
		[this]()
		{
			SpriteR->ChangeAnimation("Run_" + Direction);
		}
	);

	FSM.CreateState(NewPlayerState::Water, std::bind(&AHaiku::Water, this, std::placeholders::_1),
		[this]()
		{
			SpriteR->ChangeAnimation("Water_" + Direction);
		}
	);

	FSM.CreateState(NewPlayerState::WaterGet, std::bind(&AHaiku::WaterGet, this, std::placeholders::_1),
		[this]()
		{
			SpriteR->ChangeAnimation("WaterGet_" + Direction);
		}
	);

	FSM.CreateState(NewPlayerState::Harvest, std::bind(&AHaiku::Harvest, this, std::placeholders::_1),
		[this]()
		{
			SpriteR->ChangeAnimation("Harvest_" + Direction);
		}
	);

	FSM.CreateState(NewPlayerState::HarvestCarry, std::bind(&AHaiku::HarvestCarry, this, std::placeholders::_1),
		[this]()
		{
			SpriteR->ChangeAnimation("HarvestCarry_" + Direction);
		}
	);

	FSM.ChangeState(NewPlayerState::Idle);
}

void AHaiku::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FVector2D Location = GetActorLocation();
	std::string BeforeDirection = Direction;

	if (3 == ActionState || 6 == ActionState) //수확물 운반
	{
		TargetTile = FindStorage(Location, ActionState);
	}
	else if (TargetTile == nullptr)
	{
		TargetTile = FindCropTile(Location, ActionState);
		return;
	}
	else if (0 == ActionState)
	{
		Direction = CalDirection(Direction, Location, TargetTile->GetLocation());
		FSM.ChangeState(NewPlayerState::Move);
	}

	if (3 == ActionState) //수확물 운반
	{
		ActionState = 3;
	}
	else if (0 == ActionState && 5 <= TargetTile->GetProgress()) //수확
	{
		ActionState = 4;
	}
	else if (0 == ActionState && 0 < WaterCount) //물 주기
	{
		ActionState = 5;
	}

	if (0 < ActionState)
	{
		Direction = CalDirection(Direction, Location, TargetTile->GetLocation());
		if (Direction != BeforeDirection)
		{
			if (3 == ActionState)
			{
				FSM.ChangeState(NewPlayerState::HarvestCarry);
			}
			else
			{
				FSM.ChangeState(NewPlayerState::Move);
			}
		}

		NextActionBool = Moving(this, TargetTile, _DeltaTime, ActionState);
	}

	if (true == NextActionBool)
	{
		NextActionBool = false;
		int NextActionState = ActionState;
		ActionState = -1;

		Direction = CalDirection(Direction, Location, TargetTile->GetLocation());

		switch (NextActionState)
		{
		case 0://정지
			FSM.ChangeState(NewPlayerState::Idle);
			break;
		case 1://건설
			break;
		case 2://바이오
			break;
		case 3://수확물 운반
			FSM.ChangeState(NewPlayerState::Idle);

			CarryToStorage(TargetTile, SpriteRSub);
			break;
		case 4://수확
			FSM.ChangeState(NewPlayerState::Harvest);

			Harvesting(TargetTile, SpriteRSub);

			TimeEventer.PushEvent(1.0f, std::bind(&AHaiku::ChangeAction, this, NewPlayerState::HarvestCarry), false, false);
			break;
		case 5://물주기
			if (0 < WaterCount)
			{
				FSM.ChangeState(NewPlayerState::Water);

				--WaterCount;
				Watering(TargetTile);

				TimeEventer.PushEvent(2.0f, std::bind(&AHaiku::ChangeAction, this, NewPlayerState::Idle), false, false);
			}
			//물 기르기
			else
			{
				ActionState = 6;
				TargetTile = FindStorage(Location, ActionState);
				Direction = CalDirection(Direction, Location, TargetTile->GetLocation());
				FSM.ChangeState(NewPlayerState::Move);
			}

			break;
		case 6://물 기르기
			FSM.ChangeState(NewPlayerState::WaterGet);
			TimeEventer.PushEvent(0.75f, std::bind(&AHaiku::ChangeAction, this, NewPlayerState::Idle), false, false);
			break;
		default:
			break;
		}
	}

	FSM.Update(_DeltaTime);
}

void AHaiku::ChangeAction(NewPlayerState _NewPlayerState)
{
	FSM.ChangeState(_NewPlayerState);
}

void AHaiku::Idle(float _DeltaTime)
{
	if (0 >= WaterCount)
	{
		TargetTile = nullptr;
		ActionState = 6;
		return;
	}
	else if (-1 == ActionState)
	{
		TargetTile = nullptr;
	}

	ActionState = 0;
}

void AHaiku::Move(float _DeltaTime)
{
}

void AHaiku::Water(float _DeltaTime)
{
	if (5 != ActionState)
	{
		ActionState = -1;
	}
}

void AHaiku::WaterGet(float _DeltaTime)
{
	WaterCount += 12;
	ActionState = -1;
}

void AHaiku::Harvest(float _DeltaTime)
{
	ActionState = -1;
}

void AHaiku::HarvestCarry(float _DeltaTime)
{
	ActionState = 3;
}