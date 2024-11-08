#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class TitleLogo : public AActor
{
public:
		TitleLogo();
	~TitleLogo();

		TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator=(const TitleLogo& _Other) = delete;
	TitleLogo& operator=(TitleLogo&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

	inline USpriteRenderer* GetLogoSpriteRenderer() const;

protected:

private:
	USpriteRenderer* LogoSpriteRenderer;
	USpriteRenderer* TooltipSpriteRenderer;
	USpriteRenderer* MoneySpriteRenderer;
	USpriteRenderer* ButtonSpriteRenderer;
};

