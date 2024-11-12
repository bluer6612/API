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


		// 데미지 판정을 이걸로 하는게 좋겠죠.
		// 이걸 호출해야 이벤트가 시작됩니다.
		// 어디서 호출하건 문제가 없고
		// 한번만 호출하면 된다.
		GetWorld()->CollisionGroupLink(ECollisionGroup::PlayerBody, ECollisionGroup::MonsterBody);

		// 절대 호출안됩니다.
		// 어떤 그룹과 어떤 그룹이 충돌해라. 함수를 줄거고 그걸 호출하지 않으면 절대 
		// 왜 그 함수를 호출하면 어떤게 될는 이유는 관심이 없다.
		
		CollisionComponent->SetCollisionEnter(std::bind(&ANewPlayer::CollisionEnter, this, std::placeholders::_1));
		CollisionComponent->SetCollisionStay(std::bind(&ANewPlayer::CollisionStay, this, std::placeholders::_1));
		CollisionComponent->SetCollisionEnd(std::bind(&ANewPlayer::CollisionEnd, this, std::placeholders::_1));

		// 처음 닿았을때 딱 1번만 호출된다.
		// 계속 충돌체크를 할겁니다.
		// 포탈 => 이런 것들을 좀 생각해보셔야 합니다.
		// CollisionComponent->SetCollisionEnter(펑셔널);

		// 계속 닿고 있을때 호출되는 함수
		// CollisionComponent->SetCollisionStay(펑셔널);

		// 계속 닿고 있을때 호출되는 함수
		// CollisionComponent->SetCollisionEnd(펑셔널);
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
	// 직접 카메라 피봇을 설정해줘야 한다.
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

	FSM.CreateState(NewPlayerState::Attack, std::bind(&ANewPlayer::Attack, this, std::placeholders::_1),
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
		// 픽셀충돌에서 제일 중요한건 애초에 박히지 않는것이다.
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
			// 땅에 박히지 않을때까지 올려주는 기능도 함께 만들거나 해야한다.
		}
	}
}

void ANewPlayer::Gravity(float _DeltaTime)
{
	if (false == IsGround)
	{
		// 증가시키고 
		// 여기서 계산
		AddActorLocation(GravityForce * _DeltaTime);
		GravityForce += FVector2D::DOWN * _DeltaTime * 500.0f;
	}
	else {
		GravityForce = FVector2D::ZERO;
	}

	// 상시 
}

void ANewPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (0.0f != DashTime)
	{
		DashTime += _DeltaTime;
	}


	// 세계에는 항상 0, 0이 존재한다.

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
	// 게임적 허용
	PlayerCameraCheck();
	PlayerGroundCheck(GravityForce * _DeltaTime);
	Gravity(_DeltaTime);

	if (true == UEngineInput::GetInst().IsPress('F'))
	{
		FSM.ChangeState(NewPlayerState::Attack);
		return;
	}

	if (true == UEngineInput::GetInst().IsPress('A') ||
		true == UEngineInput::GetInst().IsPress('D') ||
		true == UEngineInput::GetInst().IsPress('W') ||
		true == UEngineInput::GetInst().IsPress('S'))
	{
		// 상태를 바꾸는 순간은 그 바로 종료하는게 좋다.
		// 최종적으로 상태를 바꿨다면 종료해라.
		FSM.ChangeState(NewPlayerState::Move);
		return;
	}
}

void ANewPlayer::Attack(float _DeltaTime)
{
	// AMonster* Monster;

	//FTransform MonsterTransform;// = Monster->GetRender()->GetActorTransfrom();
	//FTransform PlayerTransform; //= SpriteRenderer->GetActorTransform();

	//if (FTransform::RectToRect(MonsterTransform, PlayerTransform))
	//{
	//}

	AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::MonsterBody);
	if (nullptr != Result)
	{
		Result->Destroy();
	}
}


void ANewPlayer::Move(float _DeltaTime)
{
	// 일반적인 이동을 하는 이유 땅에 내가 닿아있기 때문에
	PlayerCameraCheck();
	PlayerGroundCheck(GravityForce * _DeltaTime);
	Gravity(_DeltaTime);

	FVector2D Vector = FVector2D::ZERO;

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		Vector += FVector2D::RIGHT;
	}

	
	// DashTime += _DeltaTime;

	if (true == UEngineInput::GetInst().IsUp('A'))
	{
		// 이전까지 체크를 안하고 있었다.
		if (false == DashCheck)
		{
			DashCheck = true;
			DashTime = _DeltaTime;
		}
		else if (true == DashCheck && 0.2f >= DashTime)
		{
			// 대쉬 체크 안하겠다.
			DashTime = 0.0f;
			FSM.ChangeState(NewPlayerState::Dash);
			// statechange
			return;
		}

	}

	if (true == UEngineInput::GetInst().IsPress('A'))
	{


		Vector += FVector2D::LEFT;
		// A키를 눌렀다.
	}


	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		Vector += FVector2D::DOWN;
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		Vector += FVector2D::UP;
		// AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	}

	if (true == UEngineInput::GetInst().IsPress('F'))
	{
		FSM.ChangeState(NewPlayerState::Attack);
		return;
	}

	Vector.Normalize();

	// 땅 체크하는 함수.
	// PlayerGroundCheck(Vector * _DeltaTime * Speed);

	// 나는 이미 이동을 했다.
	AddActorLocation(Vector * _DeltaTime * Speed);


	// 내가 딛고 있는 땅이 언덕인지를 어떻게 알거냐????
	// 1. 색깔을 통한 구분. 언덕은 빨간색으로 칠한다.
	// 2. 


	while (true)
	{
		UColor Color = ColImage->GetColor(GetActorLocation(), UColor::WHITE);
		if (Color == UColor::BLACK)
		{
			// 나가 땅위로 올라갈때까지 while 계속 올려준다.
			AddActorLocation(FVector2D::UP);
		}
		else {
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