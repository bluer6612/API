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
		SpriteR->SetComponentCrate(SpriteR, "croppatch0.png", {}, { Location }, ERenderOrder::BUILDING);
	}

	{
		U2DCollision* Collision = CreateDefaultSubObject<U2DCollision>();
		Collision->SetCollisionGroup(UICollisionGroup::Croppatch);
		Collision->SetCollisionType(ECollisionType::Rect);
		Collision->SetComponentLocation(Location);
		Collision->SetComponentScale({ 144, 144 });

		Collision->SetCollisionEnter(std::bind(&ACroppatch::ClickEnter, this, std::placeholders::_1, FVector2D({ Location })));
		Collision->SetCollisionStay(std::bind(&ACroppatch::ClickEnter, this, std::placeholders::_1, FVector2D({ Location })));
		Collision->SetCollisionEnd(std::bind(&ACroppatch::ClickEnter, this, std::placeholders::_1, FVector2D({ Location })));
		//Collision->SetCollisionEnter(std::bind(&AUIManager::CroppatchClickEnter, this, std::placeholders::_1, FVector2D({ Location })));
		//Collision->SetCollisionEnter(std::bind(&AUIManager::PanelButtonTileEnter, this, std::placeholders::_1, FTransform(FVector2D(1, 0), FVector2D(Location))));
	}
}

ACroppatch::~ACroppatch()
{
}

void ACroppatch::ClickEnter(AActor* _Actor, FVector2D _Index)
{
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		int a = 0;
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