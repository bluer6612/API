#include "PreCompile.h"
#include "Level.h"
#include "EngineAPICore.h"

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
	//if (nullptr != GameMode)
	//{
	//	delete GameMode;
	//	GameMode = nullptr;
	//}

	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;

		if (nullptr != CurActor)
		{
			delete *StartIter;
		}
	}
}

void ULevel::Tick(float _DeltaTime)
{
	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;

		CurActor->Tick(_DeltaTime);
	}
}

void ULevel::Render()
{
	// ���͸� ������� �������� �����°� �� ������ �̴ϴ�.
	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;

		CurActor->Render();
	}

}


void DoubleBuffering()
{
	// ������ �������� ������.
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();

	UEngineWinImage* WindowImage = MainWindow.GetWindowImage();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();

	// WindowImage->CopyTo(BackBufferImage);

}