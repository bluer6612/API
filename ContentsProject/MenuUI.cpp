#include "PreCompile.h"
#include "MenuUI.h"

AMenuUI::AMenuUI()
{
	Location.X = ScreenHX - 197;
	Location.Y = ScreenHY;

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Biofuelconverter");
		SpriteRenderer->CreateAnimation("Idle", "Biofuelconverter", 0, 0, 1.0f);
		SpriteRenderer->SetComponentScale({ static_cast<float>(55 * 2), static_cast<float>(57 * 2) });
		SpriteRenderer->SetComponentLocation({ Location.X, Location.Y });
	}
}

AMenuUI::~AMenuUI()
{
}

