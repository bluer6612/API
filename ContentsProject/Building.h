#pragma once
#include <EngineCore/Actor.h>

#include <EngineBase/FSMStateManager.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/GlobalVariable.h>

class ABuilding : public AActor
{
public:
	ABuilding();
	~ABuilding();

	ABuilding(const ABuilding& _Other) = delete;
	ABuilding(ABuilding&& _Other) noexcept = delete;
	ABuilding& operator=(const ABuilding& _Other) = delete;
	ABuilding& operator=(ABuilding&& _Other) noexcept = delete;

	void ModelAdd(std::string_view _Name, double _X, double _Y, int _Order);

protected:
	class USpriteRenderer* SpriteR = nullptr;
	class USpriteRenderer* Sprite[10] = {};

	UFSMStateManager FSM;

	USpriteRenderer* Model[20] = { };
	FVector2D Location;
	int index = 0;

private:

};

