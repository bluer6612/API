#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/FSMStateManager.h>
#include "CharacterManager.h"

class ARusty : public ACharacterManager
{
public:
	ARusty();
	~ARusty();

	ARusty(const ARusty& _Other) = delete;
	ARusty(ARusty&& _Other) noexcept = delete;
	ARusty& operator=(const ARusty& _Other) = delete;
	ARusty& operator=(ARusty&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ChangeAction(NewPlayerState _NewPlayerState);
	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Water(float _DeltaTime);
	void WaterGet(float _DeltaTime);
	void Harvest(float _DeltaTime);
	void HarvestCarry(float _DeltaTime);

protected:

private:
	Tile* TargetTile = nullptr;
	class USpriteRenderer* SpriteR = nullptr;
	class USpriteRenderer* SpriteRSub = nullptr;
	UFSMStateManager FSM;

	int WaterCount = 12;
};