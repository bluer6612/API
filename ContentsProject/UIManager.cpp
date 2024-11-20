#include "PreCompile.h"
#include "UIManager.h"
#include <EngineCore/SpriteRenderer.h>
#include "MenuPanelUI.h"
#include <EngineCore/2DCollision.h>

#include <EngineCore/EngineAPICore.h>

AUIManager::AUIManager()
{
	{
		GetWorld()->CollisionGroupLink(UICollisionGroup::UI, UICollisionGroup::Cursor);

		CursorCollision = CreateDefaultSubObject<U2DCollision>();
		CursorCollision->SetCollisionGroup(UICollisionGroup::Cursor);
		CursorCollision->SetCollisionType(ECollisionType::Rect);
		CursorCollision->SetComponentScale({ 5, 5 });
		//CursorCollision->DebugOn();
	}

	{
		SpriteRFarmInfo = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRFarmInfo->SetComponentCrate(SpriteRFarmInfo, "Info", 0, { 1 , 1 }, { static_cast<float>(ScreenX - 256 + 22) - 341, (ScreenHY + 93 - 2) }, ERenderOrder::UIUP);
		SpriteRFarmInfo->SetActive(false);
	}

	FVector2D Location = { static_cast<float>(ScreenX) - 256 - 130 , ScreenHY + 93 - 120 - 22 };

	FVector2D StartPos = Location;

	Test.resize(CropsCount / 4);

	for (int y = 0; y < CropsCount / 4; y++)
	{
		Test[y].resize(MenuCountY);

		for (int x = 0; x < MenuCountY; x++)
		{
			U2DCollision* Collision = CreateDefaultSubObject<U2DCollision>();
			Collision->SetCollisionGroup(UICollisionGroup::UI);
			Collision->SetCollisionType(ECollisionType::Rect);
			Collision->SetComponentLocation(StartPos);
			Collision->SetComponentScale({ 102, 44 });
			Collision->SetAlphafloat(0.5f);

			Collision->SetCollisionEnter(std::bind(&AUIManager::PanelButtonTileEnter, this, std::placeholders::_1, FIntPoint(x, y)));
			Collision->SetCollisionEnd(std::bind(&AUIManager::PanelButtonTileEnd, this, std::placeholders::_1, FIntPoint(x, y)));

			Collision->DebugOn();

			StartPos.X += 104;
		}

		StartPos.X = Location.X;
		StartPos.Y += 46;
	}

	// Test[0][0] = "밀";
	// Test[0][1] = "사과";
}

void AUIManager::PanelButtonTileEnter(AActor* _Actor, FIntPoint _Index)
{
	SpriteRFarmInfo->SetActive(true);

	//if (Test[_Index.Y][_Index.X] == "밀")
	{
		int a = 0;
	}
}

void AUIManager::PanelButtonTileEnd(AActor* _Actor, FIntPoint _Index)
{
	SpriteRFarmInfo->SetActive(false);
}

AUIManager::~AUIManager()
{
}

void AUIManager::BeginPlay()
{
	Super::BeginPlay();

	AMenuPanelUI* NewActor = AActor::GetWorld()->SpawnActor<AMenuPanelUI>();
}

void AUIManager::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	CursorCollision->SetComponentLocation(MousePos);
}