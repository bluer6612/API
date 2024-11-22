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

	Location.X = Location.X - 48;
	Location.Y = Location.Y - 44;
	
	{
		FVector2D StartPos = Location;

		int Index = 0;

		for (int y = 4; y > 0; --y)
		{
			for (int x = 4; x > 0; --x)
			{
				U2DCollision* Collision = CreateDefaultSubObject<U2DCollision>();
				Collision->SetCollisionGroup(UICollisionGroup::Croppatch);
				Collision->SetCollisionType(ECollisionType::Rect);
				Collision->SetComponentLocation(StartPos);
				Collision->SetComponentScale({ 32, 32 });

				Collision->SetCollisionStay(std::bind(&ACroppatch::ClickEnter, this, std::placeholders::_1, FTransform(FVector2D(Index, 0), FVector2D(StartPos))));

				CroppatchTile[Index] = CreateDefaultSubObject<USpriteRenderer>();
				CroppatchTile[Index]->SetComponentCrate(CroppatchTile[Index], "gridsmall.png", { 36, 36 }, { StartPos }, ERenderOrder::BUILDINGUP);
				CroppatchTile[Index]->SetAlphafloat(0.75f);
				//CroppatchTile[Index]->SetActive(false);

				StartPos.X += 32;

				++Index;
			}

			StartPos.X = Location.X;
			StartPos.Y += 32;
		}
	}
}

ACroppatch::~ACroppatch()
{
}

void ACroppatch::ClickEnter(AActor* _Actor, FTransform _Index)
{
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		int a = 0;
		++_Index.Scale.X;
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