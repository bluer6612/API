#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/FSMStateManager.h>

// Ό³Έν :
class AHouse : public AActor
{
public:
	// constrcuter destructer
	AHouse();
	~AHouse();

	// delete Function
	AHouse(const AHouse& _Other) = delete;
	AHouse(AHouse&& _Other) noexcept = delete;
	AHouse& operator=(const AHouse& _Other) = delete;
	AHouse& operator=(AHouse&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);

protected:

private:
	class USpriteRenderer* SpriteRenderer;
	class USpriteRenderer* SpriteRendererWheel;
	UFSMStateManager FSM;
};