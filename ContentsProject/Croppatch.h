#pragma once
#include "Building.h"

// Ό³Έν :
class ACroppatch : public ABuilding
{
public:
	ACroppatch();
	~ACroppatch();

	ACroppatch(const ACroppatch& _Other) = delete;
	ACroppatch(ACroppatch&& _Other) noexcept = delete;
	ACroppatch& operator=(const ACroppatch& _Other) = delete;
	ACroppatch& operator=(ACroppatch&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);
protected:

private:

};

