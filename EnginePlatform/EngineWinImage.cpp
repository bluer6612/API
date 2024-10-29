#include "PreCompile.h"
#include "EngineWinImage.h"
#include <EngineBase/EngineDebug.h>

UEngineWinImage::UEngineWinImage()
{
}

UEngineWinImage::~UEngineWinImage()
{
}

void UEngineWinImage::Create(UEngineWinImage* _TargetImage,  FVector2D _Scale)
{
	if (nullptr == _TargetImage)
	{
		MSGASSERT("Main windowDC를 넣지않고 이미지를 생성하려고 했습니다");
		return;
	}

	// HDC 아무것도 없곳에서
	// HDC 넣어달라고 하는데 window HDC
	// int X; 만들려는 빈 이미지의 x크기
	// int Y; 만들려는 빈 이미지의 y크기

	// 아무것도 없는곳에 
	// HDC hdc 타겟 이 이미지를 만들어서 그리려고 하는 타겟
	// int cx 만들려는 이미지의 크기
	// int cy 만들려는 이미지의 크기

	
	
	HBITMAP NewBitmap = static_cast<HBITMAP>(CreateCompatibleBitmap(_TargetImage->GetDC(), _Scale.iX(), _Scale.iY()));

	// 이미지 그자체
	// 이미지를 수정할수 있는 권한 HDC
	// 이미지의 데이터 권한 HBITMAP
	// HDC<=>HBITMAP 이 합쳐져서 이미지와 이미지를 수정하는 권한이 연결되는 개념

	// 붓
	HDC NewImageDC = CreateCompatibleDC(_TargetImage->GetDC());

	// 윈도우가 정하기를 붓과 도화지를 한쌍으로 안엮으면 못그림.
	// 붓을 만들기만 해도  1, 1 이미지랑 연결해 놓는다. window 

	// 붓과 도화지를 연결하는 작업을 거쳐야 한다.
	HBITMAP OldBitMap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));
	// OldBitMap 1, 1 크기의 이미지
	// 가만히 내버려두면 leck
	DeleteObject(OldBitMap);

	hBitMap = NewBitmap;
	ImageDC = NewImageDC;

	GetObject(hBitMap, sizeof(BITMAP), &Info);
}

void UEngineWinImage::CopyToBit(UEngineWinImage* _TargetImage, const FTransform& _Trans)
{
	if (nullptr == _TargetImage)
	{
		MSGASSERT("복사받을 대상이 존재하지 않습니다");
	}

	HDC CopyDC = ImageDC;
	HDC TargetDC = _TargetImage->ImageDC;
	// CopyDC => TargetDC에 카피하겠다.
	// 윈도우는 이런 HDC간의 Copy를 위해서 
	// 카피용 함수들을 몇개 준비했고 그중에서
	// 가장 기본적인 함수가 바로 Bitblt

	//HDC hdc, 카피 받을 대상 <= 여기에다가 복사해라
	//int x, <= 위치x
	//int y, <= 위치y
	//int cx, <= 크기x
	//int cy, <= 크기x
	// HDC hdcSrc, 카피할 이미지
	// int x1, 이미지 시작점 0
	// int y1, 
	// rop => 카피 옵션

	FVector2D LeftTop = _Trans.CenterLeftTop();
	FVector2D RightBot = _Trans.CenterRightBottom();

	BitBlt(
		TargetDC,
		LeftTop.iX(),
		LeftTop.iY(),
		_Trans.Scale.iX(),
		_Trans.Scale.iY(),
		CopyDC,
		0,
		0,
		SRCCOPY);

	// SRCCOPY 카피할때 

}