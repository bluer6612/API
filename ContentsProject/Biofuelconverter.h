#pragma once
#include "Building.h"

// Ό³Έν :
class ABiofuelconverter : public ABuilding
{
public:
	// constrcuter destructer
	ABiofuelconverter();
	~ABiofuelconverter();

	// delete Function
	ABiofuelconverter(const ABiofuelconverter& _Other) = delete;
	ABiofuelconverter(ABiofuelconverter&& _Other) noexcept = delete;
	ABiofuelconverter& operator=(const ABiofuelconverter& _Other) = delete;
	ABiofuelconverter& operator=(ABiofuelconverter&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);

protected:

private:
};

