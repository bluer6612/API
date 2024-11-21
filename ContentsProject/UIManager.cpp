#include "PreCompile.h"
#include "UIManager.h"

#include "MenuPanelUI.h"
#include "TitleLogo.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>

AUIManager::AUIManager()
{
	{
		GetWorld()->CollisionGroupLink(UICollisionGroup::Panel, UICollisionGroup::Cursor);
		GetWorld()->CollisionGroupLink(UICollisionGroup::Building, UICollisionGroup::Cursor);
		GetWorld()->CollisionGroupLink(UICollisionGroup::Croppatch, UICollisionGroup::Cursor);
		

		CursorCollision = CreateDefaultSubObject<U2DCollision>();
		CursorCollision->SetCollisionGroup(UICollisionGroup::Cursor);
		CursorCollision->SetCollisionType(ECollisionType::Rect);
		CursorCollision->SetComponentScale({ 1, 1 });

		CursorImage = CreateDefaultSubObject<USpriteRenderer>();
		CursorImage->SetSprite("Crops.png", 3);
		CursorImage->SetComponentScale({ 32, 64 });
		CursorImage->SetActive(false);
		//CursorCollision->DebugOn();
	}

	//��� ���콺 on �� ����
	{
		SRFarmInfo = CreateDefaultSubObject<USpriteRenderer>();
		SRFarmInfo->SetComponentCrate(SRFarmInfo, "FarmInfo", 0, { 1 , 1 }, { static_cast<float>(ScreenX - 256 + 22) - 341, (ScreenHY + 93 - 2) }, ERenderOrder::UIUP);
		SRFarmInfo->SetActive(false);
	}

	//��� ���콺 on �� ���� ó��
	{
		SRButtonBlack = CreateDefaultSubObject<USpriteRenderer>();
		SRButtonBlack->SetComponentCrate(SRButtonBlack, "003_crop-seed-button_Black.png", {}, { static_cast<float>(ScreenX) - (104 * 4) + 29 , ScreenHY + 93 - 120 }, ERenderOrder::UIUP);
		SRButtonBlack->SetAlphafloat(0.35f);
		SRButtonBlack->SetActive(false);
	}


	//��� �г� ��ư
	{
		FarmInfoIndex.resize(CropsCount);

		FVector2D Location = { static_cast<float>(ScreenX) - (104 * 4) + 29 , ScreenHY + 93 - 120 };
		FVector2D StartPos = Location;

		int Index = 0;
		for (int y = 0; y < 6; y++)
		{
			for (int x = 0; x < 4; x++)
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

	AMenuPanelUI* NewActor = AActor::GetWorld()->SpawnActor<AMenuPanelUI>();

	//Ÿ��Ʋ
	{
		//TitleLogo* NewActor = AActor::GetWorld()->SpawnActor<TitleLogo>();
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
		//CursorCollision->CollisionEventCheck()
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
	SRFarmInfo->SetSprite("FarmInfo", _Index.Scale.X);
	SRFarmInfo->SetActive(true);

	SRButtonBlack->SetComponentLocation({ _Index.Location.X, _Index.Location.Y });
	SRButtonBlack->SetActive(true);
}

void AUIManager::PanelButtonTileEnd(AActor* _Actor, FTransform _Index)
{
	SRFarmInfo->SetActive(false);
	SRButtonBlack->SetActive(false);
}
