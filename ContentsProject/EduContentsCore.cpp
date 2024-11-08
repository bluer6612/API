#include "PreCompile.h"
#include "EduContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>

#include "TitleGameMode.h"
#include "PlayGameMode.h"
#include "TileMapGameMode.h"
#include "Rusty.h"
#include "TitleLogo.h"


EduContentsCore::EduContentsCore()
{
}

EduContentsCore::~EduContentsCore()
{
}

void EduContentsCore::BeginPlay()
{
	
	UEngineDirectory Dir;

						
				if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}

	Dir.Append("Image");

		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}

		
	//UImageManager::GetInst().CuttingSprite("Player_Right.png", {128, 128});
	UImageManager::GetInst().CuttingSprite("Text.bmp", { 16, 32 });
				
	{
		// 타일셋 로드
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources//Image");
		Dir.Append("TileMap//TileSet");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}

	{
		// UI 로드
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources//Image");
		Dir.Append("UI");
		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	}

	{
		// Character 로드
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources//Image//Character");
		Dir.Append("RustyGold");
		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	}


	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("EduWindow");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ static_cast <float>(0), (ScreenY - static_cast<float>(ScreenY * 0.34)) }, { static_cast<float>(ScreenX), static_cast<float>(ScreenY * 0.3) });
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowAlpha();

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, ARusty>("Play");
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, TitleLogo>("Title");
	UEngineAPICore::GetCore()->CreateLevel<ATileMapGameMode, AActor>("Tile");

	UEngineAPICore::GetCore()->OpenLevel("Play");

}

void EduContentsCore::Tick()
{
	}