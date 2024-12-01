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

	//UI Manager

	AUIManager* UIManager = nullptr;
	{
		UIManager = GetWorld()->SpawnActor<AUIManager>();
	}

	//Building Manager
	{
		ABuildingManager* BuildingManager = GetWorld()->SpawnActor<ABuildingManager>();
		BuildingManager->SetUIManager(UIManager);
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

	//캐릭터
	{
		ARusty* Rusty = AActor::GetWorld()->GetPawn<ARusty>();
		Rusty->SetUIManager(UIManager);
	}

	//건물
	{
		AHouse* House = AActor::GetWorld()->SpawnActor<AHouse>();
		House->SetUIManager(UIManager);
		AWell* Well = AActor::GetWorld()->SpawnActor<AWell>();
		Well->SetUIManager(UIManager);
		ABiofuelconverter* Biofuelconverter = AActor::GetWorld()->SpawnActor<ABiofuelconverter>();
		Biofuelconverter->SetUIManager(UIManager);
		ACroppatch* Croppatch = AActor::GetWorld()->SpawnActor<ACroppatch>();
	}

	//맵
	{
		APlayMap* NewActor = AActor::GetWorld()->SpawnActor<APlayMap>();
	}

	//BGM
	//BGMPlayer = UEngineSound::Play("Rustys_Retirement-Full_OST_Master.mp3");

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
}