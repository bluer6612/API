#include "PreCompile.h"
#include "Rusty.h"
#include "Fade.h"

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
		SpriteR->CreateAnimation("Idle_Right", "RustyGold", 48, 49, 0.5f);
		SpriteR->CreateAnimation("Run_Right", "RustyGold", 0, 5, 0.2f);
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
			SpriteR->ChangeAnimation("Idle_Right");
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

	//FVector2D Vector = FVector2D::ZERO;

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
	//}

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