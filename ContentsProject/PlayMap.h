#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class APlayMap : public AActor
{
public:
	APlayMap();
	~APlayMap();

	APlayMap(const APlayMap& _Other) = delete;
	APlayMap(APlayMap&& _Other) noexcept = delete;
	APlayMap& operator=(const APlayMap& _Other) = delete;
	APlayMap& operator=(APlayMap&& _Other) noexcept = delete;

protected:
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* BackSpriteR;
	USpriteRenderer* BackTopSpriteR;
	USpriteRenderer* BackBottomSpriteR;
};