#include "PreCompile.h"
#include "MainContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>
#include <EnginePlatform/EngineSound.h>

#include "PlayGameMode.h"
#include "Rusty.h"
#include "TitleLogo.h"


MainContentsCore::MainContentsCore()
{
}

MainContentsCore::~MainContentsCore()
{
}

void MainContentsCore::BeginPlay()
{
	UEngineDirectory Dir;

	//�̹��� �ε�
	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
		return;
	}

	Dir.Append("Image");

	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}

	//���� �ε�
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Sound");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineSound::Load(FilePath);
		}
	}

	UImageManager::GetInst().CuttingSprite("Text.bmp", { 16, 32 });
	UImageManager::GetInst().CuttingSprite("Crops.png", { 16, 32 });
	UImageManager::GetInst().CuttingSprite("Crops_Lock.png", { 16, 32 });

	DirectoryAdd("", "TileMap");
	DirectoryAdd("", "Title");
	DirectoryAdd("", "Menu");
	DirectoryAdd("Character", "RustyGold");
	DirectoryAdd("Building", "House");
	DirectoryAdd("Building", "Well");
	DirectoryAdd("Building", "Biofuelconverter");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("MainWindow");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ static_cast <float>(0), (ScreenY - static_cast<float>(ScreenY)) }, { static_cast<float>(ScreenX), static_cast<float>(ScreenY) });
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowAlpha();

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, ARusty>("Play");

	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void MainContentsCore::Tick()
{
}

void MainContentsCore::DirectoryAdd(std::string _dir, std::string _Append)
{
	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources//Image//"+ _dir);
		Dir.Append(_Append);
		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	}
}