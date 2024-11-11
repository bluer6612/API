#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/FSMStateManager.h>

class ARusty : public AActor
{
public:
	// constrcuter destructer
	ARusty();
	~ARusty();

	// delete Function
	ARusty(const ARusty& _Other) = delete;
	ARusty(ARusty&& _Other) noexcept = delete;
	ARusty& operator=(const ARusty& _Other) = delete;
	ARusty& operator=(ARusty&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);

	void LevelChangeStart() override;

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;
	UFSMStateManager FSM;

	float Speed = 500.0f;
	int IsGround = false;
	bool IsMove = false;
};