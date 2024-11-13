#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/FSMStateManager.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"

// Ό³Έν :
class ABuilding : public AActor
{
public:
	// constrcuter destructer
	ABuilding();
	~ABuilding();

	// delete Function
	ABuilding(const ABuilding& _Other) = delete;
	ABuilding(ABuilding&& _Other) noexcept = delete;
	ABuilding& operator=(const ABuilding& _Other) = delete;
	ABuilding& operator=(ABuilding&& _Other) noexcept = delete;

	void ModelAdd(std::string _Name, double _X, double _Y, int _Order);

protected:
	class USpriteRenderer* SpriteRenderer = nullptr;

	UFSMStateManager FSM;

	USpriteRenderer* Model[20] = { };
	FVector2D Location;
	int index = 0;

private:

};

