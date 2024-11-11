#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/FSMStateManager.h>

class AHouse : public AActor
{
public:
	
	AHouse();
	~AHouse();
	
	AHouse(const AHouse& _Other) = delete;
	AHouse(AHouse&& _Other) noexcept = delete;
	AHouse& operator=(const AHouse& _Other) = delete;
	AHouse& operator=(AHouse&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;
	class USpriteRenderer* SpriteRendererRightDoodad = nullptr;
	class USpriteRenderer* SpriteRendererWheel = nullptr;
	class USpriteRenderer* SpriteRendererDoor = nullptr;
	UFSMStateManager FSM;
};