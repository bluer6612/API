#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>

enum class NewPlayerState
{
	Idle,
	Move,
};

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

	void LevelChangeStart() override;

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);

	void SetColImage(std::string_view _ColImageName);


protected:

private:
	U2DCollision* CollisionComponent;
	float Speed = 500.0f;
	class UEngineWinImage* ColImage = nullptr;
	class USpriteRenderer* SpriteRenderer = nullptr;

	int IsGround = false;
	bool IsMove = false;

	UFSMStateManager FSM;
};