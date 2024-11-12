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

	void ModelAdd(int _ModelNumber, float _Size, int _X, int _Y, int _Order);

	void ModelAdd(int _ModelNumber, int _SizeX, int _SizeY, int _X, int _Y, int _Order);

protected:
	int index = 0;
	USpriteRenderer* Model[20] = { };
	UFSMStateManager FSM;

private:

};

