#include "PreCompile.h"
#include "UIManager.h"
#include <EngineCore/SpriteRenderer.h>
#include "MenuPanelUI.h"
#include <EngineCore/2DCollision.h>

#include <EngineCore/EngineAPICore.h>

AUIManager::AUIManager()
{

	{
		SpriteRFarmInfo = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRFarmInfo->SetComponentCrate(SpriteRFarmInfo, "Info", 0, { 1 , 1 }, { static_cast<float>(ScreenX - 256 + 22) - 341, (ScreenHY + 93 - 2) }, ERenderOrder::UIUP);
		SpriteRFarmInfo->SetActive(false);
	}

	GetWorld()->CollisionGroupLink(UICollisionGroup::UI, UICollisionGroup::Cursor);

	CursorCollision = CreateDefaultSubObject<U2DCollision>();
	CursorCollision->SetComponentScale({ 10, 10 });
	CursorCollision->SetCollisionGroup(UICollisionGroup::Cursor);
	CursorCollision->SetCollisionType(ECollisionType::Rect);
	CursorCollision->DebugOn();

	// CursorCollision->SetCollisionEnter(std::bind(&AUIManager::PanelButtonTileEnter, this, std::placeholders::_1));
	// CursorCollision->SetCollisionEnd(std::bind(&AUIManager::PanelButtonTileEnd, this, std::placeholders::_1));

	

	FVector2D Location = { static_cast<float>(ScreenX) - 256 + 22 - 153 - 51 , ScreenHY + 93 - 120 - 22 };

	FVector2D StartPos = Location;

	Test.resize(MenuCountY);

	for (int y = 0; y < MenuCountY; y++)
	{
		Test[y].resize(CropsCount / 4);

		for (int x = 0; x < CropsCount / 4; x++)
		{
			U2DCollision* Collision = CreateDefaultSubObject<U2DCollision>();
			Collision->SetComponentLocation(StartPos);
			Collision->SetComponentScale({ 102, 44 });
			Collision->SetCollisionGroup(UICollisionGroup::UI);
			Collision->SetCollisionType(ECollisionType::Rect);

			Collision->SetCollisionEnter(std::bind(&AUIManager::PanelButtonTileEnter, this, std::placeholders::_1, FIntPoint(x, y)));
			Collision->SetCollisionEnd(std::bind(&AUIManager::PanelButtonTileEnd, this, std::placeholders::_1, FIntPoint(x, y)));

			Collision->DebugOn();

			StartPos.X += 120;
		}

		StartPos.X = Location.X;
		StartPos.Y += 50;
	}

	// Test[0][0] = "밀";
	// Test[0][1] = "사과";

	//PanelButtonTile = GetWorld()->SpawnActor<ATileMap>();
	//PanelButtonTile->SetActorLocation({ Location.X, Location.Y });
	//PanelButtonTile->Create("000_MenuPanel.png", { 4, CropsCount / 4 }, { 102, 44 });

	//int i = 0;
	//int PlusX = 0;
	//int PlusY = 0;
	//for (int x = 0; x < CropsCount / 4; x++)
	//{
	//	for (int y = 0; y < 4; y++)
	//	{
	//		if (i == 3)
	//		{
	//			//--PlusX;
	//			//PlusY += 46;
	//		}

	//		PanelButtonTile->SetTileSpriteIndex({ y, x }, { 0, 0 }, { 102, 44 }, { 2, 2 }, { 104 * PlusX, PlusY }, 0, i);

	//		if (0 > PlusX)
	//		{
	//			++PlusX;
	//		}

	//		if (i == 3)
	//		{
	//			//PlusY -= 46;
	//		}

	//		++i;
	//	}
	//}

}

void AUIManager::PanelButtonTileEnter(AActor* _Actor, FIntPoint _Index)
{
	SpriteRFarmInfo->SetActive(true);

	if (Test[_Index.Y][_Index.X] == "밀")
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