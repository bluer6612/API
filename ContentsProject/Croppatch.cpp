#include "PreCompile.h"
#include "Croppatch.h"

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

		//Collision->SetCollisionEnter(std::bind(&AUIManager::PanelButtonTileEnter, this, std::placeholders::_1, FTransform(FVector2D(Index, 0), FVector2D(StartPos))));
		//Collision->SetCollisionStay(std::bind(&AUIManager::PanelButtonTileStay, this, std::placeholders::_1, FTransform(FVector2D(Index, 0), FVector2D(StartPos))));
		//Collision->SetCollisionEnd(std::bind(&AUIManager::PanelButtonTileEnd, this, std::placeholders::_1, FTransform(FVector2D(Index, 0), FVector2D(StartPos))));
	}
}

ACroppatch::~ACroppatch()
{
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