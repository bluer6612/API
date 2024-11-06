#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"


APlayMap::APlayMap()
{
	// �Ź� ������ ����� �ٲ��
	// �̰� ��ü�� ��� ������ �ƴմϴ�.
	//FVector2D WindowSize =  UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	//SetActorScale(WindowSize.Half());
	//SetActorLocation(WindowSize.Half());

	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		SpriteRenderer->SetSprite("bg001_Col.png");

		FVector2D MapScale = SpriteRenderer->SetSpriteScale(0.425f);
		SpriteRenderer->SetComponentLocation({ static_cast <float>(ScreenX) * 0.5f, static_cast <float>(-50) });
	}

}

APlayMap::~APlayMap()
{
}

