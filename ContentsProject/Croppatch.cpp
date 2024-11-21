#include "PreCompile.h"
#include "Croppatch.h"

ACroppatch::ACroppatch()
{
	Location.X = ScreenHX - 180;
	Location.Y = ScreenHY + 159;

	{
		SpriteR = CreateDefaultSubObject<USpriteRenderer>();
		SpriteR->SetComponentCrate(SpriteR, "croppatch0.png", {}, { Location.X, Location.Y }, ERenderOrder::BUILDING);
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