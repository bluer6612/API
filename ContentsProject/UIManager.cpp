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

	//농사 모드 씨앗 이미지
	CursorImage = CreateDefaultSubObject<USpriteRenderer>();
	CursorImage->SetSprite("Crops.png", 3);
	CursorImage->SetComponentScale({ 34, 64 });
	CursorImage->SetOrder(ERenderOrder::CURSOR);
	CursorImage->SetActive(false);

	//농사 마우스 on 시 설명
	SRFarmInfo = CreateDefaultSubObject<USpriteRenderer>();
	SRFarmInfo->SetComponentCrate(SRFarmInfo, "FarmInfo", 0, { 1 , 1 }, { static_cast<float>(ScreenX - 575), (ScreenHY + 91) }, ERenderOrder::UIUP);
	SRFarmInfo->SetActive(false);

	//농사 마우스 on 시 음영 처리
	SRButtonBlack = CreateDefaultSubObject<USpriteRenderer>();
	SRButtonBlack->SetComponentCrate(SRButtonBlack, "003_crop-seed-button_Black.png", {}, { static_cast<float>(ScreenX) - (104 * 4) + 29 , ScreenHY + 93 - 120 }, ERenderOrder::UIUP);
	SRButtonBlack->SetAlphafloat(0.35f);
	SRButtonBlack->SetActive(false);

	SRTapWhite = CreateDefaultSubObject<USpriteRenderer>();
	SRTapWhite->SetComponentCrate(SRTapWhite, "004_MenuPanel_pressed.png", {}, { static_cast<float>(ScreenX - 480), (ScreenHY - 5) }, ERenderOrder::UIUP);

	//농사 탭 버튼
	{
		//패널 X 버튼
		U2DCollision* Collision = CreateDefaultSubObject<U2DCollision>();
		Collision->SetCollisionGroup(UICollisionGroup::Panel);
		Collision->SetCollisionType(ECollisionType::Rect);
		Collision->SetComponentLocation({ static_cast<float>(ScreenX - 475), (ScreenHY - 44) });
		Collision->SetComponentScale({ 16, 16 });

		Collision->SetCollisionStay(std::bind(&AUIManager::TapButtonStay, this, std::placeholders::_1, FTransform(FVector2D(-1, 0), FVector2D({}))));

		FVector2D Location = { static_cast<float>(ScreenX - 480), (ScreenHY - 5) };
		FVector2D StartPos = Location;

		int Index = 0;
		for (int y = 0; y < 2; ++y)
		{
			for (int x = 0; x < 5; ++x)
			{
				U2DCollision* Collision = CreateDefaultSubObject<U2DCollision>();
				Collision->SetCollisionGroup(UICollisionGroup::Panel);
				Collision->SetCollisionType(ECollisionType::Rect);
				Collision->SetComponentLocation(StartPos);
				Collision->SetComponentScale({ 36, 36 });

				Collision->SetCollisionStay(std::bind(&AUIManager::TapButtonStay, this, std::placeholders::_1, FTransform(FVector2D(Index, 0), FVector2D(StartPos))));

				if (3 == x && 1 == y)
				{
					break;
				}

				++Index;
				StartPos.Y += 48;
			}

			StartPos.X -= 32;
			StartPos.Y = Location.Y + 24;
		}
	}
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

				PanelAllVector.push_back(Collision);

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

	//타이틀
	{
		//TitleLogo* NewActor = AActor::GetWorld()->SpawnActor<TitleLogo>();
	}

	//패널
	AMenuPanelUI* MenuPanelUI = nullptr;
	{
		MenuPanelUI = GetWorld()->SpawnActor<AMenuPanelUI>();

		this->SetMenuPanelUI(MenuPanelUI);
	}

	ACroppatch* Croppatch = nullptr;
	{
		Croppatch = GetWorld()->SpawnActor<ACroppatch>();

		this->SetCroppatch(Croppatch);
	}

	//농지용 타일
	{
		FVector2D Location = { static_cast<float>(0), static_cast<float>(ScreenY - 298 - 36 + 4) };
		FVector2D Location2 = { static_cast<float>(17), static_cast<float>(ScreenY - 298 - 36 + 4 + 17) };
		FVector2D StartPos = Location2;

		CroppatchTile = GetWorld()->SpawnActor<ATileMap>();
		CroppatchTile->SetActorLocation(Location);
		CroppatchTile->Create("EmptyTile.png", { 56, 8 }, { 34, 34 });

		int Index = 0;

		for (int y = 0; y < 8; ++y)
		{
			for (int x = 0; x < 56; ++x)
			{
				CroppatchTile->SetTileSpriteIndex({ x, y }, { }, { 34, 34 }, { }, { }, 0, Index, ERenderOrder::BUILDINGUP);

				CroppatchTileImage[Index] = CreateDefaultSubObject<USpriteRenderer>();
				CroppatchTileImage[Index]->SetComponentCrate(CroppatchTileImage[Index], "gridsmall.png", { 34, 34 }, { StartPos }, ERenderOrder::BUILDINGUP);
				CroppatchTileImage[Index]->SetComponentScale({33.f, 33.f});
				CroppatchTileImage[Index]->SetAlphafloat(0.75f);
				CroppatchTileImage[Index]->SetActive(false);

				StartPos.X += 34;
				++Index;
			}

			StartPos.X = Location2.X;
			StartPos.Y += 34;
		}
	}
}

void AUIManager::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	CursorCollision->SetComponentLocation(MousePos);
	CursorImage->SetComponentLocation({ MousePos.X - 5, MousePos.Y - 24 });

	if (true == UEngineInput::GetInst().IsPress(VK_LBUTTON) && -1 != NowSelectCrops)
	{
		if (nullptr != CroppatchTile->GetTileLocation(MousePos))
		{
			if (CropsNeedMoney[NowSelectCrops] <= Money)
			{
				int Index = CroppatchTile->GetTileIndex(MousePos);

				if (0 == CroppatchTile->GetCropsIndex())
				{
					Money -= CropsNeedMoney[NowSelectCrops];

					CroppatchTile->SetCropsIndex(NowSelectCrops);
					CroppatchTile->SetGrow(0);
					CroppatchTile->SetWater(0);
					CroppatchTile->SetTime(CropsNeedGrowTime[NowSelectCrops]);

					CroppatchTileImage[Index]->SetActive(true);
					CroppatchTileImage[Index]->SetSprite("Crops.png", 3 + 11 * NowSelectCrops);
					CroppatchTileImage[Index]->SetComponentScale({ 32, 64 });
				}
			}
		}
	}

	if (true == UEngineInput::GetInst().IsDown(VK_RBUTTON))
	{
		NowSelectCrops = -1;
		CursorImage->SetActive(false);
	}
}

void AUIManager::TapButtonIn()
{
	if (4 > TapTimer)
	{
		MenuPanelUI->AddActorLocation({ 116, 0 });
		SRTapWhite->AddComponentLocation({ 116, 0 });

		{
			std::vector<U2DCollision*>::iterator StartIter = PanelAllVector.begin();
			std::vector<U2DCollision*>::iterator EndIter = PanelAllVector.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				U2DCollision* CurRes = *StartIter;
				
				if (nullptr != CurRes)
				{
					CurRes->AddComponentLocation({ 116, 0 });
				}
			}
		}

		++TapTimer;
	}
}

void AUIManager::TapButtonOut()
{
	if (0 < TapTimer)
	{
		MenuPanelUI->AddActorLocation({ -116, 0 });
		SRTapWhite->AddComponentLocation({ -116, 0 });

		{
			std::vector<class U2DCollision*>::iterator StartIter = PanelAllVector.begin();
			std::vector<class U2DCollision*>::iterator EndIter = PanelAllVector.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				//std::vector<class U2DCollision*>::iterator CurRes = StartIter->second;
				//U2DCollision* CurRes = StartIter->second;
				U2DCollision* CurRes = *StartIter;

				if (nullptr != CurRes)
				{
					CurRes->AddComponentLocation({ -116, 0 });
				}
			}
		}

		--TapTimer;
	}
}

void AUIManager::TapButtonStay(AActor* _Actor, FTransform _Index)
{
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		NowSelectTap = _Index.Scale.X;

		if (0 == TapTimer)
		{
			TimeEventer.PushEvent(1.0f, std::bind(&AUIManager::TapButtonIn, this), true, false);
		}
		else if (4 == TapTimer)
		{
			TimeEventer.PushEvent(0.5f, std::bind(&AUIManager::TapButtonOut, this), true, false);
		}

		//X 버튼이 아니면 화이트 이동
		if (-1 != NowSelectTap)
		{
			SRTapWhite->SetComponentLocation({ _Index.Location.X, _Index.Location.Y });
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
		if (0 == _Index.Scale.X)
		{
			NowSelectCrops = _Index.Scale.X;
			CursorImage->SetSprite("Crops.png", 3 + 11 * NowSelectCrops);
			CursorImage->SetActive(true);
		}
	}
}

void AUIManager::PanelButtonTileEnd(AActor* _Actor, FTransform _Index)
{
	SRFarmInfo->SetActive(false);
	SRButtonBlack->SetActive(false);
}