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
#include "Player.h"
#include "ANewPlayer.h"
#include "TitleLogo.h"


EduContentsCore::EduContentsCore()
{
}

EduContentsCore::~EduContentsCore()
{
}

// ������ ����ǰ� �� 1�� ����ȴ�.
void EduContentsCore::BeginPlay()
{
	// UEngineDirectory Dir = "C:\\AAA";

	UEngineDirectory Dir;

	// ����ΰ� �߿��ϴ�.
	// ��� ����� �ٽ��� �̰��̴�.
	// ���� ��� ����ƴ����� �߿����� �ʾƾ� �Ѵ�.
	// �������� ������ ���� �����̰�.
	// �����е��� �������� �ϴ°� �����մϴ�.
	// Global / ������ ���õ� 

	// ����� ���� �� ������Ʈ�� ���� �ȿ� �ִ� Resourcesã�� ������� ó���ߴ�.
	// 
	// if (false == Dir.MoveParentToDirectory("fasdjklfadsjklf"))
	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
		return;
	}

	Dir.Append("Image");

	// ��� ���� �� ������
	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}

	// �Ϲ� �ؽ�ó�� �� �ε��Ǹ�
	// �ڸ��� �۾��� �Ʒ��� ���ִ°� ����.

	UImageManager::GetInst().CuttingSprite("Player_Right.png", {128, 128});
	UImageManager::GetInst().CuttingSprite("Text.bmp", { 16, 32 });

	{
		// Ÿ�ϼ� �ε�
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources");
		Dir.Append("Image//TileMap//TileSet");
		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	}

	{
		// UI �ε�
		UEngineDirectory UIDir;
		UIDir.MoveParentToDirectory("Resources");
		UIDir.Append("Image//UI");
		UImageManager::GetInst().LoadFolder(UIDir.GetPathToString());
	}


	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("EduWindow");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ static_cast <float>(0), (ScreenY - static_cast<float>(ScreenY * 0.34)) }, { static_cast<float>(ScreenX), static_cast<float>(ScreenY * 0.3) });
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowAlpha();

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, ANewPlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, TitleLogo>("Title");
	UEngineAPICore::GetCore()->CreateLevel<ATileMapGameMode, AActor>("Tile");

	UEngineAPICore::GetCore()->OpenLevel("Play");

}

void EduContentsCore::Tick()
{
	// ���� ���� �뵵�� ã�� ���ؼ� ������� �ʴ� �Լ��Դϴ�.
}