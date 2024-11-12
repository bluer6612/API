#include "PreCompile.h"
#include "NewPlayer.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/2DCollision.h>
#include "ContentsEnum.h"

ANewPlayer::ANewPlayer()
{
	SetActorLocation({ 100, 100 });

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Player_Right.png");
		SpriteRenderer->SetComponentScale({ 300, 300 });
		SpriteRenderer->CreateAnimation("Run_Right", "Player_Right.png", 2, 4, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Right", "Player_Right.png", 0, 0, 0.1f);
	}

	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentLocation({ 200, 0 });
		CollisionComponent->SetComponentScale({ 50, 50 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::PlayerBody);
		CollisionComponent->SetCollisionType(ECollisionType::CirCle);

		GetWorld()->CollisionGroupLink(ECollisionGroup::PlayerBody, ECollisionGroup::MonsterBody);

		CollisionComponent->SetCollisionEnter(std::bind(&ANewPlayer::CollisionEnter, this, std::placeholders::_1));
		CollisionComponent->SetCollisionStay(std::bind(&ANewPlayer::CollisionStay, this, std::placeholders::_1));
		CollisionComponent->SetCollisionEnd(std::bind(&ANewPlayer::CollisionEnd, this, std::placeholders::_1));
	}

	DebugOn();
}

void ANewPlayer::CollisionEnter(AActor* _ColActor)
{
	int a = 0;
}

void ANewPlayer::CollisionStay(AActor* _ColActor)
{
	int a = 0;
}

void ANewPlayer::CollisionEnd(AActor* _ColActor)
{
	int  a = 0;
}

ANewPlayer::~ANewPlayer()
{
}

void ANewPlayer::BeginPlay()
{
	Super::BeginPlay();
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);

	GetWorld()->SetCameraToMainPawn(false);

	FSM.CreateState(NewPlayerState::Idle, std::bind(&ANewPlayer::Idle, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Idle_Right");
		}
	);

	FSM.CreateState(NewPlayerState::Move, std::bind(&ANewPlayer::Move, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Run_Right");
		}
	);

	FSM.ChangeState(NewPlayerState::Idle);

}

void ANewPlayer::PlayerCameraCheck()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPos(GetActorLocation() - WindowSize.Half());

	DebugOn();
}

void ANewPlayer::PlayerGroundCheck(FVector2D _MovePos)
{
	IsGround = false;

	if (nullptr != ColImage)
	{
		FVector2D NextPos = GetActorLocation() + _MovePos;

		NextPos.X = floorf(NextPos.X);
		NextPos.Y = floorf(NextPos.Y);

		UColor Color = ColImage->GetColor(NextPos, UColor::WHITE);
		if (Color == UColor::WHITE)
		{
			IsGround = false;
		}
		else if (Color == UColor::BLACK)
		{
			IsGround = true;
		}
	}
}

void ANewPlayer::Gravity(float _DeltaTime)
{
	if (false == IsGround)
	{
		AddActorLocation(GravityForce * _DeltaTime);
		GravityForce += FVector2D::DOWN * _DeltaTime * 500.0f;
	}
	else
	{
		GravityForce = FVector2D::ZERO;
	}

}

void ANewPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (0.0f != DashTime)
	{
		DashTime += _DeltaTime;
	}

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

	FTransform PlayerTransform = GetTransform();
	PlayerTransform.Location += FVector2D(20, 0) - GetWorld()->GetCameraPos();
	PlayerTransform.Scale = { 6,6 };
	UEngineDebug::CoreDebugRender(PlayerTransform, UEngineDebug::EDebugPosType::Circle);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineDebug::SwitchIsDebug();
	}

	FSM.Update(_DeltaTime);
}

void ANewPlayer::Idle(float _DeltaTime)
{
	PlayerCameraCheck();

	if (true == UEngineInput::GetInst().IsPress('A') ||
		true == UEngineInput::GetInst().IsPress('D') ||
		true == UEngineInput::GetInst().IsPress('W') ||
		true == UEngineInput::GetInst().IsPress('S'))
	{
		FSM.ChangeState(NewPlayerState::Move);
		return;
	}
}

void ANewPlayer::Move(float _DeltaTime)
{
	PlayerCameraCheck();

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

	AddActorLocation(Vector * _DeltaTime * Speed);

	while (true)
	{
		UColor Color = ColImage->GetColor(GetActorLocation(), UColor::WHITE);
		
		if (Color == UColor::BLACK)
		{
			AddActorLocation(FVector2D::UP);
		}
		else
		{
			break;
		}
	}

	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{
		FSM.ChangeState(NewPlayerState::Idle);
		return;
	}
	UEngineDebug::CoreOutPutString("IsGround : " + std::to_string(IsGround));
}

void ANewPlayer::SetColImage(std::string_view _ColImageName)
{
	ColImage = UImageManager::GetInst().FindImage(_ColImageName);
}

void ANewPlayer::LevelChangeStart()
{
	int a = 0;
}