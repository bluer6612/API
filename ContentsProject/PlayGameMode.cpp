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
	//{
	//	GroundTileMap = GetWorld()->SpawnActor<ATileMap>();
	//}

	//{
	//	WallTileMap = GetWorld()->SpawnActor<ATileMap>();
	//	WallTileMap->Create("TileSet", { 48, 8 }, { 48, 40 });

	//	//for (int y = 0; y < 40; y++)
	//	//{
	//	//	for (int x = 0; x < 40; x++)
	//	//	{
	//	//		WallTileMap->SetTileIndex({ y,x }, { 0, 0 }, { 48, 40 }, 1);
	//	//	}
	//	//}
	//}

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
		AMenuPanelUI* NewActor = AActor::GetWorld()->SpawnActor<AMenuPanelUI>();
	}

	//{
	//	AScore* NewActor = GetWorld()->SpawnActor<AScore>();

	//	NewActor->SetActorLocation({900, 900});
	//	NewActor->SetTextSpriteName("Text.bmp");
	//	NewActor->SetOrder(ERenderOrder::UI);
	//	NewActor->SetTextScale({ 5, 10 });
	//	NewActor->SetValue(45362784);
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

	//if (true == UEngineInput::GetInst().IsPress(VK_LBUTTON))
	//{
	//	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	//	WallTileMap->SetTileLocation(MousePos, 1);
	//}

	//if (true == UEngineInput::GetInst().IsPress(VK_RBUTTON))
	//{
	//	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	//	Tile* Tile = WallTileMap->GetTileRef(MousePos);
	//	if (nullptr != Tile->SpriteRenderer)
	//	{
	//		Tile->SpriteRenderer->Destroy(5.0f);
	//		Tile->SpriteRenderer = nullptr;
	//	}
	//}


	if (true == UEngineInput::GetInst().IsPress('R'))
	{
		UEngineSerializer _Ser;
		WallTileMap->Serialize(_Ser);
		UEngineDirectory Dir;

		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Data");

		std::string SaveFilePath = Dir.GetPathToString() + "\\MapData.Data";
		UEngineFile NewFile = SaveFilePath;
		NewFile.FileOpen("wb");
		NewFile.Write(_Ser);
	}

	if (true == UEngineInput::GetInst().IsPress('P'))
	{
		UEngineRandom Random;
		for (size_t i = 0; i < 10; i++)
		{
			int Value = Random.RandomInt(0, 100);
			UEngineDebug::OutPutString(std::to_string(Value));
		}
	}

	if (true == UEngineInput::GetInst().IsPress('T'))
	{
		UEngineDirectory Dir;

		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Data");

		std::string SaveFilePath = Dir.GetPathToString() + "\\MapData.Data";
		UEngineFile NewFile = SaveFilePath;
		NewFile.FileOpen("rb");

		UEngineSerializer Ser;
		NewFile.Read(Ser);

		WallTileMap->DeSerialize(Ser);
	}

	//if (true == UEngineInput::GetInst().IsPress('A'))
	//{
	//	WallTileMap->AddActorLocation(FVector2D::LEFT * _DeltaTime * 100.0f);
	//}

	//if (true == UEngineInput::GetInst().IsPress('D'))
	//{
	//	WallTileMap->AddActorLocation(FVector2D::RIGHT * _DeltaTime * 100.0f);
	//}

	//if (true == UEngineInput::GetInst().IsPress('W'))
	//{
	//	WallTileMap->AddActorLocation(FVector2D::UP * _DeltaTime * 100.0f);
	//}

	//if (true == UEngineInput::GetInst().IsPress('S'))
	//{
	//	WallTileMap->AddActorLocation(FVector2D::DOWN * _DeltaTime * 100.0f);
	//}
}