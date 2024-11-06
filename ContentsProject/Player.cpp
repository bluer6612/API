#include "PreCompile.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>


#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"

void APlayer::RunSoundPlay()
{
	// UEngineDebug::OutPutString("SoundPlay");
}

APlayer::APlayer()
{
	// UEngineAPICore::GetCore()->CreateLevel("Title");
	SetActorLocation({100, 100});

	// 랜더러를 하나 만든다.
	// 언리얼에서는 생서에서 CreateDefaultSubObject <= 생성자에서밖에 못합니다.
	// 무조건 만들어야 한다.
	// 다른데서하면 무조건 터져요.
	// 한번 생성자에서 만든 지울수도 없어.

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Player_Right.png");
		SpriteRenderer->SetComponentScale({ 300, 300 });

		// SpriteRenderer->CreateAnimation("bomb", 0, 2, 0.1f);

		SpriteRenderer->CreateAnimation("Run_Right", "Player_Right.png", 2, 4, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Right", "Player_Right.png", 0, 0, 0.1f);

		SpriteRenderer->ChangeAnimation("Idle_Right");


		// SpriteRenderer->CreateAnimation("Test", "Player_Right.png", { 5,  4,  3}, 0.1f);
		SpriteRenderer->SetAnimationEvent("Run_Right", 2, std::bind(&APlayer::RunSoundPlay, this));

		std::string Name = SpriteRenderer->GetCurSpriteName();

		int a = 0;

	}



	//{
	//	USpriteRenderer* Renderer = CreateDefaultSubObject<USpriteRenderer>();
	//	Renderer->SetSprite("Player_Right.png");
	//	Renderer->SetComponentLocation({ -100, 0 });
	//	Renderer->SetComponentScale({ 50, 50 });
	//}

	//{
	//	USpriteRenderer* Renderer = CreateDefaultSubObject<USpriteRenderer>();
	//	Renderer->SetSprite("Player_Right.png");
	//	Renderer->SetComponentLocation({ 100, 0 });
	//	Renderer->SetComponentScale({ 50, 50 });
	//}

	//{
	//	USpriteRenderer* Renderer = CreateDefaultSubObject<USpriteRenderer>();
	//	Renderer->SetSprite("Player_Right.png");
	//	Renderer->SetComponentLocation({ 0, -100 });
	//	Renderer->SetComponentScale({ 50, 50 });
	//}

	//{
	//	USpriteRenderer* Renderer = CreateDefaultSubObject<USpriteRenderer>();
	//	Renderer->SetSprite("Player_Right.png");
	//	Renderer->SetComponentLocation({ 0, 100 });
	//	Renderer->SetComponentScale({ 50, 50 });
	//}

	// 부모의 크기에 영향 안받게 만들것이다.

	// CreateDefaultSubObject<U2DCollision>();
}

APlayer::~APlayer()
{
}

void APlayer::SetColImage(std::string_view _ColImageName)
{
	ColImage = UImageManager::GetInst().FindImage(_ColImageName);
}


void APlayer::BeginPlay()
{
	Super::BeginPlay();

	// 직접 카메라 피봇을 설정해줘야 한다.
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);

	ChangeState(PlayerState::Idle);
}

void APlayer::IdleStart()
{
	SpriteRenderer->ChangeAnimation("Idle_Right");
}

void APlayer::ChangeState(PlayerState _CurPlayerState)
{
	switch (_CurPlayerState)
	{
	case PlayerState::Idle:
		IdleStart();
		break;
	case PlayerState::Move:
		MoveStart();
		break;
	case PlayerState::Jump:
		break;
	default:
		break;
	}

	CurPlayerState = _CurPlayerState;

}

void APlayer::Tick(float _DeltaTime)
{
	// 이런식으로 짜게되면 아무도 못알아봅니다.
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}

	switch (CurPlayerState)
	{
	case PlayerState::Idle:
		Idle(_DeltaTime);
		break;
	case PlayerState::Move:
		Move(_DeltaTime);
		break;
	case PlayerState::Jump:
		// 하이퍼 FSM이라고 합니다
		// FSM의 변종입니다.
		break;
	default:
		break;
	}

}

void APlayer::LevelChangeStart()
{
	Super::LevelChangeStart();
}

void APlayer::LevelChangeEnd()
{
	Super::LevelChangeEnd();


}

void APlayer::Idle(float _DeltaTime)
{
	Gravity();


	SpriteRenderer->ChangeAnimation("Idle_Right");

	// 아이들이라는 상태는 가만히 있는 상태이다.

	// 전이에 대한 판단은 해야 합니다.
	// 각스테이트에서 쳐야할 코드는
	// 1. 전이조건


	if (true == UEngineInput::GetInst().IsPress('A') ||
		true == UEngineInput::GetInst().IsPress('D') ||
		true == UEngineInput::GetInst().IsPress('W') ||
		true == UEngineInput::GetInst().IsPress('S'))
	{
		// 상태를 바꾸는 순간은 그 바로 종료하는게 좋다.
		// 최종적으로 상태를 바꿨다면 종료해라.
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == UEngineInput::GetInst().IsPress(VK_SPACE))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

}

void APlayer::MoveStart()
{
	SpriteRenderer->ChangeAnimation("Run_Right");
}

void APlayer::Move(float _DeltaTime)
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

	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	if (nullptr != ColImage)
	{

		// 픽셀충돌에서 제일 중요한건 애초에 박히지 않는것이다.
		FVector2D NextPos = GetActorLocation() + Vector * _DeltaTime * Speed;

		UColor Color = ColImage->GetColor(NextPos, UColor::BLACK);
		if (Color == UColor::WHITE)
		{
			AddActorLocation(Vector * _DeltaTime * Speed);
		}
	}
}