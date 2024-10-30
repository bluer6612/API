#include "PreCompile.h"
#include "MainContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>

#include "PlayGameMode.h"
#include "Player.h"

MainContentsCore::MainContentsCore()
{
}

MainContentsCore::~MainContentsCore()
{
}

// ������ ����ǰ� �� 1�� ����ȴ�.
void MainContentsCore::BeginPlay()
{
	// UEngineDirectory Dir = "C:\\AAA";

	UEngineDirectory Dir;

	// ����ΰ� �߿��ϴ�.
	// ��� ����� �ٽ��� �̰��̴�.
	// ���� ��� ����ƴ����� �߿����� �ʾƾ� �Ѵ�.
	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
		return;
	}

	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}


	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("MainWindow");

	// �̰� �� ȣ������� �մϴ�.
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, (ScreenY - (ScreenY / 3)) - 10 - 30 }, { WS_SYSMENU, ScreenY / 3 });

	UEngineAPICore::GetCore()->GetSubWindow().SetWindowTitle("SubWindow");

	UEngineAPICore::GetCore()->GetSubWindow().SetWindowPosAndScale({ 0, 3 / ScreenY }, { WS_SYSMENU, (ScreenY - (ScreenY / 3)) });

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	//UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void MainContentsCore::Tick()
{
	// ���� ���� �뵵�� ã�� ���ؼ� ������� �ʴ� �Լ��Դϴ�.
}