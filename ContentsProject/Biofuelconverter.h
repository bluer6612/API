#pragma once
#include "Building.h"

class ABiofuelconverter : public ABuilding
{
public:
	ABiofuelconverter();
	~ABiofuelconverter();

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

