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

	void ModelAdd(int _ModelNumber, float _Size, int _X, int _Y, int _Order);

	void ModelAdd(int _ModelNumber, int _SizeX, int _SizeY, int _X, int _Y, int _Order);

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;
	class USpriteRenderer* SpriteRendererWheel = nullptr;
	class USpriteRenderer* SpriteRendererDoor = nullptr;
	UFSMStateManager FSM;
};