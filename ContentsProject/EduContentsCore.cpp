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


	{

		UEngineDirectory BombDir;
		BombDir.MoveParentToDirectory("Resources//Image");
		BombDir.Append("bomb");

		UImageManager::GetInst().LoadFolder(BombDir.GetPathToString());

	}

	{
		// Ÿ�ϼ� �ε�
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources//Image");
		Dir.Append("TileMap//TileSet");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}


	


	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("EduWindow");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale("EduWindow", { 0, 0 }, { ScreenX, ScreenY });

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowAlpha();

	UEngineAPICore::GetCore()->GetSubWindow().SetWindowTitle("SubWindow");

	UEngineAPICore::GetCore()->GetSubWindow().SetWindowPosAndScale("SubWindow", { 0, 3 / ScreenY }, { static_cast<long>(ScreenX), static_cast<long>((ScreenY - (ScreenY / 3))) });

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->CreateLevel<ATileMapGameMode, AActor>("Tile");

	UEngineAPICore::GetCore()->OpenLevel("Tile");

}

void EduContentsCore::Tick()
{
	// ���� ���� �뵵�� ã�� ���ؼ� ������� �ʴ� �Լ��Դϴ�.
}