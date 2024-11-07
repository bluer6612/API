#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>

enum class PlayerState
{
	Idle,
	Move,
	Jump,
};

class APlayer : public AActor
{
public:
		APlayer();
	~APlayer();

		APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MoveFunction(FVector2D _Dir);

	/*void LeftMove();
	void RightMove();
	void UpMove();
	void DownMove();*/

	void RunSoundPlay();

	void LevelChangeStart();
	void LevelChangeEnd();

	void SetColImage(std::string_view _ColImageName);

protected:

private:

	float Speed = 500.0f;
	int MySpriteIndex = 0;

	class USpriteRenderer* SpriteRenderer;
	
	class UEngineWinImage* ColImage = nullptr;

	PlayerState CurPlayerState = PlayerState::Idle;

				
	void ChangeState(PlayerState CurPlayerState);

	void IdleStart();
	void Idle(float _DeltaTime);
	void MoveStart();
	void Move(float _DeltaTime);
	void Fly(float _DeltaTime);

		void Gravity()
	{

	}


	
};

