#include "PreCompile.h"
#include "SpriteRenderer.h"
#include "ImageManager.h"

#include "EngineAPICore.h"

USpriteRenderer::USpriteRenderer()
{
}

USpriteRenderer::~USpriteRenderer()
{
}

// SpriteRenderer : public URenderer
// MeshRenderer : public URenderer
// StaticMeshRenderer : public URenderer
void USpriteRenderer::Render()
{
	if (nullptr == Sprite)
	{
		MSGASSERT("��������Ʈ�� ���õ��� ���� ���͸� �������� �Ҽ� �����ϴ�.");
		return;
	}

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();


	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);
	CurData.Image->CopyToTrans(BackBufferImage, GetTransform(), CurData.Transform);
}

void USpriteRenderer::BeginPlay()
{
	// �θ� Ŭ������ �Լ��� ȣ���ϴ°� �����ϸ� �ȵȴ�.
	// �����Ǹ� ���� �𸮾� �н����� �ɸ����� �Ǵ� ������ �ȴ�.
	Super::BeginPlay();

	// ��������Ʈ �������� 

	AActor* Actor = GetActor();
	ULevel* Level = Actor->GetWorld();

	Level->PushRenderer(this);
}

void USpriteRenderer::ComponentTick(float _DeltaTime)
{
	Super::ComponentTick(_DeltaTime);
}

void USpriteRenderer::SetSprite(std::string_view _Name, int _CurIndex /*= 0*/)
{
	// �̱��濡 ���ؼ� �����Ҷ�
	// ���� ���ϰ� �����ϱ� ���ؼ� ����ϴ� �Ŷ�� �ϸ� Ʋ�ȴ�.
	// ��ü�� �� 1�� ����� �����̶�� ���� ���� ���ð�

	// ���Ͱ� ������������� �ε尡 ���� ��Ȳ�̾�� �Ѵ�.
	Sprite = UImageManager::GetInst().FindSprite(_Name);

	if (nullptr == Sprite)
	{
		MSGASSERT("�ε����� ���� ��������Ʈ�� ����Ϸ��� �߽��ϴ�" + std::string(_Name));
		return;
	}

	CurIndex = _CurIndex;
}
