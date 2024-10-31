#include "PreCompile.h"
#include "Level.h"
#include "EngineAPICore.h"

#include <EngineBase/EngineMath.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineWinImage.h>

#include "SpriteRenderer.h"

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
	ScreenClear();

	// 지금 이제 랜더링의 주체가 USpriteRenderer 바뀌었다.
	// 액터를 기반으로 랜더링을 돌리는건 곧 지워질 겁니다.

	// 액터가 SpriteRenderer를 만들면
	// Level도 그 스프라이트 랜더러를 알아야 한다.



	DoubleBuffering();
}

void ULevel::ScreenClear()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	FVector2D Size = MainWindow.GetWindowSize();

	Rectangle(BackBufferImage->GetDC(), -1, -1, Size.iX() + 2, Size.iY() + 2);
}

void ULevel::DoubleBuffering()
{
	// 레벨의 랜더링이 끝났다.
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();

	UEngineWinImage* WindowImage = MainWindow.GetWindowImage();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();

	FTransform Trans;
	Trans.Location = MainWindow.GetWindowSize().Half();
	Trans.Scale = MainWindow.GetWindowSize();

	// 이미지 들은 백버퍼에 다 그려졌을 것이다.
	BackBufferImage->CopyToBit(WindowImage, Trans);

}

void ULevel::PushRenderer(class USpriteRenderer* _Renderer)
{
	Renderers[_Renderer->GetOrder()].push_back(_Renderer);
}