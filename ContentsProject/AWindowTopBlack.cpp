#include "PreCompile.h"
#include "AWindowTopBlack.h"

#include <EngineCore/SpriteRenderer.h>

AWindowTopBlack::AWindowTopBlack()
{
	SetActorLocation({ ScreenX, 0 });

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("bg001_Col.png");
		SpriteRenderer->SetComponentScale({ ScreenX, 50 });
	}
}

AWindowTopBlack::~AWindowTopBlack()
{
}

void AWindowTopBlack::BeginPlay()
{
	Super::BeginPlay();
}

void AWindowTopBlack::SetColImage(std::string_view _ColImageName)
{
	ColImage = UImageManager::GetInst().FindImage(_ColImageName);
}

void AWindowTopBlack::LevelChangeStart()
{
	int a = 0;
}