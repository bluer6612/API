#include "PreCompile.h"
#include "UIManager.h"

#include "MenuPanelUI.h"
#include "TitleLogo.h"
#include "BuildingManager.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>

AUIManager::AUIManager()
{
	GetWorld()->CollisionGroupLink(UICollisionGroup::Panel, UICollisionGroup::Cursor);
	GetWorld()->CollisionGroupLink(UICollisionGroup::Building, UICollisionGroup::Cursor);
	GetWorld()->CollisionGroupLink(UICollisionGroup::Croppatch, UICollisionGroup::Cursor);
		
	CursorCollision = CreateDefaultSubObject<U2DCollision>();
	CursorCollision->SetCollisionGroup(UICollisionGroup::Cursor);
	CursorCollision->SetCollisionType(ECollisionType::Rect);
	CursorCollision->SetComponentScale({ 1, 1 });
	//CursorCollision->DebugOn();

	//농사 모드 씨앗 이미지
	CursorImage = CreateDefaultSubObject<USpriteRenderer>();
	CursorImage->SetSprite("Crops.png", 3);
	CursorImage->SetComponentScale({ 32, 64 });
	CursorImage->SetOrder(ERenderOrder::CURSOR);
	CursorImage->SetActive(false);

	//CursorImage->DebugOn();

	//농사 마우스 on 시 설명
	SRFarmInfo = CreateDefaultSubObject<USpriteRenderer>();
	SRFarmInfo->SetComponentCrate(SRFarmInfo, "FarmInfo", 0, { 1 , 1 }, { static_cast<float>(ScreenX - 256 + 22) - 341, (ScreenHY + 93 - 2) }, ERenderOrder::UIUP);
	SRFarmInfo->SetActive(false);

	//농사 마우스 on 시 음영 처리
	SRButtonBlack = CreateDefaultSubObject<USpriteRenderer>();
	SRButtonBlack->SetComponentCrate(SRButtonBlack, "003_crop-seed-button_Black.png", {}, { static_cast<float>(ScreenX) - (104 * 4) + 29 , ScreenHY + 93 - 120 }, ERenderOrder::UIUP);
	SRButtonBlack->SetAlphafloat(0.35f);
	SRButtonBlack->SetActive(false);


	//농사 패널 버튼
	{
		FarmInfoIndex.resize(CropsCount);

		FVector2D Location = { static_cast<float>(ScreenX) - (104 * 4) + 29 , ScreenHY + 93 - 120 };
		FVector2D StartPos = Location;

		int Index = 0;
		for (int y = 0; y < 6; ++y)
		{
			for (int x = 0; x < 4; ++x)
			{
				U2DCollision* Collision = CreateDefaultSubObject<U2DCollision>();
				Collision->SetCollisionGroup(UICollisionGroup::Panel);
				Collision->SetCollisionType(ECollisionType::Rect);
				Collision->SetComponentLocation(StartPos);
				Collision->SetComponentScale({ 102, 44 });

				Collision->SetCollisionEnter(std::bind(&AUIManager::PanelButtonTileEnter, this, std::placeholders::_1, FTransform(FVector2D(Index, 0), FVector2D(StartPos))));
				Collision->SetCollisionStay(std::bind(&AUIManager::PanelButtonTileStay, this, std::placeholders::_1, FTransform(FVector2D(Index, 0), FVector2D(StartPos))));
				Collision->SetCollisionEnd(std::bind(&AUIManager::PanelButtonTileEnd, this, std::placeholders::_1, FTransform(FVector2D(Index, 0), FVector2D(StartPos))));

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
}

AUIManager::~AUIManager()
{
}

void AUIManager::BeginPlay()
{
	Super::BeginPlay();

	//패널
	{
		//AMenuPanelUI* NewActor = AActor::GetWorld()->SpawnActor<AMenuPanelUI>();
	}

	//타이틀
	{
		//TitleLogo* NewActor = AActor::GetWorld()->SpawnActor<TitleLogo>();
	}

	ACroppatch* Croppatch = nullptr;
	{
		Croppatch = GetWorld()->SpawnActor<ACroppatch>();

		this->SetCroppatch(Croppatch);
	}

	//농지용 타일
	{
		FVector2D Location = { static_cast<float>(0), static_cast<float>(ScreenY - 298 - 36 + 4) };
		FVector2D StartPos = Location;

		CroppatchTile = GetWorld()->SpawnActor<ATileMap>();
		CroppatchTile->SetActorLocation(Location);
		CroppatchTile->Create("gridsmall.png", { 59, 8 }, { 36, 36 });

		int Index = 0;
		float loc = 0;

		for (int y = 0; y < 59; ++y)
		{
			for (int x = 0; x < 8; ++x)
			{
				if (4 == x)
				{
					loc -= 4;
				}
				else if (5 == x)
				{
					loc += 1;
				}
				else if (6 == x)
				{
					loc += 0.5;
				}
				else if (7 == x)
				{
					loc += 0.25;
				}

				CroppatchTile->SetTileSpriteIndex({ y, x }, { }, { 36, 36 }, { static_cast<float>(-4), -4 - loc }, { }, 0, 0, ERenderOrder::BUILDINGUP);

				CroppatchTileImage[Index] = CreateDefaultSubObject<USpriteRenderer>();
				CroppatchTileImage[Index]->SetComponentCrate(CroppatchTileImage[Index], "gridsmall2.png", { 36, 36 }, { StartPos }, ERenderOrder::BUILDINGUP);
				CroppatchTileImage[Index]->SetAlphafloat(0.75f);
				//CroppatchTileImage[Index]->SetActive(false);

				StartPos.Y += 32;
				++Index;
			}

			StartPos.Y = Location.Y;
			StartPos.X += 32;
			loc = 0;
		}
	}
}

void AUIManager::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	CursorCollision->SetComponentLocation(MousePos);
	CursorImage->SetComponentLocation({ MousePos.X - 5, MousePos.Y - 24 });

	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		if (nullptr != CroppatchTile->GetTileLocation(MousePos))
		{
			SRFarmInfo->SetSprite("FarmInfo", CroppatchTile->GetTileIndex(MousePos));
			SRFarmInfo->SetActive(true);
		}
	}
}

void AUIManager::PanelButtonTileEnter(AActor* _Actor, FTransform _Index)
{
	SRFarmInfo->SetSprite("FarmInfo", _Index.Scale.X);
	SRFarmInfo->SetActive(true);

	SRButtonBlack->SetComponentLocation({ _Index.Location.X, _Index.Location.Y });
	SRButtonBlack->SetActive(true);
}

void AUIManager::PanelButtonTileStay(AActor* _Actor, FTransform _Index)
{
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	SRFarmInfo->SetSprite("FarmInfo", _Index.Scale.X);
	SRFarmInfo->SetActive(true);

	SRButtonBlack->SetComponentLocation({ _Index.Location.X, _Index.Location.Y });
	SRButtonBlack->SetActive(true);

	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		CursorImage->SetSprite("Crops.png", 3 + 11 * _Index.Scale.X);
		CursorImage->SetActive(true);
	}
}

void AUIManager::PanelButtonTileEnd(AActor* _Actor, FTransform _Index)
{
	SRFarmInfo->SetActive(false);
	SRButtonBlack->SetActive(false);
}