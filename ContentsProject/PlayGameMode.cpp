#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Fade.h"

#include "Rusty.h"
#include "Haiku.h"

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
	{
		UIManager = GetWorld()->SpawnActor<AUIManager>();
		this->SetUIManager(UIManager);
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

	//ĳ����
	{
		ARusty* Rusty = AActor::GetWorld()->GetPawn<ARusty>();
		Rusty->SetUIManager(UIManager);
	}

	//�ǹ�
	{
		AHouse* House = AActor::GetWorld()->SpawnActor<AHouse>();
		House->SetUIManager(UIManager);
		AWell* Well = AActor::GetWorld()->SpawnActor<AWell>();
		Well->SetUIManager(UIManager);
		ABiofuelconverter* Biofuelconverter = AActor::GetWorld()->SpawnActor<ABiofuelconverter>();
		Biofuelconverter->SetUIManager(UIManager);
		ACroppatch* Croppatch = AActor::GetWorld()->SpawnActor<ACroppatch>();
	}

	//��
	{
		APlayMap* NewActor = AActor::GetWorld()->SpawnActor<APlayMap>();
	}

	//BGM
	BGMPlayer = UEngineSound::Play("Rustys_Retirement-Full_OST_Master.mp3");

	//���̵�
	//{
	//	AFade* Actor = GetWorld()->SpawnActor<AFade>();
	//	Actor->FadeOut();
	//} 
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown(VK_UP))
	{
		UIManager->CropsLock += 1;

		int Index = UIManager->CropsLock;

		UIManager->MenuPanelUI->SpriteRFarmCrops[Index]->SetSprite( "Crops.png", Index * 11 + 1);
		UIManager->MenuPanelUI->SpriteRFarmCoin[Index]->SetSprite("uiresourceicons_0.png");
		UIManager->MenuPanelUI->SpriteRFarmCoin[Index]->SetComponentLocation({ static_cast<float>(UIManager->MenuPanelUI->SpriteRFarmCoin[Index]->GetComponentLocation().X - std::to_string(CropsNeedMoney[Index]).size() * 7.5), (static_cast<float>(UIManager->MenuPanelUI->SpriteRFarmCoin[Index]->GetComponentLocation().Y)) });
		UIManager->CropsCountText[Index]->SetActive(true);
		UIManager->CropsPriceText[Index]->SetActive(true);
	}

	if (true == UEngineInput::GetInst().IsDown('1'))
	{
		AHaiku* Haiku = AActor::GetWorld()->SpawnActor<AHaiku>();
		Haiku->SetUIManager(UIManager);
	}


	//if (true == UEngineInput::GetInst().IsPress('R'))
	//{
	//	UEngineSerializer _Ser;
	//	GroundTileMap->Serialize(_Ser);
	//	UEngineDirectory Dir;

	//	if (false == Dir.MoveParentToDirectory("Resources"))
	//	{
	//		MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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
	//		MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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