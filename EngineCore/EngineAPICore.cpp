#include "PreCompile.h"
#include "EngineAPICore.h"
#include <string>

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

// ������ ��Ʋ� 1�� ��������� ������.
// 1�� ���õǰ� ����� �ٲ��� �����Ŵ�.
UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;


UEngineAPICore::UEngineAPICore()
{

}

UEngineAPICore::~UEngineAPICore()
{
	std::map<std::string, class ULevel*>::iterator StartIter = Levels.begin();
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

	Levels.clear();
}


int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UserCore = _UserCore;
	WNDCLASSEXA _wcex = WNDCLASSEXA();
	WNDCLASSEXA _wcexS = WNDCLASSEXA();

	UEngineWindow::EngineWindowInit(_Inst, _wcex);
	UEngineWindow::EngineWindowInit(_Inst, _wcexS);

	// ��ü �ȸ���� ��ü������ �ƴѰ� ���Ƽ� ��ü�� ����.
	UEngineAPICore Core = UEngineAPICore();
	Core.EngineMainWindow.Open("Window", _wcex.lpszClassName);
	MainCore = &Core;

	EngineDelegate Start = EngineDelegate(std::bind(EngineBeginPlay));
	EngineDelegate FrameLoop = EngineDelegate(std::bind(EngineTick));;
	return UEngineWindow::WindowMessageLoop(Start, FrameLoop);
}

void UEngineAPICore::EngineBeginPlay()
{
	UserCore->BeginPlay();
}

void UEngineAPICore::EngineTick()
{
	//AXVidio NewVidio;
	//NewVidio.Play("AAAA.avi");

	// �ð����
	// �̺�Ʈ
	// ������
	// �浹
	UserCore->Tick();

	// MainCore->TimeCheck();
	MainCore->Tick();
	// MainCore->Render();
	// MainCore->Collision();
}

void UEngineAPICore::Tick()
{
	if (nullptr == CurLevel)
	{
		MSGASSERT("���� �ھ ���� ������ �������� �ʾҽ��ϴ�");
		return;
	}

	CurLevel->Tick();
	CurLevel->Render();
}


void UEngineAPICore::OpenLevel(std::string_view _LevelName)
{
	std::string ChangeName = _LevelName.data();

	//if (true == Levels.contains(ChangeName))
	//{
	//	MSGASSERT(ChangeName + "��� �̸��� ������ �������� �ʽ��ϴ�.");
	//	return;
	//}

	//// �ֽ� ���
	// ������ ���� �ϳ��� �ִ�.
	// ������ ��带 insert���� �ع�����.
	// ���ο��� ������ ����ٱ��� ���ϰ� �ִ�.
	// CurLevel = Levels[ChangeName];

	std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(ChangeName);
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	if (EndIter == FindIter)
	{
		MSGASSERT(ChangeName + "��� �̸��� ������ �������� �ʽ��ϴ�.");
		return;
	}

	// �ֽ� ���
	CurLevel = FindIter->second;
}