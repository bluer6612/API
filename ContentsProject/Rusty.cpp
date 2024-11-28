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

		SpriteR->SetOrder(ERenderOrder::PLAYER);
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

	FSM.ChangeState(NewPlayerState::Idle);
}

void ARusty::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FVector2D Location = GetActorLocation();
	std::string BeforeDirection = Direction;

	switch (ActionState)
	{
	case 0:
		TargetTile = FindTile(Location);

		if (TargetTile == nullptr)
		{
			if (4 == NextAction)
			{
				NextAction = -1;
				TimeEventer.PushEvent(2.0f, std::bind(&ARusty::ChangeAction, this, NewPlayerState::Idle), false, false);
			}
			else
			{
			}
			break;
		}
		else
		{
			Direction = CalDirection(Direction, Location, TargetTile->GetLocation());
			TargetTile->SpriteRenderer->SetSprite("gridsmall2.png");
		}

		if (0 == NextAction && 0 < WaterCount)
		{
			NextAction = 4;
			FSM.ChangeState(NewPlayerState::Move);
		}

		if (4 == NextAction)
		{
			if (CalDirection(Direction, Location, TargetTile->GetLocation()) != BeforeDirection)
			{
				FSM.ChangeState(NewPlayerState::Move);
			}
			Direction = CalDirection(Direction, Location, TargetTile->GetLocation());
			NextActionBool = Moving(this, TargetTile, _DeltaTime);
		}

		if (true == NextActionBool)
		{
			NextActionBool = false;

			switch (NextAction)
			{
			case 0://정지
				FSM.ChangeState(NewPlayerState::Idle);
				break;
			case 1://건설
				break;
			case 2://바이오
				break;
			case 3://수확
				break;
			case 4://물주기
				if (0 < WaterCount)
				{
					Direction = CalDirection(Direction, Location, TargetTile->GetLocation());
					FSM.ChangeState(NewPlayerState::Water);
					Watering(TargetTile);
					--WaterCount;
				}

				break;
			default:
				break;
			}
		}

		break;
	}
	FSM.Update(_DeltaTime);
}

void ARusty::ChangeAction(NewPlayerState _NewPlayerState)
{
	FSM.ChangeState(_NewPlayerState);
}

void ARusty::Idle(float _DeltaTime)
{
	NextAction = 0;
}

void ARusty::Move(float _DeltaTime)
{
}

void ARusty::Water(float _DeltaTime)
{
	NextActionBool = true;
}