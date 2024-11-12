#pragma once
#include "Building.h"

// Ό³Έν :
class AWell : public ABuilding
{
public:
	// constrcuter destructer
	AWell();
	~AWell();

	// delete Function
	AWell(const AWell& _Other) = delete;
	AWell(AWell&& _Other) noexcept = delete;
	AWell& operator=(const AWell& _Other) = delete;
	AWell& operator=(AWell&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;

};

