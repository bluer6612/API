#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Fade.h"
#include "Score.h"

#include "Rusty.h"
#include "House.h"
#include "Well.h"
#include "Biofuelconverter.h"
#include "Croppatch.h"

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/Level.h>
#include <EngineCore/EngineAPICore.h>

#include <EnginePlatform/EngineSound.h>

#include "BuildingManager.h"
#include "CharacterManager.h"
#include "FarmingManager.h"
#include "UIManager.h"
#include "PlayMap.h"

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
		GroundTileMap->SetActorLocation({ static_cast<float>(0), static_cast<float>(ScreenY - 296 - TaskbarY) });
		GroundTileMap->Create("EmptyTile.png", { 53, 8 }, { 32, 32 });

		for (int y = 0; y < 53; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				GroundTileMap->SetTileSpriteIndex({ y, x }, { }, { 32, 32 }, { 4, 4 }, { }, 0);
			}
		}
	}

	//UI Manager
	AUIManager* UIManager = nullptr;
	ABuildingManager* BuildingManager = nullptr;
	{
		UIManager = GetWorld()->SpawnActor<AUIManager>();
		SetUIManager(UIManager);
	}

	//Building Manager
	{
		BuildingManager = GetWorld()->SpawnActor<ABuildingManager>();
		//BuildingManager->SetBuildingManager(BuildingManager);
	}

	//Farming Manager
	{
		AFarmingManager* FarmingManager = GetWorld()->SpawnActor<AFarmingManager>();
		FarmingManager->SetUIManager(UIManager);
	}

	//Character Manager
	{
		ACharacterManager* CharacterManager = GetWorld()->SpawnActor<ACharacterManager>();
		CharacterManager->SetUIManager(UIManager);
	}

	//BGM
	BGMPlayer = UEngineSound::Play("Rustys_Retirement-Full_OST_Master.mp3");

	//캐릭터
	{
		ARusty* Rusty = AActor::GetWorld()->GetPawn<ARusty>();
	}

	//건물
	{
		AHouse* House = AActor::GetWorld()->SpawnActor<AHouse>();
		AWell* Well = AActor::GetWorld()->SpawnActor<AWell>();
		ABiofuelconverter* Biofuelconverter = AActor::GetWorld()->SpawnActor<ABiofuelconverter>();
		ACroppatch* Croppatch = AActor::GetWorld()->SpawnActor<ACroppatch>();
	}

	//맵
	{
		APlayMap* NewActor = AActor::GetWorld()->SpawnActor<APlayMap>();
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

	//if (true == UEngineInput::GetInst().IsPress('A'))
	//{
	//	GroundTileMap->AddActorLocation(FVector2D::LEFT * _DeltaTime * 100.0f);
	//}

	//if (true == UEngineInput::GetInst().IsPress('D'))
	//{
	//	GroundTileMap->AddActorLocation(FVector2D::RIGHT * _DeltaTime * 100.0f);
	//}

	//if (true == UEngineInput::GetInst().IsPress('W'))
	//{
	//	GroundTileMap->AddActorLocation(FVector2D::UP * _DeltaTime * 100.0f);
	//}

	//if (true == UEngineInput::GetInst().IsPress('S'))
	//{
	//	GroundTileMap->AddActorLocation(FVector2D::DOWN * _DeltaTime * 100.0f);
	//}
}