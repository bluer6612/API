#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class AMenuUI : public AActor
{
public:
	// constrcuter destructer
	AMenuUI();
	~AMenuUI();

	// delete Function
	AMenuUI(const AMenuUI& _Other) = delete;
	AMenuUI(AMenuUI&& _Other) noexcept = delete;
	AMenuUI& operator=(const AMenuUI& _Other) = delete;
	AMenuUI& operator=(AMenuUI&& _Other) noexcept = delete;

protected:

private:

};

