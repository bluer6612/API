#pragma once
#include "Building.h"

class AWell : public ABuilding
{
public:
		AWell();
	~AWell();

		AWell(const AWell& _Other) = delete;
	AWell(AWell&& _Other) noexcept = delete;
	AWell& operator=(const AWell& _Other) = delete;
	AWell& operator=(AWell&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);

protected:

private:
};

