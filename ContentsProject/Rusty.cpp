#include "PreCompile.h"
#include "Rusty.h"
#include "Fade.h"

#include "CharacterManager.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"

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
			SpriteR->ChangeAnimation("Run_Right");
		}
	);

	FSM.ChangeState(NewPlayerState::Idle);
}

void ARusty::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FVector2D Location = GetActorLocation();
	bool NextActionBool = false;

	switch (ActionState)
	{
	case 0:
		TargetTile = FindTile(Location);

		if (TargetTile == nullptr)
		{
			break;
		}

		if (0 < Water)
		{
			NextAction = 4;
			FSM.ChangeState(NewPlayerState::Move);
			NextActionBool = Moving(this, TargetTile, _DeltaTime);
		}

		if (true == NextActionBool)
		{
			switch (NextAction)
			{
			case 0://정지
				break;
			case 1://건설
				break;
			case 2://바이오
				break;
			case 3://수확
				break;
			case 4://물주기
				if (0 < Water)
				{
					FSM.ChangeState(NewPlayerState::Idle);
					NextAction = Watering(TargetTile);
					--Water;
				}

				break;
			}
		}

		break;
	}

	FSM.Update(_DeltaTime);
}

void ARusty::Idle(float _DeltaTime)
{
	//if (true == UEngineInput::GetInst().IsPress('A') ||
	//	true == UEngineInput::GetInst().IsPress('D') ||
	//	true == UEngineInput::GetInst().IsPress('W') ||
	//	true == UEngineInput::GetInst().IsPress('S'))
	//{
	//	FSM.ChangeState(NewPlayerState::Move);
	//	return;
	//}
}

void ARusty::Move(float _DeltaTime)
{
	//FVector2D Vector = FVector2D::LEFT;

	//if (true == UEngineInput::GetInst().IsPress('D'))
	//{
	//	Vector += FVector2D::RIGHT;
	//}
	//if (true == UEngineInput::GetInst().IsPress('A'))
	//{
	//	Vector += FVector2D::LEFT;
	//}
	//if (true == UEngineInput::GetInst().IsPress('S'))
	//{
	//	Vector += FVector2D::DOWN;
	//}
	//if (true == UEngineInput::GetInst().IsPress('W'))
	//{
	//	Vector += FVector2D::UP;
	////}

	//Vector.Normalize();

	//if (true == IsMove)
	//{
	//	AddActorLocation(Vector * _DeltaTime * Speed);
	//}

	//if (false == UEngineInput::GetInst().IsPress('A') &&
	//	false == UEngineInput::GetInst().IsPress('D') &&
	//	false == UEngineInput::GetInst().IsPress('W') &&
	//	false == UEngineInput::GetInst().IsPress('S'))
	//{
	//	FSM.ChangeState(NewPlayerState::Idle);
	//	return;
	//}
}