#include "PreCompile.h"
#include "MenuUI.h"

AMenuUI::AMenuUI()
{
	Location.X = static_cast<float>(ScreenX * 0.5) - 197;
	Location.Y = static_cast<float>(ScreenY * 0.3 * 0.275);

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

