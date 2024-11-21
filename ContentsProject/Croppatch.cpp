#include "PreCompile.h"
#include "Croppatch.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/2DCollision.h>
#include "UIManager.h"

ACroppatch::ACroppatch()
{
	Location.X = ScreenHX - 180;
	Location.Y = ScreenHY + 159;

	{
		SpriteR = CreateDefaultSubObject<USpriteRenderer>();
		SpriteR->SetComponentCrate(SpriteR, "croppatch0.png", {}, { Location.X, Location.Y }, ERenderOrder::BUILDING);
	}

	{
		U2DCollision* Collision = CreateDefaultSubObject<U2DCollision>();
		Collision->SetCollisionGroup(UICollisionGroup::Croppatch);
		Collision->SetCollisionType(ECollisionType::Rect);
		Collision->SetComponentLocation(Location);
		Collision->SetComponentScale({ 144, 144 });

		Collision->SetCollisionEnter(std::bind(&ACroppatch::ClickEnter, this, std::placeholders::_1, FVector2D({1, 1})));
		Collision->SetCollisionStay(std::bind(&ACroppatch::ClickStay, this, std::placeholders::_1, FVector2D({1, 1})));
		Collision->SetCollisionEnd(std::bind(&ACroppatch::ClickEnd, this, std::placeholders::_1, FVector2D({1, 1})));
	}
}

ACroppatch::~ACroppatch()
{
}

void ACroppatch::ClickEnter(AActor* _Actor, FVector2D _Index)
{
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{/*
		CursorImage->SetActive(true);
		CursorImage->SetComponentLocation({ MousePos.X - 5, MousePos.Y - 24 });*/
		++_Index.X;
	}
}

void ACroppatch::ClickStay(AActor* _Actor, FVector2D _Index)
{
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		++_Index.X;
	}
}

void ACroppatch::ClickEnd(AActor* _Actor, FVector2D _Index)
{
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		++_Index.X;
	}
}

void ACroppatch::BeginPlay()
{
	Super::BeginPlay();
}

void ACroppatch::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//FSM.Update(_DeltaTime);
}

void ACroppatch::Idle(float _DeltaTime)
{
}