#include "PreCompile.h"
#include "Rusty.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include "ContentsEnum.h"

ARusty::ARusty()
{
	SetActorLocation({ 100, 100 });

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("RustyGold");
		SpriteRenderer->SetSpriteScale(2.0f);
		SpriteRenderer->CreateAnimation("Idle_Right", "RustyGold", 48, 49, 0.5f);
		SpriteRenderer->CreateAnimation("Run_Right", "RustyGold", 2, 5, 0.2f);
	}

	//DebugOn();
}

ARusty::~ARusty()
{
}

void ARusty::BeginPlay()
{
	Super::BeginPlay();
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);

	GetWorld()->SetCameraToMainPawn(false);


	FSM.CreateState(NewPlayerState::Idle, std::bind(&ARusty::Idle, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Idle_Right");
		}
	);

	FSM.CreateState(NewPlayerState::Move, std::bind(&ARusty::Move, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Run_Right");
		}
	);

	FSM.ChangeState(NewPlayerState::Idle);

}


void ARusty::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineDebug::SwitchIsDebug();
	}

	FSM.Update(_DeltaTime);
}

void ARusty::Idle(float _DeltaTime)
{
	if (true == UEngineInput::GetInst().IsPress('A') ||
		true == UEngineInput::GetInst().IsPress('D') ||
		true == UEngineInput::GetInst().IsPress('W') ||
		true == UEngineInput::GetInst().IsPress('S'))
	{
		FSM.ChangeState(NewPlayerState::Move);
		return;
	}
}

void ARusty::Move(float _DeltaTime)
{
	FVector2D Vector = FVector2D::ZERO;

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		Vector += FVector2D::RIGHT;
	}
	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		Vector += FVector2D::LEFT;
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		Vector += FVector2D::DOWN;
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		Vector += FVector2D::UP;
	}

	Vector.Normalize();

	if (true == IsMove)
	{
		AddActorLocation(Vector * _DeltaTime * Speed);
	}

	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{
		FSM.ChangeState(NewPlayerState::Idle);
		return;
	}
}

void ARusty::SetColImage(std::string_view _ColImageName)
{
	ColImage = UImageManager::GetInst().FindImage(_ColImageName);
}

void ARusty::LevelChangeStart()
{
	int a = 0;
}