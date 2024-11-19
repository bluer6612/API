#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Fade.h"
#include "Score.h"

#include "MenuPanelUI.h"

#include "Rusty.h"
#include "House.h"
#include "Well.h"
#include "Biofuelconverter.h"

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/Level.h>
#include <EngineCore/EngineAPICore.h>

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	//타일
	{
		GroundTileMap = GetWorld()->SpawnActor<ATileMap>();
		GroundTileMap->SetActorLocation({ static_cast<float>(0), static_cast<float>(ScreenY - 298 - 36 - 2) });
		GroundTileMap->Create("EmptyTile.png", { 53, 8 }, { 36, 36 });

		for (int y = 0; y < 53; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				GroundTileMap->SetTileIndex({ y, x }, { 0, 0 }, { 36, 36 }, { 0, 0 }, 0);
			}
		}
	}

	{
		FVector2D Location = { static_cast<float>(ScreenX) - 256 + 22 - 153 - 51 , ScreenHY + 93 - 120 - 22 };

		PanelButtonTile = GetWorld()->SpawnActor<ATileMap>();
		PanelButtonTile->SetActorLocation({ Location.X, Location.Y });
		PanelButtonTile->Create("000_MenuPanel.png", { 4, CropsCount / 4 }, { 102, 44 });

		int i = 0;
		for (int x = 0; x < CropsCount / 4; x++)
		{
			for (int y = 0; y < 4; y++)
			//for (int x = 0; x < CropsCount / 4; x++)
			{
				++i;
				if (i == 4)
				{
					++x;
					y = 0;
					//continue;
				}

				PanelButtonTile->SetTileIndex({ y, x }, { 0, 0 }, { 102, 44 }, { 2, 2 }, 0);
			}
		}
	}

	{
		SpriteRFarmInfo = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRFarmInfo->SetComponentCrate(SpriteRFarmInfo, "Info", 0, { 1 , 1 }, { static_cast<float>(ScreenX - 256 + 22) - 341, (ScreenHY + 93 - 2) }, ERenderOrder::UIUP);
		SpriteRFarmInfo->SetActive(false);
	}

	//BGM
	BGMPlayer = UEngineSound::Play("Echo-metal-1.wav");

	//캐릭터
	ARusty* Rusty = AActor::GetWorld()->GetPawn<ARusty>();

	//건물
	AHouse* House = AActor::GetWorld()->SpawnActor<AHouse>();
	AWell* Well = AActor::GetWorld()->SpawnActor<AWell>();
	ABiofuelconverter* Biofuelconverter = AActor::GetWorld()->SpawnActor<ABiofuelconverter>();

	//타이틀
	{
		//TitleLogo* NewActor = AActor::GetWorld()->SpawnActor<TitleLogo>();
	}

	//맵
	{
		APlayMap* NewActor = AActor::GetWorld()->SpawnActor<APlayMap>();
	}

	//패널 메뉴
	{
		//AMenuPanelUI* NewActor = AActor::GetWorld()->SpawnActor<AMenuPanelUI>();
	}

	//{
	//	AScore* NewActor = GetWorld()->SpawnActor<AScore>();

	//	NewActor->SetActorLocation({1600, 800});
	//	NewActor->SetTextSpriteName("Text.png");
	//	NewActor->SetOrder(ERenderOrder::UI);
	//	NewActor->SetTextScale({ 7, 14 });
	//	NewActor->SetValue(134567890);
	//}

	//페이드
	//{
	//	AFade* Actor = GetWorld()->SpawnActor<AFade>();
	//	Actor->FadeOut();
	//} 
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	if (nullptr != PanelButtonTile->GetTileLocation(MousePos))
	{
		{	
			FIntPoint Point = PanelButtonTile->GetTileLocationIndex(MousePos);
			Point = PanelButtonTile->GetCalIndex(Point);
			SpriteRFarmInfo->SetSprite("Info", Point.X * Point.Y);
			SpriteRFarmInfo->SetActive(true);
		}
	}
	else
	{
		SpriteRFarmInfo->SetActive(false);
	}


	//if (true == UEngineInput::GetInst().IsPress('R'))
	//{
	//	UEngineSerializer _Ser;
	//	GroundTileMap->Serialize(_Ser);
	//	UEngineDirectory Dir;

	//	if (false == Dir.MoveParentToDirectory("Resources"))
	//	{
	//		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
	//		return;
	//	}

	//	Dir.Append("Data");

	//	std::string SaveFilePath = Dir.GetPathToString() + "\\MapData.Data";
	//	UEngineFile NewFile = SaveFilePath;
	//	NewFile.FileOpen("wb");
	//	NewFile.Write(_Ser);
	//}

	//if (true == UEngineInput::GetInst().IsPress('P'))
	//{
	//	UEngineRandom Random;
	//	for (size_t y = 0; y < 10; y++)
	//	{
	//		int Value = Random.RandomInt(0, 100);
	//		UEngineDebug::OutPutString(std::to_string(Value));
	//	}
	//}

	//if (true == UEngineInput::GetInst().IsPress('T'))
	//{
	//	UEngineDirectory Dir;

	//	if (false == Dir.MoveParentToDirectory("Resources"))
	//	{
	//		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
	//		return;
	//	}

	//	Dir.Append("Data");

	//	std::string SaveFilePath = Dir.GetPathToString() + "\\MapData.Data";
	//	UEngineFile NewFile = SaveFilePath;
	//	NewFile.FileOpen("rb");

	//	UEngineSerializer Ser;
	//	NewFile.Read(Ser);

	//	GroundTileMap->DeSerialize(Ser);
	//}

	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		GroundTileMap->AddActorLocation(FVector2D::LEFT * _DeltaTime * 100.0f);
	}

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		GroundTileMap->AddActorLocation(FVector2D::RIGHT * _DeltaTime * 100.0f);
	}

	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		GroundTileMap->AddActorLocation(FVector2D::UP * _DeltaTime * 100.0f);
	}

	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		GroundTileMap->AddActorLocation(FVector2D::DOWN * _DeltaTime * 100.0f);
	}
}