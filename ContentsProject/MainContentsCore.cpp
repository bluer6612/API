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

// 엔진이 실행되고 단 1번 실행된다.
void MainContentsCore::BeginPlay()
{
	// UEngineDirectory Dir = "C:\\AAA";

	UEngineDirectory Dir;

	// 상대경로가 중요하다.
	// 상대 경로의 핵심은 이것이다.
	// 내가 어디서 실행됐는지는 중요하지 않아야 한다.
	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}

	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}


	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("MainWindow");

	// 이거 꼭 호출해줘야 합니다.
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, (ScreenY - (ScreenY / 3)) - 10 - 30 }, { WS_SYSMENU, ScreenY / 3 });

	UEngineAPICore::GetCore()->GetSubWindow().SetWindowTitle("SubWindow");

	UEngineAPICore::GetCore()->GetSubWindow().SetWindowPosAndScale({ 0, 3 / ScreenY }, { WS_SYSMENU, (ScreenY - (ScreenY / 3)) });

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	//UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void MainContentsCore::Tick()
{
	// 지금 전혀 용도를 찾지 못해서 사용하지 않는 함수입니다.
}