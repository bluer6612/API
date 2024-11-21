#include "PreCompile.h"
#include "UIManager.h"

#include "MenuPanelUI.h"
#include "TitleLogo.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>
#include <EngineCore/EngineAPICore.h>

AUIManager::AUIManager()
{
	{
		GetWorld()->CollisionGroupLink(UICollisionGroup::UI, UICollisionGroup::Cursor);

		CursorCollision = CreateDefaultSubObject<U2DCollision>();
		CursorCollision->SetCollisionGroup(UICollisionGroup::Cursor);
		CursorCollision->SetCollisionType(ECollisionType::Rect);
		CursorCollision->SetComponentScale({ 1, 1 });
		//CursorCollision->DebugOn();
	}

	{
		SpriteRFarmInfo = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRFarmInfo->SetComponentCrate(SpriteRFarmInfo, "Info", 0, { 1 , 1 }, { static_cast<float>(ScreenX - 256 + 22) - 341, (ScreenHY + 93 - 2) }, ERenderOrder::UIUP);
		SpriteRFarmInfo->SetActive(false);
	}

	Test.resize(CropsCount);

	FVector2D Location = { static_cast<float>(ScreenX) - (104 * 4) + 29 , ScreenHY + 93 - 120 };
	FVector2D StartPos = Location;

	int Index = 0;
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			U2DCollision* Collision = CreateDefaultSubObject<U2DCollision>();
			Collision->SetCollisionGroup(UICollisionGroup::UI);
			Collision->SetCollisionType(ECollisionType::Rect);
			Collision->SetComponentLocation(StartPos);
			Collision->SetComponentScale({ 102, 44 });

			Collision->SetCollisionEnter(std::bind(&AUIManager::PanelButtonTileEnter, this, std::placeholders::_1, FIntPoint(Index, 0)));
			Collision->SetCollisionStay(std::bind(&AUIManager::PanelButtonTileStay, this, std::placeholders::_1, FIntPoint(Index, 0)));
			Collision->SetCollisionEnd(std::bind(&AUIManager::PanelButtonTileEnd, this, std::placeholders::_1, FIntPoint(Index, 0)));

			//Collision->DebugOn();

			++Index;
			
			if ((6 * 4) - 1 == Index)
			{
				break;
			}
			else if (3 == Index)
			{
				StartPos.X = Location.X;
				StartPos.Y += 46;
			}
			else if (0 == (Index - 3) % 4 && 4 != Index)
			{
				StartPos.X = Location.X;
				StartPos.Y += 46;
			}
			else
			{
				StartPos.X += 104;
			}
		}
	}
}

void AUIManager::PanelButtonTileEnter(AActor* _Actor, FIntPoint _Index)
{
	SpriteRFarmInfo->SetSprite("Info", _Index.X);
	SpriteRFarmInfo->SetActive(true);
}

void AUIManager::PanelButtonTileStay(AActor* _Actor, FIntPoint _Index)
{
	SpriteRFarmInfo->SetSprite("Info", _Index.X);
	SpriteRFarmInfo->SetActive(true);
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

	//Å¸ÀÌÆ²
	{
		//TitleLogo* NewActor = AActor::GetWorld()->SpawnActor<TitleLogo>();
	}
}

void AUIManager::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	CursorCollision->SetComponentLocation(MousePos);
}