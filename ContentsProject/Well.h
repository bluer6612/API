#pragma once
#include "BuildingManager.h"

class AWell : public ABuildingManager
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

