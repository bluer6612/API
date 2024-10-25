#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/EngineAPICore.h>

APlayer::APlayer()
{
	// UEngineAPICore::GetCore()->CreateLevel("Title");
	SetActorLoaction({100, 100});
	SetActorScale({ 100, 100 });
}

APlayer::~APlayer()
{
}


void APlayer::BeginPlay()
{
	// 기본크기가 존재하지 않으므로 
	// 기본 크기 및 기본 스케일을 지정해줘야 합니다.


}

void APlayer::Tick(float _DeltaTime)
{
	// Time::DeltaTime;

	// 여러분들의 컴퓨터가 1프레임이고
	// 선생님의 컴퓨터가 2프레임이

	// 게임시작하고 얼마지났다?

	//         여러분  제컴퓨터는
	// 0.5초             0.5        =+> 0.5         // 0.0, 0.0, => 0.5, 0.0
	// 1.0초    1.0f     0.5        =+> 1.0         // 0.5, 0.0, => 1.0, 0.0
	// 1.5초             0.5        =+> 1.5 - 1.0
	// 2.0초    1.0f     0.5        =+> 1.0         // 1.0, 0.0, => 2.0, 0.0

	// 델타임


	// 엔진에서 
	// 0.0, 0.0, => 1.0, 0.0

	AddActorLoaction(FVector2D::RIGHT * _DeltaTime * 100);
}