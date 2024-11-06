#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>


APlayMap::APlayMap()
{
	// 매번 윈도우 사이즈가 바뀌면
	// 이거 자체도 사실 좋은건 아닙니다.
	//FVector2D WindowSize =  UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	//SetActorScale(WindowSize.Half());
	//SetActorLocation(WindowSize.Half());

	{
		{
			BackSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
			BackSpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
			BackSpriteRenderer->SetSprite("bg001.png");

			FVector2D MapScale = BackSpriteRenderer->SetSpriteScale(1.0f);
			BackSpriteRenderer->SetComponentLocation(MapScale.Half());
		}

		{
			BackTopSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
			BackTopSpriteRenderer->SetOrder(ERenderOrder::BACKGROUNDTOP);
			BackTopSpriteRenderer->SetSprite("bg001_Col.png");

			FVector2D MapScale = BackTopSpriteRenderer->SetSpriteScale(1.0f);
			BackTopSpriteRenderer->SetComponentLocation({ScreenX, -30 });
		}

		{
			ColSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
			ColSpriteRenderer->SetOrder(ERenderOrder::COLMAP);
			ColSpriteRenderer->SetSprite("bg001_Col.png");

			FVector2D MapScale = ColSpriteRenderer->SetSpriteScale(0.4f);
			ColSpriteRenderer->SetComponentLocation({ ScreenX, 0});
		}

	}

}

APlayMap::~APlayMap()
{
}

void APlayMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('Y'))
	{
		ColSpriteRenderer->SetActiveSwitch();
	}
}