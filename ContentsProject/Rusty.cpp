#include "PreCompile.h"
#include "Fade.h"
#include "Rusty.h"

#include "CharacterManager.h"

#include "ContentsEnum.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

ARusty::ARusty()
{
	SetActorLocation({ static_cast<float>(ScreenX * 0.5 - 85), static_cast<float>((ScreenY - 243) + 76) });

	{
		SpriteR = CreateDefaultSubObject<USpriteRenderer>();
		SpriteR->SetSprite("RustyGold");
		SpriteR->SetOrder(ERenderOrder::PLAYER);

		SpriteR->CreateAnimation("Idle_Bot", "RustyGold", 48, 49, 0.6f);
		SpriteR->CreateAnimation("Idle_Top", "RustyGold", 50, 51, 0.6f);
		SpriteR->CreateAnimation("Idle_Right", "RustyGold", 52, 53, 0.6f);
		SpriteR->CreateAnimation("Idle_Left", "RustyGold", 54, 55, 0.6f);
		SpriteR->CreateAnimation("Run_Bot", "RustyGold", 0, 5, 0.2f);
		SpriteR->CreateAnimation("Run_Top", "RustyGold", 6, 11, 0.2f);
		SpriteR->CreateAnimation("Run_Right", "RustyGold", 12, 17, 0.2f);
		SpriteR->CreateAnimation("Run_Left", "RustyGold", 18, 23, 0.2f);
		SpriteR->CreateAnimation("Water_Bot", "RustyGold", 24, 27, 0.5f);
		SpriteR->CreateAnimation("Water_Top", "RustyGold", 28, 31, 0.5f);
		SpriteR->CreateAnimation("Water_Right", "RustyGold", 32, 35, 0.5f);
		SpriteR->CreateAnimation("Water_Left", "RustyGold", 36, 39, 0.5f);
		SpriteR->CreateAnimation("Harvest_Bot", "RustyGold", 65, 70, 0.2f);
		SpriteR->CreateAnimation("Harvest_Top", "RustyGold", 71, 76, 0.2f);
		SpriteR->CreateAnimation("Harvest_Right", "RustyGold", 77, 82, 0.2f);
		SpriteR->CreateAnimation("Harvest_Left", "RustyGold", 83, 88, 0.2f);


		SpriteRSub = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRSub->SetSprite("EmptyTile.png");
		SpriteRSub->SetComponentScale({32, 64});
		SpriteRSub->SetOrder(ERenderOrder::BUILDINGUP);
		SpriteRSub->SetPivotValue({0.5f, 1.25f});
		SpriteRSub->SetActive(false);
	}
}

ARusty::~ARusty()
{
}

void ARusty::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);

	FSM.CreateState(NewPlayerState::Idle, std::bind(&ARusty::Idle, this, std::placeholders::_1),
		[this]()
		{
			SpriteR->ChangeAnimation("Idle_" + Direction);
		}
	);

	FSM.CreateState(NewPlayerState::Move, std::bind(&ARusty::Move, this, std::placeholders::_1),
		[this]()
		{
			SpriteR->ChangeAnimation("Run_" + Direction);
		}
	);

	FSM.CreateState(NewPlayerState::Water, std::bind(&ARusty::Water, this, std::placeholders::_1),
		[this]()
		{
			SpriteR->ChangeAnimation("Water_" + Direction);
		}
	);

	FSM.CreateState(NewPlayerState::Harvest, std::bind(&ARusty::Harvest, this, std::placeholders::_1),
		[this]()
		{
			SpriteR->ChangeAnimation("Harvest_" + Direction);
		}
	);

	FSM.ChangeState(NewPlayerState::Idle);
}

void ARusty::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FVector2D Location = GetActorLocation();
	std::string BeforeDirection = Direction;

	if (TargetTile == nullptr)
	{
		TargetTile = FindTile(Location, ActionState);
		return;
	}
	else if (0 == ActionState)
	{
		Direction = CalDirection(Direction, Location, TargetTile->GetLocation());
		FSM.ChangeState(NewPlayerState::Move);
	}

	if (0 == ActionState && 5 <= TargetTile->GetProgress()) //수확
	{
		ActionState = 3;
	}
	else if (0 == ActionState && 0 < WaterCount) //물 주기
	{
		ActionState = 4;
	}

	if (0 < ActionState)
	{
		Direction = CalDirection(Direction, Location, TargetTile->GetLocation());
		if (Direction != BeforeDirection)
		{
			FSM.ChangeState(NewPlayerState::Move);
		}
		NextActionBool = Moving(this, TargetTile, _DeltaTime);
	}

	if (true == NextActionBool)
	{
		NextActionBool = false;
		Direction = CalDirection(Direction, Location, TargetTile->GetLocation());

		switch (ActionState)
		{
		case 0://정지
			FSM.ChangeState(NewPlayerState::Idle);
			break;
		case 1://건설
			break;
		case 2://바이오
			break;
		case 3://수확
			FSM.ChangeState(NewPlayerState::Harvest);

			Havesting(TargetTile, SpriteRSub);
			break;
		case 4://물주기
			if (0 < WaterCount)
			{
				FSM.ChangeState(NewPlayerState::Water);

				--WaterCount;
				Watering(TargetTile);

				TimeEventer.PushEvent(2.0f, std::bind(&ARusty::ChangeAction, this, NewPlayerState::Idle), false, false);
			}
			//물 기르기
			else
			{

			}

			break;
		default:
			break;
		}

		ActionState = -1;
	}

	FSM.Update(_DeltaTime);
}

void ARusty::ChangeAction(NewPlayerState _NewPlayerState)
{
	FSM.ChangeState(_NewPlayerState);
}

void ARusty::Idle(float _DeltaTime)
{
	if (-1 == ActionState)
	{
		TargetTile = nullptr;
	}

	ActionState = 0;
}

void ARusty::Move(float _DeltaTime)
{
}

void ARusty::Water(float _DeltaTime)
{
	ActionState = -1;
	NextActionBool = true;
}

void ARusty::Harvest(float _DeltaTime)
{
	ActionState = -1;
}
