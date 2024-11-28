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

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);

protected:

private:
	class USpriteRenderer* SpriteR = nullptr;
	UFSMStateManager FSM;

	float Speed = 500.0f;
	int IsGround = false;
	bool IsMove = false;

	int Water = 12;
	Tile* TargetTile = nullptr;
};