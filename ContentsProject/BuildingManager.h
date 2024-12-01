#pragma once
#include "UIManager.h"
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/GlobalVariable.h>
#include "UIManager.h"

// Ό³Έν :
class ABuildingManager : public AUIManager
{
public:
	ABuildingManager();
	~ABuildingManager();

	ABuildingManager(const ABuildingManager& _Other) = delete;
	ABuildingManager(ABuildingManager&& _Other) noexcept = delete;
	ABuildingManager& operator=(const ABuildingManager& _Other) = delete;
	ABuildingManager& operator=(ABuildingManager&& _Other) noexcept = delete;

	void SetUIManager(AUIManager* const _UIManager)
	{
		UIManager = _UIManager;
	}

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;

	UFSMStateManager FSM;
	class USpriteRenderer* SpriteR = nullptr;
	class USpriteRenderer* Model[20] = { };

	FVector2D Location;
	int index = 0;

private:
	AUIManager* UIManager = nullptr;
};