#pragma once
#include "BuildingManager.h"

#include <EngineBase/FSMStateManager.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/GlobalVariable.h>
//#include "UIManager.h"

class ABuilding : public ABuildingManager
{
public:
	ABuilding();
	~ABuilding();

	ABuilding(const ABuilding& _Other) = delete;
	ABuilding(ABuilding&& _Other) noexcept = delete;
	ABuilding& operator=(const ABuilding& _Other) = delete;
	ABuilding& operator=(ABuilding&& _Other) noexcept = delete;

	void ModelAdd(std::string_view _Name, double _X, double _Y, int _Order);/*

	void SetUIManager(AUIManager* const _UIManager)
	{
		UIManager = _UIManager;
	}*/

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;

	UFSMStateManager FSM;
	class USpriteRenderer* SpriteR = nullptr;
	class USpriteRenderer* Model[20] = { };

	FVector2D Location;
	int index = 0;

private:
	//AUIManager* UIManager = nullptr;
};

