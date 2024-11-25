#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include "Building.h"

class TitleLogo : public ABuilding
{
public:
	TitleLogo();
	~TitleLogo();

	TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator=(const TitleLogo& _Other) = delete;
	TitleLogo& operator=(TitleLogo&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

	void TitleButtonEnter(AActor* _Actor, FVector2D _Index);
	void TitleButtonStay(AActor* _Actor, FVector2D _Index);

protected:

private:
	USpriteRenderer* LogoSpriteR;
	USpriteRenderer* TooltipSpriteR;
	USpriteRenderer* ButtonSpriteR;
	USpriteRenderer* ButtonBorderSpriteR;
};

