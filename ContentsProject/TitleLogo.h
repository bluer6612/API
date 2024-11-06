#pragma once
#include "PreCompile.h"
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class TitleLogo : public AActor
{
public:
	// constrcuter destructer
	TitleLogo();
	~TitleLogo();

	// delete Function
	TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator=(const TitleLogo& _Other) = delete;
	TitleLogo& operator=(TitleLogo&& _Other) noexcept = delete;
protected:
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* LogoSpriteRenderer;
	USpriteRenderer* TooltipSpriteRenderer;
	USpriteRenderer* MoneySpriteRenderer;
	USpriteRenderer* ButtonSpriteRenderer;
};

