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
	//농사 통계
	FarmingStats.resize(CropsCount);

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

	//패널 탭 버튼
	{
		//패널 X 버튼
		{
			U2DCollision* Collision = CreateDefaultSubObject<U2DCollision>();
			Collision->SetCollisionGroup(UICollisionGroup::Panel);
			Collision->SetCollisionType(ECollisionType::Rect);
			Collision->SetComponentLocation({ static_cast<float>(ScreenX - 475), (ScreenHY - 44) });
			Collision->SetComponentScale({ 16, 16 });

			Collision->SetCollisionStay(std::bind(&AUIManager::TapButtonStay, this, std::placeholders::_1, FTransform(FVector2D(-1, 0), FVector2D({}) )));

			PanelAllVector.push_back(Collision);
		}

		//패널 탭 버튼 1~9
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

				PanelAllVector.push_back(Collision);

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

	//건물 타일
	{
		GroundTileMap = GetWorld()->SpawnActor<ATileMap>();
		GroundTileMap->SetActorLocation({ static_cast<float>(0), static_cast<float>(ScreenY - 296 - TaskbarY) });
		GroundTileMap->Create("GroundTile.png", { 56, 8 }, { 34, 34 });

		for (int y = 0; y < 56; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				GroundTileMap->SetTileSpriteIndex({ y, x }, { 1, 1 }, { 33, 33 }, 0);
			}
		}
	}

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

	//농사 타일
	{
		FVector2D Location = { static_cast<float>(0), static_cast<float>(ScreenHY - 32 - 16 + 8) };
		FVector2D Location2 = { static_cast<float>(17), static_cast<float>(ScreenHY - 32 - 16 + 25 ) };
		FVector2D StartPos = Location2;

		CroppatchTile = GetWorld()->SpawnActor<ATileMap>();
		CroppatchTile->SetActorLocation(Location);
		CroppatchTile->Create("EmptyTile.png", { 56, 8 }, { 34, 34 });

		int Index = 0;

		for (int y = 0; y < 8; ++y)
		{
			for (int x = 0; x < 56; ++x)
			{
				CroppatchTile->SetTileSpriteIndex({ x, y }, { 1, 1 }, { 33, 33 }, 0, Index, ERenderOrder::BUILDINGUP);
				//CroppatchTile->GetTileByLocation(StartPos)->SetCropsIndex(-2);
				CroppatchTile->GetTileByLocation(StartPos)->SetCropsIndex(-1);
				CroppatchTile->GetTileByLocation(StartPos)->SetLocation(StartPos);

				CroppatchTileImage[Index] = CreateDefaultSubObject<USpriteRenderer>();
				CroppatchTileImage[Index]->SetComponentCrate(CroppatchTileImage[Index], "EmptyTile.png", { 34, 34 }, { StartPos }, ERenderOrder::BUILDINGTILE);
				CroppatchTileImage[Index]->SetPivotType(PivotType::Bot);
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

	CreateText(ResourcesText[0], { static_cast<float>(ScreenHX + 22), static_cast<float>(ScreenY - 48) }, Money, false);
	CreateText(ResourcesText[1], { static_cast<float>(ScreenHX - 22), static_cast<float>(ScreenY - 48) }, Bio, true);
	CreateText(ResourcesText[2], { static_cast<float>(ScreenX - 310), static_cast<float>(ScreenHY + 225) }, Money, false, ERenderOrder::UITOP);
	CreateText(ResourcesText[3], { static_cast<float>(ScreenX - 360), static_cast<float>(ScreenHY + 225) }, Bio, true, ERenderOrder::UITOP);
}

void AUIManager::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	CursorCollision->SetComponentLocation(MousePos);
	CursorImage->SetComponentLocation({ MousePos.X - 5, MousePos.Y - 24 });

	if (true == UEngineInput::GetInst().IsPress(VK_LBUTTON) && -1 != NowSelectCrops && false == CursorOnTap)
	{
		if (nullptr != CroppatchTile->GetTileByLocation(MousePos))
		{
			Tile* CropTile = CroppatchTile->GetTileByLocation(MousePos);

			if (CropsNeedMoney[NowSelectCrops] <= Money)
			{
				int Index = CroppatchTile->GetTileIndex(MousePos);

				if (-1 == CropTile->GetCropsIndex())
				{
					Money -= CropsNeedMoney[NowSelectCrops];

					CropTile->CropsReset(Index, NowSelectCrops);
					CropTile->SetLocation(CroppatchTileImage[Index]->GetComponentLocation());

					CroppatchTile->SetCropsTileSprite(CroppatchTileImage[Index]->GetComponentLocation(), 0);

					CroppatchTileImage[Index]->SetActive(true);
					CroppatchTileImage[Index]->SetSprite("Crops.png", 3 + 11 * NowSelectCrops);
					CroppatchTileImage[Index]->SetComponentScale({ 32, 64 });
					CroppatchTileImage[Index]->SetAlphafloat(1.f);

					CropsAllVector.push_back(CropTile);
				}
			}
		}
	}

	if (true == UEngineInput::GetInst().IsDown(VK_RBUTTON))
	{
		NowSelectCrops = -1;
		CursorImage->SetActive(false);

		FVector2D Location = { static_cast<float>(17), static_cast<float>(ScreenHY - 32 - 16 + 25) };
		FVector2D StartPos = Location;
		int Index = 0;

		for (int y = 0; y < 8; ++y)
		{
			for (int x = 0; x < 56; ++x)
			{
				if (-1 == CroppatchTile->GetTileByLocation(StartPos)->GetCropsIndex())
				{
					CroppatchTile->SetCropsTileSprite(StartPos, 0);
				}

				++Index;
				StartPos.X += 34;
			}

			StartPos.X = Location.X;
			StartPos.Y += 34;
		}
	}
}

void AUIManager::TapButtonIn()
{
	if (4 > TapTimer)
	{
		MenuPanelUI->AddActorLocation({ 116, 0 });
		SRTapWhite->AddComponentLocation({ 116, 0 });
		ResourcesText[2]->SetActive(false);
		ResourcesText[3]->SetActive(false);

		for (int i = 0; i < PanelAllVector.size(); ++i)
		{
			PanelAllVector[i]->AddComponentLocation({ 116, 0 });
			PanelAllVector[i]->SetActive(false);
		}

		++TapTimer;
	}
	else
	{
		for (int i = 0; i < PanelAllVector.size(); ++i)
		{
			PanelAllVector[i]->SetActive(true);
		}
	}
}

void AUIManager::TapButtonOut()
{
	if (0 < TapTimer)
	{
		MenuPanelUI->AddActorLocation({ -116, 0 });
		SRTapWhite->AddComponentLocation({ -116, 0 });
		ResourcesText[2]->SetActive(true);
		ResourcesText[3]->SetActive(true);

		for (int i = 0; i < PanelAllVector.size(); ++i)
		{
			PanelAllVector[i]->AddComponentLocation({ -116, 0 });
			PanelAllVector[i]->SetActive(false);
		}

		--TapTimer;
	}
	else
	{
		for (int i = 0; i < PanelAllVector.size(); ++i)
		{
			PanelAllVector[i]->SetActive(true);
		}
	}
}

void AUIManager::TapButtonStay(AActor* _Actor, FTransform _Index)
{
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		NowSelectTap = _Index.Scale.X;

		if (0 == TapTimer && -1 == NowSelectTap)
		{
			TimeEventer.PushEvent(1.0f, std::bind(&AUIManager::TapButtonIn, this), true, false);

			//X 버튼이 아니면 화이트 이동
			if (-1 != NowSelectTap)
			{
				SRTapWhite->SetComponentLocation({ _Index.Location.X + (116 * 4), _Index.Location.Y});
			}
		}
		else if (4 == TapTimer)
		{
			TimeEventer.PushEvent(0.5f, std::bind(&AUIManager::TapButtonOut, this), true, false);

			//X 버튼이 아니면 화이트 이동
			if (-1 != NowSelectTap)
			{
				SRTapWhite->SetComponentLocation({ _Index.Location.X + (116 * 4), _Index.Location.Y });
			}
		}
		else
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

	CursorOnTap = true;
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
		//if (0 == _Index.Scale.X)
		{
			NowSelectCrops = _Index.Scale.X;
			CursorImage->SetSprite("Crops.png", 3 + 11 * NowSelectCrops);
			CursorImage->SetActive(true);

			FVector2D Location = { static_cast<float>(17), static_cast<float>(ScreenHY - 32 - 16 + 25) };
			FVector2D StartPos = Location;
			int Index = 0;

			for (int y = 0; y < 8; ++y)
			{
				for (int x = 0; x < 56; ++x)
				{
					if (-1 == CroppatchTile->GetTileByLocation(StartPos)->GetCropsIndex())
					{
						CroppatchTile->SetCropsTileSprite(StartPos, 1);
					}

					++Index;
					StartPos.X += 34;
				}

				StartPos.X = Location.X;
				StartPos.Y += 34;
			}
		}
	}

	CursorOnTap = true;
}

void AUIManager::PanelButtonTileEnd(AActor* _Actor, FTransform _Index)
{
	SRFarmInfo->SetActive(false);
	SRButtonBlack->SetActive(false);

	CursorOnTap = false;
}