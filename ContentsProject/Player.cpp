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

void APlayer::Tick()
{
	AddActorLoaction(FVector2D::RIGHT * 0.0001f);
}