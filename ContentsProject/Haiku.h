#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/FSMStateManager.h>
#include "CharacterManager.h"

// Ό³Έν :
class AHaiku : public ACharacterManager
{
public:
	// constrcuter destructer
	AHaiku();
	~AHaiku();

	// delete Function
	AHaiku(const AHaiku& _Other) = delete;
	AHaiku(AHaiku&& _Other) noexcept = delete;
	AHaiku& operator=(const AHaiku& _Other) = delete;
	AHaiku& operator=(AHaiku&& _Other) noexcept = delete;

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

