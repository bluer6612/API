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
		MSGASSERT("Main windowDC�� �����ʰ� �̹����� �����Ϸ��� �߽��ϴ�");
		return;
	}

	// HDC �ƹ��͵� ��������
	// HDC �־�޶�� �ϴµ� window HDC
	// int X; ������� �� �̹����� xũ��
	// int Y; ������� �� �̹����� yũ��

	// �ƹ��͵� ���°��� 
	// HDC hdc Ÿ�� �� �̹����� ���� �׸����� �ϴ� Ÿ��
	// int cx ������� �̹����� ũ��
	// int cy ������� �̹����� ũ��

	
	
	HBITMAP NewBitmap = static_cast<HBITMAP>(CreateCompatibleBitmap(_TargetImage->GetDC(), _Scale.iX(), _Scale.iY()));

	// �̹��� ����ü
	// �̹����� �����Ҽ� �ִ� ���� HDC
	// �̹����� ������ ���� HBITMAP
	// HDC<=>HBITMAP �� �������� �̹����� �̹����� �����ϴ� ������ ����Ǵ� ����

	// ��
	HDC NewImageDC = CreateCompatibleDC(_TargetImage->GetDC());

	// �����찡 ���ϱ⸦ �װ� ��ȭ���� �ѽ����� �ȿ����� ���׸�.
	// ���� ����⸸ �ص�  1, 1 �̹����� ������ ���´�. window 

	// �װ� ��ȭ���� �����ϴ� �۾��� ���ľ� �Ѵ�.
	HBITMAP OldBitMap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));
	// OldBitMap 1, 1 ũ���� �̹���
	// ������ �������θ� leck
	DeleteObject(OldBitMap);

	hBitMap = NewBitmap;
	ImageDC = NewImageDC;

	GetObject(hBitMap, sizeof(BITMAP), &Info);
}